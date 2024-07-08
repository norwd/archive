# BrainFunct Macro interpreter
# $Id: bfm.py 1.9 2001/01/04 22:47:45 vdp Exp vdp $
#
# LANGUAGE LEVEL 2: HIGHER-ORDER MACROS

# Author: Frédéric van der Plancke
#         <http://go.to/fvdp/> <frederic.vdplancke@writeme.com>
# Disclaimer: the author(s) take no responsibility to whatever happens
#         as a result of using (or not using) this program.
# License: public domain


_testing_ = 0

import string
import re

#input-output classes:
#input_fn is callable with type "unit -> char or None" where None means EOF
#output_fn is callable with type "char -> unit"

class BfRuntimeError:
   def __init__(self, msg):
       self.msg = msg
   def __repr__(self):
       return "BfRuntimeError(%s)" % self.msg


class BfRuntime:
    def __init__(self, input_fn = None, output_fn = None):
        self.array = 256 * [0]
        self.array_start = 0
        self.memptr = 0

        if input_fn is None:
            input_fn = (lambda : None)
        assert callable(input_fn)  # can't assert functional type more precisely...
        self.input_fn = input_fn

        if output_fn is None:
            output_fn = (lambda c : None)
        assert callable(output_fn)
        self.output_fn = output_fn

        self.ins = { '+': self.plus, '-': self.minus, '<': self.left, '>': self.right,
                     '.': self.output, ',': self.input }

    def execute_ins(self, ins):
        method = self.ins.get(ins)
        if method is not None:
            method()
        else:
            raise BfRuntimeError("Undefined BF instruction")

    def plus(self):
        self.array[self.memptr] = (self.array[self.memptr] + 1) % 256

    def minus(self):
        self.array[self.memptr] = (self.array[self.memptr] + 255) % 256

    def left(self):
        if self.memptr == 0:
            n = min(100, len(self.array) / 3)
            self.array = n * [0] + self.array
            self.array_start = n + self.array_start
            self.memptr = n + self.memptr

        self.memptr = self.memptr - 1

    def right(self):
        if self.memptr <= len(self.array):
            n = min(100, len(self.array) / 3)
            self.array = self.array + n * [0]

        self.memptr = self.memptr + 1


    def is_zero(self):
        return self.array[self.memptr] == 0

    def input(self):
        c = self.input_fn()
        if c:
            assert type(c) is type("") and len(c) is 1
            i = ord(c)
        else:
            i = 0
        self.array[self.memptr] = i


    def output(self):
        c = self.array[self.memptr]
        self.output_fn(chr(c))



class BfmRuntime(BfRuntime):
    debug_stack_depth_limit = 490
    # getting such a big stack is easier than you think !
    # limit is set to 490 because:
    #    * Python 2 stack depth limit is 1000 on my machine, and
    #    * each BFM macro call consumes two Python calls.

    def __init__(self, input_fn = None, output_fn = None):
        BfRuntime.__init__(self, input_fn, output_fn)
        self.env_frame = Frame(None, None, None)  #dummy
        self.depth = 0  # depth of recursive calls to execute_sequence

    def getCurrentFrame(self):
        return self.env_frame

    def setCurrentFrame(self, frame):
        assert isinstance(frame, Frame)
        self.env_frame = frame

    def resetExecutionDepth(self):
        self.depth = 0

    def execute_sequence(self, body):
        """execute code_item sequence in current env, which is updated"""

        def combined_sequence_value(old_value, new_value):
            if new_value is None:
                return old_value
            else: #new_value is not None:
                if old_value is not None:
                    ok = isinstance(new_value, GroundValue) and isinstance(old_value, GroundValue)
                    if not ok:
                        #print "BFERR - old value (%s) new value (%s)" % (old_value, new_value)
                        #raise BfRuntimeError("non-ground value in sequence")
                        raise BfRuntimeError("you tried to concatenate a not-fully-evaluated macro with something")
                return new_value


        # we must check depth, lest the Python stack be overflown; and that would be fatal.
        if self.depth > self.debug_stack_depth_limit:
            raise BfRuntimeError("stack depth exceeded debug limit : infinite recursion possible")
            # a well-formed BFM program has no recursive macro-calls.
            # YES BUT: we don't check this well enough: e.g. "&f(f); f(f)"

        value = None

        self.depth = self.depth + 1
        for code_item in body:
            assert isinstance(code_item, CodeItem)
            new_value = code_item.execute(self)
            value = combined_sequence_value(value, new_value)

        self.depth = self.depth - 1
        assert self.depth >= 0

        if value is None: value = theGroundValue   # no value -> empty ground value
        return value


    def execute_ground_sequence(self, body):
        """same as execute_sequence; ensure the result is ground."""
        value = self.execute_sequence(body)
        if not isinstance(value, GroundValue):
            raise BfRuntimeError("non-ground value in ground sequence")
        return value


    def execute_sequence_in(self, body, env):
        """execute code_item sequence in given temporary env, which is discarded"""

        assert isinstance(env, Frame)
        old_env = self.getCurrentFrame()
        self.setCurrentFrame(env)
        value = self.execute_sequence(body)
        self.setCurrentFrame(old_env)
        return value


