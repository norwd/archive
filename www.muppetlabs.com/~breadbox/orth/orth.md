### Introduction

This document describes the Orthogonal language. It does not, however
explain why you would want to know this, as that would be a far more
difficult task. Let us just take it as read that you are willing to
entertain the notion that you might be interested, or else you wouldn\'t
be here.

Orthogonal, or rather the idea of a 2-dimensional language, first began
in the alt.lang.intercal newsgroup. In 1994 an enterprising [Jeff
Epler](mailto:jepler@herbie.unl.edu) created an interpreter for such a
language. In 1996 we discovered his work, and decided to build upon this
foundation.

The version you see here is basically the original language with a new
interpreter. For the most part this version of Orthogonal is fully
compatible with the previous version, although this is somewhat of a
moot point as the file format has completely changed. It is somewhat of
a moot point anyway, but you can expect us to ignore that fact, here and
throughout this document.

At some point in the future[¹](#note1) Orthogonal will undergo many
changes, and absolutely no attempt will be made to maintain much in the
way of backwards-compatibility. We can justify this by pointing out that
Epler\'s language was called Orthagonal, not Orthogonal, so this is
really an entirely different language. See? With that pathetic
rationalization behind us, let us turn to the description of the current
language.

### The Orthogonal Environment

When reading the following, it may help to think of Orthogonal not so
much as a computer language, but more as the assembly language for a
nonexistant chip - a very primitive, stack-based chip, with damn few
instructions (though strangely enough capable of writing to stdout).

The Orthogonal environment consists of two entities: the grid and the
stack. The grid is a two-dimensional memory space, where code and data
can be found. The stack is the more familiar one-dimensional object that
data is pushed to and popped from.

Available data types in Orthogonal include the 32-bit signed integer.
The 32-bit signed integer also completes the list of available data
types.

At the beginning of an Orthogonal program the stack is empty, the grid
contains the program being interpreted, and execution begins at the
origin \[0,0\] with a delta of \[+1,0\] (in other words, heading due
east). Thus after executing the instruction at \[0,0\], the interpreter
moves to \[1,0\], and then to \[2,0\], unless and until the program
changes the direction, or ends the execution with the `ret` instruction
(more on that below).

Also during startup, any command-line arguments are, at the
programmer\'s option, loaded into the grid in a horizontal row, one
character per cell. The default location is from \[0,255\] to
\[255,255\]; both the position and length of the row can be set by the
program (see \"Preprocessor Variables\" below). Each argument is
separated by a single zero value, and zeros pad out the cells to the end
of the row if there is leftover space.

Each cell in the grid can contain either a datum (one of the integers
mentioned earlier) or an instruction. When execution encounters a cell
containing an integer, the value is pushed onto the stack; in other
words, numbers carry an implicit push instruction. Besides specifying
numbers in decimal notation, hexadecimal can be used by preceding the
number with, of course, `0x`. Octal numbers can also be specified using
a preceding `0`, but who really uses octal anymore? I mean, come on.
Furthermore, numbers in the range of ASCII characters can be represented
by enclosing the character in single quotes, and the standard set of
backslash escape sequences (\'\\n\', et al.) is also available for
quoting non-graphic characters.

### The Orthogonal Instruction Set

The Orthogonal instruction set falls roughly into three categories:
operators, directives and the other ones. The operators all pop one or
more elements from the top of the stack and then push back to the stack
a result. The directives may also take values from the stack, but also
affect the direction of program execution. The other ones are basically
like operators, but with side effects.

  ------- ---------------------------------------------------------------------------------------
  `+  `   add the top two elements of the stack (and push the sum)
  `*  `   multiply the top two elements of the stack
  `-  `   subtract the top stack element from the second element
  `/  `   divide the top element into the second (i.e., S2 / S1)
  `%  `   divide the top element into the second and push the remainder
  `&  `   bitwise AND the top two stack elements
  `|  `   bitwise OR the top two elements
  `^  `   bitwise XOR the top two elements
  `!  `   push the logical NOT of the top element (0 `->`{.sample} 1, all else `->`{.sample} 0)
  `~  `   exchange the top two stack elements
  `@  `   duplicate the top stack element
  `$  `   discard the top stack element (i.e., pop-and-drop)
  ------- ---------------------------------------------------------------------------------------

  : The Operators

  ------- ---------------------------------------------------------------
  `L  `   set delta to \[+1,0\] (i.e., go west)
  `K  `   set delta to \[0,-1\] (north)
  `J  `   set delta to \[0,+1\] (south)
  `H  `   set delta to \[-1,0\] (east)
  `cw `   change delta from \[dx,dy\] to \[dy,-dx\] (i.e., clockwise)
  `ccw`   change delta from \[dx,dy\] to \[-dy,dx\] (counter-clockwise)
  `rev`   change delta from \[dx,dy\] to \[-dx,-dy\]
  `x  `   change current x-coordinate to the top stack element
  `y  `   change current y-coordinate to the top stack element
  `dx `   change the x value of the delta to the top stack element
  `dy `   change the y value of the delta to the top stack element
  ------- ---------------------------------------------------------------

  : The Directives

  ------- ----------------------------------------------------------------------------------------------------------------------
  `=  `   push the data at the grid coordinates given by the top two stack elements (i.e., push the contents of \[S1,S2\])
  `#  `   store the third stack element at the coordinates of the top two elements (i.e., \[S1,S2\] is set to S3)
  `?  `   test the top stack element, and if zero, skip over the next cell (i.e., add the delta twice to the current position)
  `c  `   output the top stack element as an ASCII character, or a newline if top element is zero
  `s  `   output stack elements as characters until a zero is encountered
  `d  `   output the top element as a number in ASCII format (i.e., itoa)
  `nop`   nothing happens (i.e., xyzzy)
  `ret`   end the program and return the top stack element to the OS
  ------- ----------------------------------------------------------------------------------------------------------------------

  : And the Other Ones

Cells that have not been set to contain anything remain undefined, and
it is an error to allow execution to enter an undefined cell, or to read
its contents with the `=` instruction (push cell contents). It is also
an error to attempt to push the contents of a cell containing an
instruction. (Setting the contents of an undefined cell, using the `#`
instruction, is on the other hand perfectly acceptable and even
encouraged.)

### The Orthogonal Program File Format

This is an excellent example of that ancient maxim that tells us that
words are equivalent to millipictures. Therefore, the following program
is the description of Orthogonal\'s file format:

     
    ; A hello world program in Orthogonal.
    ;
    [0,0]
    0   'd' 'l' 'r' 'o' 'w' ' ' ',' 'o' 'l' 'l' 'e' 'h' s   cw
                                                            0
                                                            c
                                                    ret 0   cw

Unlike most languages, whitespace is very important in an Orthogonal
source file. Note that each column is four characters wide. This is the
default setting, and it can be changed if desired, but four is wide
enough for all of the instructions and all integers in the range of -999
to 9999, which includes most of the useful ones. Spaces are not required
between adjacent cell contents, though admittedly some legibility can be
lost in their absences. (But do note also that the cell contents do not
have to be left-justified.) In the interest of keeping things terse, it
is considered acceptable, if a bit gauche, to leave off the closing
quote of a character value (with the exception of a quoted space
character, since that\'s just too ugly to allow).

Note also that the section is headed by its coordinates. An input file
can contain any number of such sections, allowing a programmer to
scatter a program\'s various components hither and yon.

Comments are introduced with a semicolon, and extend to the end of the
line. Comments can be inserted in the middle of a section, in a
section\'s right margin, and in fact pretty much anywhere. They are
disallowed only in a preprocessor command line, which gives us the
segueway we so desperately needed to move on to the next topic.

### Orthogonal Preprocessor Variables

The \":set\" preprocessor command allows one to create macro-style
variable names and generally avoid using magic numbers in the program
proper. Since the only available storage outside of the stack are grid
cells of arbitrarily chosen coordinates, magic numbers tend to be a fact
of life in Orthogonal.

The syntax is:

    :set <name> = <value>

where `<name>`{.variable} is the name to create, and
`<value>`{.variable} is the number to be assigned. (Or quoted character,
or what have you.) So, if the following lines appeared in a source file:

    :set ix = 12
    :set iy = 48

the code to decrement the contents of \[12,48\] could be written as:

    iy  ix  =   1   -   iy  ix  #

and in all likelihood would be.

There also exist a number of predefined variables, which can be used
and/or modified by the programmer to control the program parsing and
startup conditions.

The predefined variables and their semantics:

-   ORTHVER the version of Orthogonal being used (currently set to
    0x0002, indicating version 0.2)
-   COLSIZE the width of columns in the source file (default is 4)
-   TABSIZE how big a tabstop should be read as (default is 8)
-   ARGROW the y-coordinate of where to store the command-line arguments
    (default is 255)
-   MAXARGS the number of cells to devote to storing the command-line
    arguments, or zero to indicate no arguments should be stored
    (default is 256)

### lnvoking Orthogonal

An Orthogonal program is invoked as follows:

    orth [-t] [<orthogonal program> [command-line arguments]]

The optional -t argument runs Orthogonal in trace mode. \"-\" can be
supplied as the program name, or it can be omitted entirely, to have the
source file read from stdin.

Additionally, Orthogonal will also ignore the first line of a file if it
begins with `#`, essentially treating it as a comment line. This permits
the Orthogonal interpreter to be automatically invoked via the Unix `#!`
convention.

### Conclusion

If you are still confused, and need further explanation, I suggest you
go look at the sample programs. Really. There\'s nothing more I can do
for you here.

### Appendix: Differences Between Orthagonal and Orthogonal

(First and foremost, of course, is that Orthagonal used a non-graphic
source file format, but actually this section discusses differences
between the languages proper, rather than how one gets a program into
the interpreter.)

Orthagonal had a fixed-size grid of 256x256. Orthogonal\'s grid, on the
other hand, is an unbounded quarter-plane (well, unbounded except for
available memory). This change is the source of the biggest
incompatibility between the two languages: Orthagonal\'s fixed grid
allowed for wrap-around. That is, if a westbound execution reached
\[255,4\] the next instruction would come from \[0,4\]. In Orthogonal,
however, the next instruction would be taken from \[256,4\]. We felt
that the chances of someone having written a program that was fatally
dependent upon the wraparound feature were miniuscule.

Upon initialization, Orthagonal\'s grid was initialized with zero
values; thus in Orthagonal one never encountered undefined cells.

Orthagonal only accepted a single argument on the command line, which
was stored in a row always starting at \[0,255\]. Also, the cells were
not padded out with zeros to the end of the row. Orthogonal accepts any
number of command-line arguments, and allows the source file to define
where, and how many bytes, should be stored, and always uses the entire
space.

Orthagonal\'s stack was also limited to 256 elements. Orthogonal\'s
stack is unbounded.

Finally, Orthagonal contained a bug in regard to the c instruction
(output character). If the top stack element was zero, Orthagonal would
print a newline as advertised, but in all other cases it would throw
away the top stack element and output the next element. This bug has
been corrected in Orthogonal. This fact can be used to create
dynamically portable code. For example:

    0   10  10  c   !   ?   1

After printing a newline, the above code will place a one or a zero on
the stack if Orthagonal or Orthogonal, respectively, is the interpreter
in use. One can then store this value somewhere, and use it later to
select different sections of implementation-dependent code.

### About the Author

Please send bug reports and other Orthogonally-related material to
[Brian Raiter](mailto:breadbox@muppetlabs.com).

------------------------------------------------------------------------

[¹]{#note1} The design and subsequent implementation of the successor
language was originally planned to begin immediately following the
completion of testing of the current version. However, said testing
phase has long since reached completion, and it must be acknowledged
that progress on the next design phase remains at the cocktail-napkin
state at which it has been since the differences of opinions regarding
certain language aesthetics between certain programmers reached certain
discordant apexes. Names will of course not be named, but it is
unarguable that a few purists are going to have a hard time clinging to
their precious ideals when the research grants dry up and they are
forced to fend for themselves out in the cold and unforgiving pragmata
that comprise the reality in which the rest of us manage to get real
work accomplished.
