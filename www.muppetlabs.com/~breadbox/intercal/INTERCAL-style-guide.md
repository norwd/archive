Google INTERCAL Style Guide
===========================

Introduction
------------

Historically, INTERCAL has not been widely used at Google, or anywhere
else. Recent events, however, have made it expedient to put together a
style guide for INTERCAL programming (in much the same way that building
a wall with bags of sand when the levee breaks is expedient).

If you\'re looking for an introduction to using INTERCAL, you\'ve come
to the wrong place. This should come as no surprise. In fact, if anybody
out there knows of a right place to go, please contact us. In the
meantime, however, you can amuse yourself with [the original
manual](http://www.muppetlabs.com/~breadbox/intercal/intercal.txt).

The rules below are not guidelines or recommendations, or even
teleological inferences, but strict rules. *You may not disregard the
rules listed below* unless they don\'t apply to you in the first place.

If you have questions about these guidelines, you are almost certainly
not alone.

Coding Standards
----------------

### Spacing and Formatting

INTERCAL has a standard formatting style that is widely used.
Unfortunately it is at odds with the formatting guidelines in other
Google style guides. Adhering to the general philosophy that a
compromise should leave no one happy, the following rules have been
selected.

-   Line labels should always begin at column zero.
-   The `DO` should begin at column eight (whether or not it is preceded
    by a label, of course). Code proper should thus begin at column
    eleven.
-   If the `DO` is replaced by a `PLEASE`, then it should begin at
    column four, so that code still begins at column eleven. Please note
    that this means that you should not use `PLEASE` with a line label.
    Theoretically this could present a problem with label-heavy code,
    but until it does stop whining about hypothetical situations.
-   If the statement is longer than one line, any and all continued
    lines should be indented to column eleven.

#### Tabs

Tabs are universally used in INTERCAL source code, but try telling that
to anyone here. Jerks. Just replace the leading tabs in your source code
with eight spaces before submitting your code.

#### Line Breaks

Line breaks should always be placed to the right of a binary operator.
Other things being equal, prefer to place the break after a higher-level
operator rather than a heavily nested one. (Some people also prefer to
place line breaks following an interleave over a select, but this is not
required.)

Here is an illustrative example.

**Bad:**

            DO :3 <- '"'"'"'".1$':1~#32768'"~"#1109$#1"'$':1~#128'"~#2735'$':1~"
               #546$#0"'"~"#43679"'$':1~"#1365$#0"'"~"#1023$#63"'$'"'"'".1$#0
               "~#34959'$':1~"#0$#1170"'"~#11007'$':1~"#0$#2925"'"~"#2005$#255"'
      

**Good:**

            DO :3 <- '"'"'"'".1$':1~#32768'"~"#1109$#1"'$':1~#128'"~#2735'$':1~
               "#546$#0"'"~"#43679"'$':1~"#1365$#0"'"~"#1023$#63"'$'"'"'".1$#0"~
               #34959'$':1~"#0$#1170"'"~#11007'$':1~"#0$#2925"'"~"#2005$#255"'
      

**Better:**

            DO :3 <- '"'"'"'".1$':1~#32768'"~"#1109$#1"'$':1~#128'"~#2735'$
               ':1~"#546$#0"'"~"#43679"'$':1~"#1365$#0"'"~"#1023$#63"'$
               '"'"'".1$#0"~#34959'$':1~"#0$#1170"'"~#11007'$':1~"#0$#2925"'"~
               "#2005$#255"'
      

#### Internal Spaces

Do not put spaces inside of expressions. Sometimes people get this idea
that spaces will help make a complex expression slightly less opaque. Ho
ho ho. The truth is, it doesn\'t help enough to be worth the bother, and
everyone is used to seeing no spaces in expressions by now. Seriously,
just let it go.

#### Grouping

Outermost sparks/rabbit-ears must match on either side of a binary
operator. That is, your code shouldn\'t contain expressions that look
like this:

**Bad:**

            DO .5 <- ":1~'#32768$#0'"$':2~"#32768$#0"'
      

Fix it to look like this:

**Good:**

            DO .5 <- ":1~'#32768$#0'"$":2~'#32768$#0'"
      

Having your code always adhere to this rule while you\'re writing it is
a pain, yes, but it\'s nothing compared to the pain of reading other
people\'s code that doesn\'t.

#### Line lengths

The general standard in Google code is to restrict lines to eighty
columns. It is recommended that INTERCAL code be restricted to
seventy-two columns, so that the last eight columns can be used to punch
sequence numbers. If you think that\'s a perfectly idiotic idea, then
you are welcome to use eighty columns, on the condition that if anybody
drops a deck of punch cards containing your code, you\'re the one who
has to put it all back in sequence again. You want to sign up for that?
Yeah, didn\'t think so.

### Naming Conventions

Naming rules are very important in maintainable INTERCAL code, due to
the lack of local variables or local labels or really any kind of
scoping whatsoever. We follow the general practices of the INTERCAL
community, with the following additional rules.

#### Line Labels

-   Four-digit line labels are reserved for general-purpose libraries
    that are used throughout the INTERCAL community. If you are
    introducing a new library, and you think it should be in the
    under-ten-thousand set, you will need to present your case to the
    style committee and get signoff by two-thirds of the people present,
    assuming quorum has been satisfied. (Note: assuming the number of
    committee members is stored in `.1`, the number of people required
    to satisfy quorum is `'V".1~#65534"$"!1~.1'~#65534"'~'#0$#65535'`.)
-   Five-digit line labels are reserved for use by all other libraries.
-   Line labels in executables (i.e. non-library code) should all have
    from one to three digits.

Generally, you should try to keep close numbers near each other in the
code, at least initially. Obviously this state cannot always be
preserved as the code is revised over time, so this guideline is mainly
an attempt to stave off the inevitable.

In addition to the above rules, you should always use composite numbers
when writing new code. Prime numbers are reserved for use by other parts
of the code to fall back on when they run out of numbers in their
designated block.

#### Variable Names

-   Global variables in libraries should be in the same general range as
    their line labels.
-   Likewise, executables should generally not use variable names with
    four or more digits (except of course when accessing a variable
    provided by a library).
-   As a general rule of thumb, a variable name\'s cardinal value should
    roughly correspond with its scope --- e.g. a widely used global
    variable should be assigned a number of relatively low magnitude.
-   `.5` is reserved as an error return flag. Don\'t use `.5` for other
    purposes in your code. This should go without saying.
-   The other one-digit variable names are reserved for passing
    arguments to routines.

If you are writing a routine that needs to accept more than eight
arguments of one type, consider using stashed values instead. Failing
that, consider packing one or more pairs of 16-bit values into 32-bit
values. Failing that, consider giving up and letting someone else deal
with writing that stupid routine. Are you sure that you really need that
routine? Maybe it can be put off until version two.

While we\'re on the subject of variable names, you should always keep
the list of variables in `STASH` and `RETRIEVE` statements in sorted
order. Sort by variable type first, then by the name\'s cardinal value.
For example:

        PLEASE STASH .1 + .2 + .3 + .4 + .610 + :3 + :101 + ,44 + ;1
      

Ideally, variable lists should also be sorted when they appear in
`READ OUT` and `WRITE IN` statements. However, this may sometimes
require renaming variables throughout the entire program, and/or
modifying your application\'s user interface, so regretfully this is not
an absolute requirement. Your peers may judge you if you don\'t, though.

### Comments

Comments should always begin with `DO NOTE`, unless they begin with
`PLEASE NOTE`. Remember that comments take up space in compiled INTERCAL
programs, and furthermore they take up processing time if execution
passes through them. For these reasons, *keep comments to a minimum, and
never put comments inside of optimized INTERCAL code*. Ideally all of
your comments will lie outside of the path of execution.

For libraries, comments can appear directly above each entry point
(unless of course the previous routines falls through, in which case
move it somewhere else and add an explanation).

Source code files should include a comment block that provides a
copyright statement, in the following form:

            DO NOTE COPYRIGHT MMVIII GOOGLE INCORPORATED
      

Other information such as the license boilerplate can be included if you
really think it\'s necessary. (Remember: this is INTERCAL. Does the
license really matter?) Since a header block would always get executed,
please use footer blocks instead, and place the comment at the bottom of
the file.