def str_sequence(sequence):
    return string.join(map(str, sequence), "")


class GroundValue:
    pass
theGroundValue = GroundValue()

class CodeItem:
    pass
    def execute(self, runtime):
        raise "undefined interface fn"


class CodeInstruction(CodeItem):

    def __init__(self, ins_char):
        self.ins = ins_char

    def execute(self, runtime):
        runtime.execute_ins(self.ins)
        return theGroundValue

    def __str__(self):
        return self.ins
    def __repr__(self):
        return "CodeInstruction(%s)" % repr(self.ins)


class CodeLoop(CodeItem):
    def __init__(self, body):
        self.body = body

    def execute(self, runtime):
       # make new frame
       # execute body in new frame
       outside_frame = runtime.getCurrentFrame()
       while not runtime.is_zero():
           runtime.execute_ground_sequence(self.body)
           runtime.setCurrentFrame(outside_frame)
       return theGroundValue   #should combine values of sequence somehow ?


    def __str__(self):
        return "[%s]" % str_sequence(self.body)
    def __repr__(self):
        return "CodeLoop(%s)" % repr(self.body)


class CodeMacroCall(CodeItem):
    def __init__(self, name, arg_list):
        assert type(name) is type("")
        # assert type(arg_list) is list of CodeItem lists...

        self.name = name
        self.arglist = arg_list


    def execute(self, runtime):

        caller_env = runtime.getCurrentFrame()
        (macro_decl, inside_env) = caller_env.find(self.name)   #may raise exception
        arguments = self.arglist

        # we can't use [self] in the sequel. Let's forbid it:
        del self   ##ever seen this ???

        while 1:
            #done?@@@to correct: change [outside_env] to [caller_env] and update it for subcalls
            #LOOP:
            #  next iterations of this loop
            #      execute [macro_decl] with arguments [arguments]
            #  it cannot use [self] (except perhaps for error messages)

            #if __debug__:
            #    print "CodeMacroCall, execution step:"
            #    print "  formals = %s; args = %s; decl = %s" % (
            #        macro_decl.formals, arguments, macro_decl)

            num_arguments = len(arguments)
            num_formals = len(macro_decl.formals)

            #--- bind arguments in new environment:

            #inside_env = macro_decl.env
            #assert inside_env, "call of non-already-executed macro declaration : internal error ?"

            num_binds = min(num_formals, num_arguments)
            binds = map(None, arguments[:num_binds], macro_decl.formals[:num_binds])
            for (arg, formal) in binds:
                pseudo_decl = CodeMacroDecl(formal, [], arg)
                pseudo_decl.debug_info = "arg of macro %s at %d" % (str(macro_decl), id(macro_decl))
                inside_env = Frame(inside_env, pseudo_decl, caller_env)  #@why caller_env ?

            #--- macro "execution" in new [inside_env]:

            if num_formals > num_arguments:
                # return closure value as CodeMacroDecl:
                # such a closure never appears in code;
                #   it can have any name, as its name never appears in any frame.
                closure_decl = CodeMacroDecl("<closure>", macro_decl.formals[num_binds:],
                                             macro_decl.body)
                return (closure_decl, inside_env)

            else: #if num_formals <= num_arguments:
                assert num_formals <= num_arguments

                #-- call macro and return or use its value

                runtime.setCurrentFrame(inside_env)
                value = runtime.execute_sequence(macro_decl.body)
                runtime.setCurrentFrame(caller_env)  # restore frame

                if num_formals == num_arguments:
                    return value
                else:
                    if value is None or isinstance(value, GroundValue):
                        raise BfRuntimeError("call of non-macro closure, or too many arguments")
                    else:
                        (macro_decl, inside_env) = value
                        assert isinstance(macro_decl, CodeMacroDecl)
                        assert isinstance(inside_env, Frame)

                    arguments = arguments[num_binds :]


    def __repr__(self):
        return "CodeMacroCall(%s,%s)" % (repr(self.name), repr(self.arglist))

    def __str__(self):
        if self.arglist:
            arg_strings = []
            for arg in self.arglist:
                arg_strings.append( str_sequence(arg) )

            arg_string = string.join(arg_strings, "|")
            return " %s(%s)" % (self.name, arg_string)

        else:
            return " " + self.name


