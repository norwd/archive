[Download
float.tar.gz](http://www.muppetlabs.com/~breadbox/pub/intercal/float.tar.gz)

The INTERCAL floating-point library
===================================

Background
----------

In [the INTERCAL
manual](http://www.muppetlabs.com/~breadbox/intercal-man/), section 8.4
offers the reader a handful of INTERCAL programming projects. They are
of widely varying difficulty (though none of them are particularly easy
\[though again arguably is no INTERCAL programming project\]). But by
the time I began to write INTERCAL code, most of the suggested projects
had already been completed. There was, in fact, only two left (one of
which was predicated on the other):

-   Compile a floating-point library, using 32-bit variables to
    represent floating-point numbers.
-   Use said library to program a set of Fast Fourier Transform
    functions.

So you see, I really had no choice in the matter. The only option open
to me was to write a floating-point library. And not only did it need to
provide the basic arithmetic operations including exponentiation, but in
order to implement FFT it also needed to supply the trigonometric
functions.

So, that\'s what I did.

One of the more minor obstacles to completing this task was that the
C-INTERCAL compiler, the only INTERCAL compiler generally available at
the time, had a hard limit of 1000 lines per program. The author (Eric
S. Raymond) had assumed, when he wrote it, that 1000 lines would be
sufficiently large to accomodate any single INTERCAL program likely to
be written, if not the total amount of INTERCAL code that would ever be
written. He, alas, was not a true INTERCAL programmer. The
floating-point library would ultimately require nearly twice that space
alone, never mind when added to an actual program. So in addition to the
floating-point library, I also contributed improvements to the
C-INTERCAL compiler to allow it to handle source files of arbitrary
size.

The timing for this work happened to be such that I was able to finish
all of the above in time for May 26th, 1997: the 25th anniversary of
INTERCAL. I thus coordinated to have the floating-point library, along
with the FFT program and the new version of the compiler, released along
with the improved compiler on that day.

As I stated at the time: \"INTERCAL stands a living testament to the
Turing-completeness Theorem.\"

Here follows the complete documentation for the floating-point library.

Summary of Routines
-------------------

`(5000)`

`:3 <- :1` plus `:2`

`(5010)`

`:3 <- :1` minus `:2`

`(5020)`

`:2 <-` the integer part of `:1`\
`:3 <-` the fractional part of `:1`

`(5030)`

`:3 <- :1` times `:2`

`(5040)`

`:3 <- :1` divided by `:2`

`(5050)`

`:3 <- :1` modulo `:2`

`(5060)`

`:2 <- :1` cast from a two\'s-complement integer into a floating-point
number

`(5070)`

`:2 <- :1` cast from a floating-point number into the nearest
two\'s-complement integer

`(5080)`

`:2 <- :1` cast from a floating-point number into a decimal
representation in scientific notation

`(5090)`

`:2 <- :1` cast from a decimal representation in scientific notation
into a floating-point number

`(5100)`

`:2 <-` the square root of `:1`

`(5110)`

`:2 <-` the natural logarithm of `:1`

`(5120)`

`:2 <-` *e* to the power of `:1` (the exponential function)

`(5130)`

`:3 <- :1` to the power of `:2`

`(5200)`

`:2 <-` *sin* `:1`

`(5210)`

`:2 <-` *cos* `:1`

`(5220)`

`:2 <-` *tan* `:1`

`(5400)`

`:1 <-` uniform random number between zero and one exclusive

`(5410)`

`:2 <- :1` times φ

`(5419)`

`:2 <- :1` divided by φ

Note: All of the above routines except `(5020)`, `(5060)`, `(5080)`,
`(5200)`, `(5210)`, and `(5400)` also modify `.5` as follows: `.5` will
contain `#3` if the result overflowed or if the arguments were out of
domain, `#2` if the result underflowed, `#1` otherwise. (See below for
details.)

Detailed description
--------------------

The INTERCAL floating-point library uses the IEEE format for 32-bit
floating-point numbers, which uses bit 31 as a sign bit (1 being
negative), bits 30 through 23 hold the exponent with a bias of 127, and
bits 22 through 0 contain the fractional part of the mantissa with an
implied leading 1. In mathematical notation:

> **N** = (1.0 + *fraction*) · 2\^(*exponent* − 127) · −1\^*sign*

Thus the range of floating-point magnitudes is, roughly, from
5.877472\*10\^-39 up to 6.805647\*10\^38, positive and negative. Zero is
specially defined as all bits 0. (Actually, to be precise, zero is
defined as bits 30 through 0 as being 0. Bit 31 can be 1 to represent
negative zero, which the library generally treats as equivalent to zero,
though don\'t hold me to that.)

Note that, contrary to the IEEE standard, exponents 0 and 255 are not
given special treatment (besides the representation for zero). Thus
there is no representation for infinity or not-a-numbers, and there is
no gradual underflow capability. Conformance with widely-accepted
standards was not considered to be a priority for an INTERCAL library.
(The fact that the general format conforms to IEEE at all is due to the
author doubting their ability to get anything done without being able to
lean upon some form of prior art.)

Here, for easy reference, are some common values as they would be
directly represented within an INTERCAL program:

  -------------------- -----------------
  Zero                 `#0$#0`
  One                  `#30720$#28672`
  Two                  `#0$#32768`
  One million          `#9280$#40480`
  One-half             `#28672$#28672`
  Square root of two   `#31757$#30509`
  *e*                  `#1760$#33742`
  π                    `#571$#35133`
  -------------------- -----------------

However, a more human-accessible representation of floating-point
numbers is made possible by the routines `(5080)` and `(5090)`. For this
representation, scientific notation is used with six digits of precision
after the decimal point. The seven digits of the mantissa are suffixed
with the two digits of the exponent. If the number is negative, a one is
prefixed (in the billions\' place), so there can be ten decimal digits
in all. Finally, if the exponent is negative, fifty is added. As is the
usually the case with scientific notation, the digit to the left of the
decimal point must be nonzero except for the case of zero itself. The
above may sound convoluted, but it is not nearly as confusing as it
perhaps should be. As an example, if you wished to enter the value of
the speed of light measured in centimeters per seconds squared, you
would type `TWO NINE NINE SEVEN NINE TWO FIVE ONE OH`. The INTERCAL
program would then call `(5080)` to transform this into the
floating-point number 2.997925e+10. The same value printed out with the
help of `(5090)` would appear as ccxcixD̅C̅C̅X̅C̅MMDX. Similarly, the value
-1.602189e-19 (the charge of an electron measured in Coulombs) would be
represented respectively as
`ONE ONE SIX ZERO TWO ONE EIGHT NINE SIX NINE` and mclxC̅C̅X̅V̅I̅I̅I̅CMLXIX.
Note that the negative sign on the exponent always translates to an L
between the fraction and the exponent when output.

The 16-bit variable `.5` is used by the floating-point library as an
error indicator. Upon return from most of the functions, `.5` will
normally be set to `#1` if the return value is valid. If `.5` is set to
`#2`, this indicates that the result of the function underflowed (that
is, the magnitude of the result is less than 2\^-127). If `.5` is set to
`#3`, this indicates either that the result overflowed (magnitude
greater than 2\^128), or that the arguments to the function were
illegal. The latter can occur for the following situations: division by
zero (either via division or modulus), negative root (either via square
root or a fractional power), and non-positive logarithm. Also, `(5070)`
will set `.5` to `#3` if the magnitude of the argument is greater than
2\^31, and `(5080)` will do likewise if given a bad number (e.g., if it
is greater than two billion).

It may be worth nothing that there are some cases in which an under- or
overflow can be recovered from with tolerable grace. The sign and
fraction bits of such a value will usually still be correct, and the
exponent bits will just be the lower eight bits of the true exponent:
that is, the true exponent plus or minus 256 as appropriate. If such a
value is passed to another function as is, and the return value from
that over- or underflows in the opposite direction, it is likely that
the final result can be trusted. Of course, this depends entirely on the
nature of the operations involved, and this paragraph should not be
taken as advice to pursue such approaches in general, just as this
document should not be taken as advice to make use of this library at
all. Note also that in the case of `(5110)`, the exponential function,
and `(5130)`, the power function, it is quite easy to request a
massively under- and/or overflowed result. In these cases the functions
in question exit early, and attempting to salvage something from such
results, with the possible exception of the sign bit, is pretty much
guaranteed to be fruitless.

`(5020)` is the integral partition function (equivalent to `modf()` in
the C library). Both return values are floating-point numbers, and both
have the same sign as the argument, such that `:2` + `:3` = `:1` while
keeping the magnitude of `:3` less than 1.

`(5060)` and `(5070)` are the \"type-casting\" functions. They translate
values to and from 32-bit two\'s-complement integers. `(5070)` truncates
any fractional amounts from its argument, and will signal an error if
the magnitude of the value requires more than 32 bits.

The trigonometric functions `(5200)`, `(5210)`, and `(5220)` will return
erroneous results when given very large arguments. At magnitudes around
8 million or so, the result is occasionally off by one bit. The errors
get progressively worse, so that with magnitudes in the neighborhood of
the quintillions and higher, the number is wholly inaccurate. However,
at magnitudes around 8 million, there is already a difference of over
20π between consecutive floating-point numbers, so it is hard to
conceive of a purpose for which improved accuracy would be useful.

In the descriptions for `(5410)` and `(5419)`, φ refers to the golden
ratio.

Internal routines
-----------------

A floating-point library involves a fair amount of mathematical
functionality to begin with, something that INTERCAL is not generally
mistaken for having. The floating-point library therefore has a number
of internal functions to provide it with some 64-bit arithmetic, among
other things. While these routines were designed specifically for
internal use, and in many cases one would be hard-pressed to find other
uses for them in their current form, it was felt that they were
nonetheless worth documenting. Besides providing a guide for anyone so
foolish as to examine the actual code, it provides a sort of \"itemized
bill\" that helps to justify the inordinate size of the library.

In the following list, the notation `:1:2` simply indicates that two
32-bit variables, in this example `:1` and `:2`, are being used to hold
a single 64-bit integer value. The notation `:1:2.1`, on the other hand,
indicates a kind of double-precision floating-point value, a format that
the library uses frequently when storing intermediate values. The two
32-bit variables hold the fraction bits, with no implied bits, and
ideally with the highest 1 bit at bit 55. The 16-bit variable holds the
exponent, but with a bias of 639 instead of 127. This is done so that
underflows do not affect the sign, which is also stored in the 16-bit
variable in bit 10. These intermediate values are rounded (to even),
truncated, and stored in a single 32-bit variable by the floating-point
normalization function, `(5600)`.

Finally, note that the numbers in the tables accessed by routines
`(5690)` through `(5693)` are generally tailored for the function that
applies them, and all of them use slightly different representations for
the values they encode.

Here are brief descriptions of the internal routines:

  ----------------------------------- -----------------------------------
  `(5500)`                            `:1:2 <- :1:2` plus `:3:4`\
                                      `.5 <- #0` if no overflow, `#1`
                                      otherwise

  `(5510)`                            `:1 <- :1` plus `:6,` where `:6`
                                      has at most one 1 bit\
                                      `:6 <- #0` on overflow, nonzero
                                      otherwise

  `(5519)`                            `:1 <- :1` minus `:6`, where `:6`
                                      has at most one 1 bit\
                                      `:6 <- #0` on underflow, nonzero
                                      otherwise

  `(5520)`                            `.1 <- .1` minus `#1`

  `(5530)`                            `:1:2:3:4 <- :1:2` times `:3:4`

  `(5540)`                            `:1 <- :1:2` divided by `:3:4`,
                                      with `:1:2` aligned on bit 63,
                                      `:3:4` aligned on bit 62, and the
                                      result aligned on bit 31\
                                      `.1 <-` the exponent of the
                                      quotient plus `#126`\
                                      `.5 <- #1` if the result should be
                                      rounded up, `#0` otherwise

  `(5550)`                            `:1:2.1 <- :1:2.1` modulo `:3:4.2`

  `(5560)`                            `:1:2 <-` two\'s complement of
                                      `:1:2`

  `(5570)`                            `:1:2 <- :1:2` left-shifted
                                      logically so that bit 63 is 1\
                                      `.1 <- .1` minus the no. of bits
                                      shifted out

  `(5580)`                            `:3:4 <- :3:4` shifted right
                                      arithmetically `.3` bits

  `(5590)`                            `:1:2 <- :1:2` shifted so that bit
                                      55 is the highest 1 bit\
                                      `.1 <- .1` plus or minus the no. of
                                      bits shifted\
                                      `.5 <-` the bits right-shifted out
                                      of `:1:2`, if any

  `(5600)`                            `:1 <-` the normalization of
                                      `:1:2.1`

  `(5610)`                            `:1:2.1 <-` the natural logarithm
                                      of `:1:2.1`

  `(5620)`                            `:1:2.1 <-` *e* to the power of
                                      `:1:2.1`

  `(5640)`                            `:1:2.1 <- :1:2.1` to the power of
                                      the two\'s-complement integer in
                                      `:3`

  `(5650)`                            `:1:2.1 <- :1` to the power of
                                      `:2`\
                                      `.5 <- #1` if the power is not
                                      real, `#2` otherwise

  `(5670)`                            `:1:2 <-` an angle between -π/2 and
                                      π/2 that has the same value for
                                      sine as `:1`, and stored in
                                      two\'s-complement, fixed-point
                                      form, with the one\'s position at
                                      bit 62\
                                      `.1 <- #1024` if the cosine of
                                      `:1:2` will have the opposite sign
                                      as the cosine of `:1`, `#2048`
                                      otherwise

  `(5680)`                            `:1:2 <-` the sine of `:1:2` in
                                      two\'s-complement, fixed-point\
                                      `:3:4 <-` the cosine of `:1:2`

  `(5690)`                            `;1 <-` a table of 32 significant
                                      bits of the numbers 10\^*i*, where
                                      *i* ranges from 1 to 39\
                                      `,1 <-` a table of exponents for
                                      the above powers of ten

  `(5691)`                            `;1 <-` a table of bit patterns
                                      representing ln(1 + 1/(2\^*i* −
                                      1)), where *i* ranges from -1 to
                                      -26

  `(5692)`                            `;1 <-` a table of bit patterns
                                      representing −ln(1 + 2\^*i*), where
                                      *i* ranges from -1 to -32

  `(5693)`                            `;1 <-` a table of bit patterns
                                      representing *arctan*(2\^*i*),
                                      where *i* ranges from 0 to -30
  ----------------------------------- -----------------------------------

Bibliography
------------

-   Knuth, Donald E.: *The Art of Computer Programming: Vol. 2
    (Seminumerical Algorithms)*, 2nd edition. Addison-Wesley, 1981.\
    This book provided the essential background, as well as algorithms
    for the basic arithmetic operations. Mention should also be made of
    Vol. 1, which provided an algorithm for the natural logarithm as a
    side note.
-   Koren, Israel: *Computer Arithmetic Algorithms*. Prentice-Hall,
    1993.\
    In addition to information on the IEEE standard, this book provided
    algorithms for the exponential and trigonometric functions.
-   Plauger, P. J.: *The Standard C Library*. Prentice-Hall, 1992.\
    This book provided assistance in designing the modulus and power
    functions, as well as other miscellaneous contributions.

\
[[INTERCAL](http://www.muppetlabs.com/~breadbox/intercal/)]{.small}\
[[Brian Raiter](http://www.muppetlabs.com/~breadbox/)]{.small}\
[[Muppetlabs](http://www.muppetlabs.com/)]{.small}