Do not write comments in lowercase. Lowercase in INTERCAL source code
looks really weird. Just trust us on this one.

Finally, please remember to *always* double-check your comments to make
sure that they don\'t contain an embedded `DO`. If you find such, reword
the comments as necessary to remove it. An embedded `PLEASE` has the
same problem: If you find an embedded `PLEASE` in your comment, reword
it to be less ingratiating.

### Internationalization

Although UTF-8 is in wide use these days, not everyone is equally
comfortable in editing code with nonstandard characters. Because of
this, you should use the pedestrian ASCII replacement `$` to interleave,
in place of the original `¢`. Likewise, you should use `?` in place of
`∀`. (And do *not* use the trigraph of `V -` with a backspace character
inbetween, as this is not portable. Although admittedly it does look
really nice when you print your source code on a daisy-wheel printer.
Okay, you can use the trigraph if you own a daisy-wheel printer, but for
everyone else it\'s off limits.)

If you\'re creating input files for running unit tests of INTERCAL code,
please keep your input numerals in English. If a significant fraction of
engineers on your team are familiar with Basque or Sanskrit, then you
can consider relaxing this requirement. (On the other hand, feel free to
use either `NINE` or `NINER` as the mood strikes you.)

Language Features
-----------------

### Using `!` as an abbreviation for `'.`

[Con:]{.point} Use of this abbreviation makes it harder to grep for
16-bit variables. It\'s irritating to deal with when one has to add
another enclosing group in an expression and the sparks and rabbit-ears
have to be swapped for each other.

[Pro:]{.point} The abbreviation is already used widely if not
universally. Shorter expressions means shorter statements.

[Decision:]{.point} The abbreviation is too familiar to INTERCAL
programmers, and its use is therefore not just permitted but required.

### Eliminating nonessential grouping in expressions

[Con:]{.point} Allowing extra groups sometimes allow you to avoid having
to exchange all the rabbit-ears in a subexpression with sparks (and vice
versa) when editing code.

[Pro:]{.point} Large expressions already have too many groups; allowing
even more just makes code difficult to read.

[Decision:]{.point} Adding extra groups is like asking for extra dioxin
in your fillet of sole. Bite the bullet and edit those subexpressions.
Yes, that means you must suffer so that we don\'t have to. It\'s called
life, okay?

### Using line abstention

[Con:]{.point} It\'s not always obvious when a routine is making use of
line abstention, confusing the casual reader.

[Pro:]{.point} Several familiar idioms are based on line abstention,
such as those that appear in the standard library.

[Decision:]{.point} Line abstention is permitted, but you should strive
to have the `REINSTATE` statement follow as closely as possible.
Libraries should never leave an abstention in effect between calls,
unless the alternative would be to introduce more global variables.

### Using gerund abstention

[Con:]{.point} The effects of gerund abstention cannot be contained: it
is necessarily global, potentially affecting all code in the main
program and any libraries in use. It also interferes with line
abstention, which is not always obvious to the programmer if line
abstention is being used in one or more libraries.

[Pro:]{.point} Watching someone else try to track down a bug caused by
gerund abstention is *hilarious*.

[Decision:]{.point} Do you really need to ask? For crying out loud,
don\'t use gerund abstention! Unless you\'re writing an executable and
your code makes no further calls to any library routines, that is. Only
in that specific situation is it okay to use. Oh, and only as long as
you aren\'t also making use of line abstention, or if you are you can
verify that it doesn\'t interact with your use of gerund abstention. Or
at least not in any unexpected way --- if it interacts in a way that you
want it to, then that\'s okay, I suppose. Oh, what the heck. If it
works, use it.

### Embedding messages for fatal errors as syntactically incorrect statements

[Con:]{.point} Taking advantage of INTERCAL\'s feature of displaying
syntax errors when encountered at runtime is a klugey way to display
error messages, and potentially confusing to users who are unfamiliar
with the practice.

[Pro:]{.point} Displaying messages in the proper way is such an
incredible pain in the neck.

[Decision:]{.point} Let\'s face it. If we didn\'t permit this practice,
INTERCAL programs wouldn\'t have any error messages.

### Using `COME FROM`

[Con:]{.point} `COME FROM` is a nonstandard extension of the language.
It is a late addition, and there is no guarantee that it will remain
part of the language going forward. It also arguably goes against the
philosophy of the core language as it was originally defined.

[Pro:]{.point} `COME FROM` is unlikely to be removed from any existing
or future compilers, seeing as it has ironically become the most
well-known feature of the language. It also relieves pressure on the
`NEXT` stack, which has a hard limit of seventy-nine entries.

[Decision:]{.point} `COME FROM` is permitted throughout Google, although
you should avoid it if you are concerned about portability to the
Princeton compiler.

### Using non-standard features

[Con:]{.point} INTERCAL extensions such as threading and operator
overloading are non-standard and poorly tested, and may therefore have
broad unforeseen side effects.

[Pro:]{.point} INTERCAL extensions such as threading and operator
overloading are non-standard and poorly tested, and may therefore have
broad unforeseen side effects.

[Decision:]{.point} Undecided. Use your best judgement.

### Setting `.5` to `#2`/`#3` instead of `#1`/`#2`

[Con:]{.point} This use is nonstandard, and some may therefore find it
non-idiomatic. It requires an extra level of nesting, which can impede
performance.

[Pro:]{.point} The newer idiom often allows branching to be accomplished
with much simpler expressions. Also, \"performance\"? Give me a break:
it\'s INTERCAL.

[Decision:]{.point} Yeah, come on. Do you even understand the question?
Be honest. If you can explain the issue to me in one sentence, then
you\'re already an experienced INTERCAL programmer and you don\'t need
to consult this guide for assistance. In fact, there\'s a non-trivial
probability that you helped write this.

Some General Guidelines
-----------------------

### Short Routines

To the extent that it is feasible, routines should be kept small and
focused. It is however recognized that long routines are sometimes
appropriate, so no hard limit is placed on routine length. If you\'re
writing a routine and it exceeds 700 lines or so, think about whether it
can be broken up without introducing a herd of new global variables.

### Short Statements

Long expressions can take the INTERCAL novice a day or two to mentally
work through, and thus should be avoided when possible. Where possible,
try to keep your statements under 512 characters.

### Consistency

Above all, *be consistent*. If you\'re editing code, take a few hours to
look at the code around you and understand its style. If they always use
rabbit-ears for their outermost group, you should too. If they always
prefix `RESTORE` statements with `PLEASE`, you should do the same. If
they have internal spaces in their expression, you should go through the
file and remove them, and then look to see what other files they might
have edited and fix those as well.

The point of having style guidelines is to have a common vocabulary of
coding, so people can concentrate on what you\'re desperately trying to
accomplish, rather than how. We present global style rules here so
people know the vocabulary. But local style is also important. No, it
won\'t help, not really. But do it anyway. I\'m serious. Do it. Do it or
I\'ll come find you and beat you like a tambourine.

When to use INTERCAL
--------------------

Never. What are you, high?

------------------------------------------------------------------------

Revision XLVIII\
*Brian Raiter*