class CodeMacroDecl(CodeItem):
    def __init__(self, name, formals, body):
        assert type(name) is type("")
        assert type(formals) is type([])   # string list

        self.name = name
        self.formals = formals
        self.body = body

        # computed lazily:
        self.type = None


    def execute(self, runtime):
        # (1) warning, a declaration can be executed several times
        #     AND NOT ALWAYS IN THE (semantically) SAME ENVIRONMENT.
        #     example: 'local' in "&thing(x) = &local(z)=x;; thing(+) thing(-)"
        # (2) True, but now useless:
        #     a macro cannot possibly be called before its definition is reached & executed
        #     (since the definition does not belong to any Frame before it is executed)

        env = runtime.getCurrentFrame()
        new_env = Frame(env, self, env)
        runtime.setCurrentFrame(new_env)
        return None  # no value


    def __repr__(self):
        return "CodeMacroDecl(%s,%s,%s)" % (repr(self.name), self.formals, repr(self.body))

    def __str__(self):
        if self.formals:
            formals_string = "(" + string.join(self.formals, '|') + ")"
        else:
            formals_string = ""

        return "&%s%s=%s;" % (self.name, formals_string, str_sequence(self.body))


class Code_debug_Dump(CodeItem):
    def __init__(self,ident):
        self.ident = ident

    def execute(self, runtime):
        print "?%s" % self.ident,
        #return None  # no value... this is @@@infraction to overall design
        return theGroundValue

    def __repr__(self):
        return "Code_debug_Dump(%s)" % self.ident
    def __str__(self):
        return "?%s" % self.ident

#---------------------------------

