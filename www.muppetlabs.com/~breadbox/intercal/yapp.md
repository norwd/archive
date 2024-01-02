[Download
yapp.tar.gz](http://www.muppetlabs.com/~breadbox/pub/intercal/yapp.tar.gz)

yapp
====

yapp stands for \"yet another program printer\", or \"yet another
printing program\", or maybe \"yet another printer printer\". Yeah,
probably \"yet another printer printer\". What yapp does is print out
programs that print out. That is, yapp takes whatever is piped into its
standard input, and produces on its standard output the source code for
an INTERCAL program that will, when compiled, produce the original
output.

Since producing output in an INTERCAL program calls for quite a few
lines of code just to store the character data in an array (see, for
example, beer.i), yapp attempts to minimze the size of the programs it
generates. The most important of these attempts is the fact that the
character data is actually stored four characters at a time, in a
32-bit, or hybrid, array. After this array has been filled in (which
usually is the vast majority of the generated program), a 16-bit, or
tail, array is filled with the unpacked character data. After the latter
array is output, the remaining lines print any leftover characters (if
the original input size was not evenly divisible by four) and exit.

Other attempts to reduce size made by yapp are leaving out whitespace,
and avoiding use of the system library.

Here is an example of what yapp\'s output looks like. The parts that
change depending on the input data are marked with curly braces.
Whitespace has been added in a mostly-futile attempt to attain
legibility.

            DO (9) NEXT
            DO ;1 <- .4~#65532
            DO ,1 <- .4
            DO .1 <- #0
            DO ;1SUB#1 <- {data}${data}
            DO ;1SUB#2 <- {data}${data}
            PLEASE ;1SUB#3 <- {data}${data}
            DO ;1SUB#4 <- {data}${data}
                    *
                    *
                    *
            PLEASE ;1SUB{N/4} <- {data}${data}
            PLEASE COME FROM (1)
            DO .2 <- .1
            DO .3 <- #4
            PLEASE COME FROM (3)
            DO .5 <- '?".1~.3"$#1'~#3
            DO .1 <- '?.1$.3'~'#0$#65535'
            DO (4) NEXT
    (3)     DO .3 <- !3$#0'~'#32767$#1'
    (4)     DO (5) NEXT
            PLEASE FORGET #1
            DO :1 <- ;1SUB!1~#65532'
            DO ,1SUB"!2$#1'~'#65532$#3'" <- :1~'#43690$#0'
            DO ,1SUB"!2$#2'~'#65532$#3'" <- :1~'#21845$#0'
            DO ,1SUB"!2$#3'~'#65532$#3'" <- :1~'#0$#43690'
            DO ,1SUB.1 <- :1~'#0$#21845'
            DO .5 <- '?"'#65535~"'?.4$.1'~'#0$#65532'"'~#1"$#1'~#3
    (1)     DO (2) NEXT
    (2)     DO (5) NEXT
            PLEASE FORGET #1
            DO READ OUT ,1
            PLEASE GIVE UP
    (5)     PLEASE RESUME .5
    (9)     DO .4 <- {N}
            PLEASE RESUME #1

The first lines call the routine at `(9)`, which does nothing but
initialize `.4` with the size of the input (indicated by `{N}`). The
reason for this being a routine is that yapp does not know what this
number is until it has already generated the lines at the top of the
program, so it has to delay inserting this information until the end.
The value in `.4` is then used to initialize `,1` and `;1`, the latter
being one-fourth as large. Our counter variable, `.1`, is also set to
zero.

The next lines fill `;1` with the character data representing the input
to yapp, four characters in each array element. These lines represent
yapp\'s real work. Everything besides these lines and the line labelled
`(9)` are the same for every input. (Note: this is assuming that the
size of the input is a multiple of four. When this is not the case, a
few more lines are added in to directly output the leftover characters.)

The `COME FROM (1)` marks the top of the loop that translates the
contents of `;1` into `,1`. After the counter value in `.1` is saved in
`.2`, the `COME FROM (3)` begins the inner loop of the modified
increment routine. Note that this routine is incrementing by four
instead of one. This is because `.1` is indirectly serving as the index
into `,1`, as well as the index into `;1`. Since INTERCAL arrays are
one-based, the index needs to be stored in `.2` before being
incremented. The bottommost bits of `.2` can then be twiddled to index
three of the four `,1` elements to be initialized, and the value in `.1`
gives the fourth element. Shifting `.1` right two bits also gives the
index into `;1`.

The loop continues until `.1` is equal to `.4`, at which point `,1` is
filled and can be output.

\
[[INTERCAL](http://www.muppetlabs.com/~breadbox/intercal/)]{.small}\
[[Brian Raiter](http://www.muppetlabs.com/~breadbox/)]{.small}\
[[Muppetlabs](http://www.muppetlabs.com/)]{.small}
