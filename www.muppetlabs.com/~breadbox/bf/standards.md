Portable Brainfuck
==================

The detailed description of the language given in the page above is only
strictly accurate for the original Brainfuck compiler. Brainfuck has
many implementations, and some implementors have chosen to extend the
original Müller limits, sometimes in ways that make it difficult for a
Brainfuck programmer to write portable code.

In the absence of a more formal regulating standards body, I offer up my
own guidelines to programmers desiring to create either portable
Brainfuck programs or compatible Brainfuck implementations. These
guidelines are based on my observations of the range of existing
Brainfuck implementations, and should include just about every sane
implementation created as of this writing.

For the reader who is unfamiliar with standard standardese, I offer some
prefatory definitions. When something is said to be
implementation-defined, such as an environmental limitation or how a
program construct behaves in a certain situation, that means that a
given implementation can do pretty much anything (subject to any other
applicable constraints, of course), but that the implementation must
document its choice. (In the case of Brainfuck, however, many
implementors consider the source code to be documentation enough.) When
something is said to be undefined, however, that means that an
implementation in that situation can do pretty much anything at all
without violating any restrictions of this standard. (In other words, a
portable Brainfuck program should eschew all undefined behavior.)

Finally, note that comments in parentheses are informal; they are
offered merely as helpful clarifications, and do not impose any
requirements.

------------------------------------------------------------------------

The Unofficial Constraints on Portable Brainfuck Implementations
----------------------------------------------------------------

-   The actual size of the cell array is implementation-defined.
    However, the array shall always contain at least 9999 cells.
    (Allowing the size to be as small as a 4-digit number is done for
    the benefit of programmers writing interpreters in three lines of C
    code and the like.)
-   If a program attempts to move the pointer below the first array
    cell, or beyond the last array cell, then that program\'s behavior
    is undefined. (A few implementations cause the pointer to wrap
    around, but many, perhaps most, implementations behave in a manner
    consistent with a C pointer wandering off into arbitrary memory.)
-   The range of values a single cell can contain is
    implementation-defined. (The range need not be consistent, either:
    consider the case of a \"bignum\" implementation, whose cells\'
    ranges would be limited only by currently available resources.)
    However, the range of every cell shall always at least include the
    values 0 through 127, inclusive.
-   If a program attempts to either decrement the value of a cell below
    its documented minimum value, if any, or increment the value of a
    cell beyond its documented maximum value, if any, then the value in
    the cell after such an operation is implementation-defined. (Most
    implementations choose to let the value wrap around in a fashion
    typical to C integers, but this is not required.)
-   If a program attempts to input a value when there is no more data in
    the input stream, the value in the current cell after such an
    operation is implementation-defined. (The most common choices are to
    either store 0, or store -1, or to leave the cell\'s value
    unchanged. This is frequently the most problematic issue for the
    programmer wishing to achieve portability.)
-   If a program contains one or more unbalanced brackets, then the
    behavior of that program is undefined. (In fact, a number of
    Brainfuck compilers will crash during compilation itself.) (And no,
    I\'m not going to formally describe what \"unbalanced\" means here.
    You all know what it means.)

------------------------------------------------------------------------

Since I am not an actual formal standards body, I don\'t have a nice
pronounceable acronym that one could prepend to \"-compliant\" to form
an adjective to describe a conforming implementation. In lieu of this,
then, I hereby suggest that a Brainfuck implementation that is compliant
with all of the constraints listed here should be described as \"nice\".

------------------------------------------------------------------------

[[Brainfuck](http://www.muppetlabs.com/~breadbox/bf/)]{.small}\
[[Brian Raiter](http://www.muppetlabs.com/~breadbox/)]{.small}