class Frame:
    def __init__(self, parent, macro_decl, decl_env):

        if parent is not None:
            # real cell:
            assert isinstance(macro_decl, CodeMacroDecl)
            self.parent = parent
            self.macro_name = macro_decl.name
            self.macro_decl = macro_decl

            assert isinstance(decl_env, Frame)
            self.macro_decl_env = decl_env

        else:
            # dummy
            assert macro_decl is None
            self.parent = None
            self.macro_name = "+"  # some invalid macro name
            self.macro_decl = None
            self.macro_decl_env = None


    def find(self, name):
        assert type(name) is type("")

        if self.macro_name == name:
            return (self.macro_decl, self.macro_decl_env)
        elif self.parent is not None:
            return self.parent.find(name)
        else:
            raise BfRuntimeError("undefined macro " + name)

    #--- debug methods:

    def dump(self):
        if self.parent is not None:
            print "  ", self.macro_decl
            self.parent.dump()
        else:
            print "  end of frame"

    def get_all_names(self):
        countmap = {}
        current = self
        names = []

        while current.parent is not None:
            name = current.macro_name
            count = countmap.get(name, 0)
            countmap[name] = count + 1
            if count > 0:
                # name already met
                name = "%s(%d)" % (name, count)
            names.append(name)
            current = current.parent

        return names

    '''
    def find_n(self, name, n):
        assert type(name) is type("")

        if self.macro_name == name:
            if n = 0:
                return (self.macro_decl, self.macro_decl_env)
            else:
                return self.parent.find_n(name, n-1)
        elif self.parent is not None:
            return self.parent.find_n(name, n)
        else:
            raise BfRuntimeError("macro " + name + " not found")


    def get_definition(self, name):
        count = 0
        if '(' in name:
            try:
                prog = re.compile("(.*)\((.*)\)$")
                g = prog.match(name).groups()
                print g
                #@@@@@
                name = 00000000
            except:
                raise BfRuntimeError("undefined macro " + name)


        current = self
    '''

    def get_definition(self, name):
        decl, env = self.find(name)
        return str(decl)


#---------------------------------

_digits = "0123456789"
_alpha = "abcdefghijklmnopqrstuvwxyz"
_Alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
_identifier_head_char = _digits + _alpha + _Alpha + "_"
_identifier_body_char = _identifier_head_char


class ParseError:
   def __init__(self, msg):
       self.msg = msg
   def __repr__(self):
       return "ParseError(%s)" % self.msg


def parse_item(stream):
   eat_space(stream)

   c = stream.peek()

   if c in "+-,.<>":
       stream.junk()
       return CodeInstruction(c)

   elif c == "[":
       stream.junk()
       loop = parse_sequence(stream)
       stream.eat("]")
       return CodeLoop(loop)

   elif c in _identifier_head_char:
       ident = parse_identifier(stream)
       args = parse_arguments(stream, parse_sequence)
       return CodeMacroCall(ident, args)

   elif c == "&":
       stream.junk()
       eat_space(stream)
       ident = parse_identifier(stream)

       formals = parse_arguments(stream, parse_identifier)

       eat_space(stream)
       stream.eat("=")

       body = parse_sequence(stream)

       stream.eat(";")

       return CodeMacroDecl(ident, formals, body)

   elif c == "?":  # DEBUG ONLY
       stream.junk()
       ident = parse_identifier(stream)
       return Code_debug_Dump(ident)

   else:
       return None


def parse_arguments(stream, arg_parser):
    args = []

    eat_space(stream)
    d = stream.peek()

    while (d == '('):
        d = '|'
        while d == '|':
               stream.junk()
               eat_space(stream)
               arg = arg_parser(stream)
               args.append(arg)
               eat_space(stream)
               d = stream.peek()

        stream.eat(')')

        eat_space(stream)
        d = stream.peek()

    return args


def parse_sequence(stream):
    sequence = []
    while 1:
        item = parse_item(stream)
        if item is None:
            break
        else:
            sequence.append(item)

    return sequence


def eat_space(stream):
    _spaces = " \t"
    _ends = "\n\0"

    while 1:
        c = stream.peek()
        if c in _spaces:
            stream.junk()
        elif c == '#':
            while not stream.peek() in _ends:
                stream.junk()
            stream.junk()   # junk the end
        else:
            break

def parse_identifier(stream):
    c = stream.peek()
    if c not in _identifier_head_char:
        raise ParseError("expected identifier")

    ident = c
    stream.junk()
    while stream.peek() in _identifier_body_char:
        ident = ident + stream.peek()
        stream.junk()

    return ident


#---------------------------------

class Stream:
    def __init__(self, string):
        self.string = string
        self.index = 0

    def eof(self):
        return self.index >= len(self.string)

    def peek(self):
        if self.index < len(self.string):
            return self.string[self.index]
        else:
            return "\0"

    def junk(self):
        self.index = self.index + 1

    def eat(self, c):
        assert len(c) == 1
        if self.peek() != c:
            raise ParseError("expected '%s' got '%s'" % (c, self.peek()))
        else:
            self.junk()


#------------------------------------------------------------------
#           PARSING
#------------------------------------------------------------------

_parse_debug = _testing_

def parse(code):
    stream = Stream(code)
    c = parse_sequence(stream)
    eat_space(stream)
    stream.eat("\0")

    if _parse_debug:
        print "From:", code
        print "Repr:", repr(c)
        print "Str:", string.join(map(str,c), "")
    return c

parse("+-,.<>")
parse("+[-]")
parse("+[-+][+[-]]")
parse("+- zut ou quoi")
parse("&zut=+-;")
parse("&zut=+-;&t(x)=;&t(a|b|c)=zut;")
parse("& zut = +- ; & t(x) = ; & t(a|b|c) = zut;")
parse("  &  zut  =  +  -  ;  &  t  (  x  )  = ; &  t ( a | b | c )  =  zut  ;  ")
parse("+[?any-]")
parse("+ #comment\n - #other comment\n +")

try:
    parse("&zut=[bad;]")
except ParseError:
    print "ok 1"

library = [ # standard things:
   # you better not call &meet_God;
   "&meet_God= &f(f)=f(f); f(f);"

   #standard things...
   "&if(then)= [ then [-] ];",

   #-- level 2 standard things

   "&apply(x|y)=x(y);",
   "&compose(f|g) = &f_g(x)=f(g(x)); f_g;",  #better: &compose(f|g|x)=f(g(x));
   "&id(x)=x;",  # identity

   # Concatenation numbers from 0 to 10
   "&0(t)=; &1(t)=0()t; &2(t)=t t; &3(t)=t t t; &4(t)=2(2(t)); &5(t)=4(t) t; &6(t)=3(2(t));"
   "&7(t)=4(t) 3(t); &8(t)=4(2(t)); &9(t)=3(3(t)); &10(t)=5(t t);",

   # Concatenation number constructors
   "&nn(x|y)= &nn_t(t)=x(10(t)) y(t); nn_t;",
   "&NN(x|y|t)=x(10(t)) y(t);"  # [nn] and [NN] are semantically identical

   "&plus(x|y|t)=x(t)y(t);"

   # Church numbers from 0 to 10;
   # for such a number c whose value is n, c(t|x) applies n times macro t to parameter x
   "&ch_0(t|x)=x; &ch_1(t|x)=t(x); &ch_2(t|x)=t(t(x)); &ch_3(t|x)=t(t(t(x)));"
   "&ch_plus(n|m|t|x)=n(t|m(t|x));"
   "&ch_times(n|m|t|x)=n(m(t)|x);"
   "&ch_power(n|m) = m(ch_times(n) | ch_1);"
   "&ch_4=ch_times(ch_2|ch_2); &ch_5=ch_plus(ch_2|ch_3); &ch_6=ch_times(ch_2|ch_3);"
   "&ch_7=ch_plus(ch_3|ch_4); &ch_8=ch_power(ch_2|ch_3); &ch_9=ch_power(ch_3|ch_2);"
   "&ch_10=ch_times(ch_2|ch_5);"

   # Output of concatenation numbers, as numbers and as lowercase/uppercase letters:
   # out(n), outa(n), outA(n)
   "&out(n)=[-] n(+) .;"
   "&outa(n)=out(plus(nn(9|6)|n)); &outA(n)=out(plus(nn(6|4)|n));"

   # Output of Church numbers:
   "&concat_of_ch(n|text) = n( & concat_text(right) = text right; concat_text | );"
   "&ch_out(n)=out(concat_of_ch(n));"

   ]

test = [
   "+++[?any -]",
   "&macro=?macro; macro",
   "&macro2(arg)= ?in arg ?out;   macro2(?hello)",
   "&zero=[-]; zero",
   "&a=?a_outside;  a zero++ [&a= ?a_inside; a -] a",  # "?a_outside ?a_inside ?a_inside ?a_outside"
   "&test= &b=?b_test; b; &b=?b_top; b test b test",   # "?b_top ?b_test ?b_top ?b_test"
   "&2x(arg)=arg arg; 2x(?arg)",                       # "?arg ?arg"
   "&4x(arg4)=2x(arg4)2x(arg4); 4x(?4)",               # "?4 ?4 ?4 ?4"

   #and now for some more nasty things
   "&2x(arg)=arg arg; &4x(arg)=2x(arg)2x(arg); 4x(?4)", # "?4 ?4 ?4 ?4" nastier than expected (cf note #1)
   "&top(arg)=  &zut=arg; zut;  top(?arg)",    # "?arg"
   "&zombi(arg)=?zombi arg; zombi(&zombi=?inside; zombi)",  # "?zombi ?inside"
   "&thing(x)=&local(z)=x; local(+++); thing(?first) thing(?second)",  # "?first ?second" (cf note #2)
   "&a=?a; &test(a|b)=a b; test(?a_arg|a)", # "?a_arg ?a" and not "?a_arg ?a_arg": b evaluated in top context

   #standard things...
   "&if(then)= [ then [-] ];",

   # LEVEL 2
   "&2(m)=m m; &hello(n)=n(?hello); hello(2) ?and hello(2)",
   "&apply(x|y)=x(y); &what=?what; apply(2 | what)",
   "apply(2 | &temp=?temp; temp )",
   "&compose(f|g) = &f_g(x)=f(g(x)); f_g;",
   "&4=compose(2|2); 4(?4__)",  # ?4__ ?4__ ?4__ ?4__
   "&four_args(a|b|c|d)=a b c d; &three_args=four_args(?first);"
       "&one_arg=three_args(?second|?third); one_arg(?last)", # ?first ?second ?third ?last
   "&identity(x)=x; &APPLY=identity(apply); APPLY(2|?twice)", # ?twice ?twice
   "&identity(x)=x; identity(apply|2|?twice)",  # ?twice ?twice

   # level 2 - nastier... or would-be nastier:
   "&oh=?oh; &test=apply(2|oh); &oh=?oh2; ?ha identity(&oh=?inside; test) ?ah" # ?ha ?oh ?oh ?ah
   #"&xxx(x)=x(+); &recursive= xxx(2); xxx(recursive)"  -> BfRuntimeError
   #"&f(x)=x(f); &g(x)=x(g); g(f)"  -> BfRuntimeError: undefined g (in &g(x)=x(g))
   #"&f(f|x)=f(f|x); f(f|burps)", -> BfRuntimeError: recursion!!! _definitely_ nastier.

   # level 2 standard things
   "&0(t)=; &1(t)=0()t; &2(t)=t t; &3(t)=t t t; &4(t)=2(2(t)); &5(t)=4(t) t; &6(t)=3(2(t));"
   "&7(t)=4(t) 3(t); &8(t)=4(2(t)); &9(t)=3(3(t)); &10(t)=5(t t);",
   "&nn(x|y)= &nn_t(t)=x(10(t)) y(t); nn_t;",
   "&NN(x|y|t)=x(10(t)) y(t);"  # [nn] and [NN] are semantically identical
   "&out(n)=[-] n(+) .;  out(nn(7|2)) out(NN(10|1))"
       "&plus(x|y|t)=x(t)y(t); &outa(n)=out(plus(nn(9|6)|n)); &outA(n)=out(plus(nn(6|4)|n));"
       "outa(plus(10|2)) outa(nn(1|2)) outa(nn(1|5))"  # "Hello"

   # bug in parser: f(x)(y) was refused, except on top-level where it did not do
   #    the expected thing. "(y)" part probably just got skipped.
   "&f(g|x|y)=g(x)(y);",
   "f(f)(3)",
]
### missing feature: define local things at top-level (loop executed once)
### -> no so missing !
###   &local_block(block)=block;    local_block(&temp=...; temp)
###   &1x(x)=x;   1x(&temp=...; temp)

# note #1:
#   bug: callee environment (inside_env) was build from caller environment (outside_env);
#        it must be built from _declaration_ environment (macro_decl.env) instead.
#   This error caused infinite looping in "&4xx(arg)=2x(arg)2x(arg); 4xx(?4)"
#   for reasons I don't fully understand yet...
#   (_did_ it cause infinite looping ? or was this "infinite looping' just apparent ?)
# note #2:
#   corrected bug:
#   Who's the silly boy who declared that a given macro declaration
#   was always executed in the (semantically) same env ?
#   That's simply not true. In
#     "&thing(x)=&local(z)=x; local(+++);  thing(?first) thing(?second)"
#   "local"'s declaration is first executed with "&z=?first;" then with "&z=?second;".
# note #3:
#   recursion... how to avoid it (in the language definition, not necessarily
#      in this interpreter):
#   (1) forbid f to be used inside of f code without being to some extent closed
#   (2) static typing could detect and forbid recursive types
#       e.g. "&f(g|x)=g(g|x);" would have type 'g -> 'x -> 't with 'g = 'g -> 'x -> 't,
#       this last equation being forbidden. ('g cannot be equal to some complicated
#       expression where 'g appears. Of course 'g = 'g is admitted.)

class InteractiveInputOutput:
    def __init__(self):
        import sys
        self.cout = sys.stdout
        self.to_flush = 0

        self.input_string = ""
        self.input_ptr = 0

    def input(self):
        self.flush()
        while self.input_ptr >= len(self.input_string):
            #print "Enter some input for BFM:"
            inp = raw_input("BFM runtime input>")
            self.input_string = inp
            self.input_ptr = 0

        c = self.input_string[self.input_ptr]
        self.input_ptr = self.input_ptr + 1
        return c

    def output(self, c):
        if ord(c) >= 32:
            self.cout.write(c)
        else:
            self.cout.write("(%d)" % ord(c))
        self.to_flush = 1

    def flush(self):
        if self.to_flush:
            print
            self.to_flush = 0


_parse_debug = 0

top_io = InteractiveInputOutput()   #i/o for BF runtime
top_runtime = BfmRuntime(top_io.input, top_io.output)

if _testing_:
    library = test
else:
    library = library

for line in library:
    c = parse(line)
    if _testing_: print "<<<", str_sequence(c)
    top_runtime.execute_sequence(c)
    if _testing_: print

print "Final env:"
top_runtime.getCurrentFrame().dump()

welcome = """BrainFunctMacro top-level:
    "exit"   to quit
    "?"      for a list of all defined macros.
    "?xxx"   for the definition of macro &xxx;
    "??"     prints all macro definitions (might be long!);
    "help"   displays this message again
"""


def toplevel(initial_runtime = None, io = None):
    runtime = initial_runtime
    if runtime is None:
        runtime = BfmRuntime()

    # overwrite runtime input/output:
    if io is not None:
        #io = InteractiveInputOutput()   #i/o for BF runtime
        runtime.input_fn = io.input
        runtime.output_fn = io.output

    print welcome

    while 1:
        io.flush()
        line = raw_input("BFM> ");
        if line == "exit":
            break
        elif line == "?":
            print "Defined macros (type ?xxx for definition of macro &xxx;):"
            for name in top_runtime.getCurrentFrame().get_all_names():
                print name,
            print
        elif line == "??":
            top_runtime.getCurrentFrame().dump()
        elif line[:1] == "?":
            name = line[1:]
            try:
                value = top_runtime.getCurrentFrame().get_definition(name)
                print value
            except BfRuntimeError:
                print "macro &%s; is undefined." % name
        elif line == "help":
            print welcome
        else:
            try:
                rescue_frame = runtime.getCurrentFrame()

                c = parse(line)
                runtime.execute_sequence(c)

            except ParseError, exc:
                io.flush()
                print "Parse error:", exc.msg
            except BfRuntimeError, exc:
                io.flush()
                runtime.setCurrentFrame(rescue_frame)
                runtime.resetExecutionDepth()
                print "Runtime error:", exc.msg

    #end while
#end def toplevel

toplevel(top_runtime, top_io)
