> **quine** /kwi:n/ *n.* \[from the name of the logician Willard van
> Oman Quine, via Douglas Hofstadter\] A program that generates a copy
> of its own source text as its complete output.
>
> (from the [Jargon
> File](http://www.catb.org/~esr/jargon/html/Q/quine.html))

[Download
quine.i](http://www.muppetlabs.com/~breadbox/pub/intercal/quine.i).

quine.i dissected
=================

### Quines and INTERCAL

A basic feature of any quine is that it must have some chunk of data
which is output twice: once as code, and once as data (i.e., itself). In
a language that has identical representations for code and data, such as
Lisp, creating this data can be relatively straightforward. In a
language with powerful and terse string-manipulation capabilities, such
as Perl, the data can be very small.

And then we have INTERCAL. Not only does INTERCAL have no concept of
\"data-as-code\", it has no strings, as such. It quickly becomes clear
that a large part of any INTERCAL quine will have to consist of many
numbers to be output as the characters of the source code. The largest
INTERCAL variable is the 32-bit integer, into which four characters can
be interleaved, and then later unpacked and stored in an array to be
output. Since there is no way to assign a value to more than one
variable per statement, that adds up to a lot of statements.

### Earlier INTERCAL Quines

The first INTERCAL quine I ever created was in February of 1997, and it
was 18871 bytes long. It contained 644 statements, of which 530 were
devoted to initializing a hybrid array. The next section of the program
was the part that output these 530 lines of source code, and consisted
of roughly 75 lines itself. (Much of those lines were for the routine to
output a number in ASCII characters.) The remaining section created a
tail array of 2120 elements, into which the interleaved characters in
the hybrid array were separated out and stored, and then a single
`READ OUT` brought the program to completion.

Having actually completed a successful INTERCAL quine, I then began to
wonder about how to go about making it smaller. At first I concentrated
on tightening up the code, reasoning that any savings would shrink the
size of the array as well. However, I soon realized that the routines
were already pretty skeletal, and there wasn\'t much I could do in that
direction. (Although much later I would revise my opinion on that
score.) That left me with the option of making the data itself more
compact, and using slightly larger code to produce the actual
characters. It didn\'t take long before the idea of using Huffman
compression came to mind. Huffman compression is almost ideal for this
task, since all the real work is up front in the encoding stage, and
specifically in building the character translation table. The actual
decoding process can be done in two lines of (obfuscated) C, once the
binary tree is reconstructed, and mainly involves bit-twiddling, an
activity that INTERCAL excels at (relatively speaking).

My first successful quine with Huffman compression was 11323 bytes long,
completed in May 1997. In November 1998 I went on a protracted campaign
of making the program shorter, and eventually released a version that
was a mere 9130 bytes. This quine consisted of 412 statements, of which
292 statements initialized a hybrid array. This array contained the
binary tree defining the Huffman code in its first 48 elements, with the
remaining 244 elements being the encoded \"bitstream\".

In August 2003, I picked up the quine again and worked on making it
smaller still. I made a modification to the Huffman compression wherein
a given encoded symbol could automatically imply some number of bits to
implicitly follow it. (Thus, for example, because the character `D` was
always followed by an `O` character, all but the last bit of the code
for `O` could be dropped from the bitstream.) This along with several
reductions of the INTERCAL code itself allowed me to produce a quine
that was 6758 bytes in size. This quine consisted of 323 statements,
with a hybrid array of 211 elements: 41 for the Huffman tree, and 169
for the bitstream.

By this point I had become aware of the large amount of redundancy in
the INTERCAL code, which even my variant Huffman compression couldn\'t
take advantage of. However, switching to a more powerful compression
scheme seemed hopeless. The INTERCAL routine that decompressed the
Huffman-encoded bitstream was extremely terse. A more powerful
compression scheme would be counterbalanced by requiring a larger amount
of code to do the decompression. I looked around for compression schemes
that allowed for trivial decompression algorithms, and eventually found
one, called \"Re-Pair\".

### Re-Pair Compression Overview

Re-Pair is short for \"recursive pairing\". (The name comes from a
paper, \"Offline Dictionary-Based Compression\", by N. Jesper Larsson
and Alistair Moffat. The term \"byte pair\" encoding is also sometimes
seen.) Re-Pair compression uses a very simple coding scheme, in which
frequently-occuring pairs of symbols are replaced by a single symbol,
previously unused. A dictionary is thus created matching pairs of
symbols to new symbols. Note that either or both of the symbols in the
pair might themselves be dictionary entries. In this manner, long
repeated sections can be encoded.

The simplest approach for encoding a stream in this manner is as
follows:

1.  Scan the plaintext and find the most frequently-occuring pair of
    symbols.
2.  Replace the chosen pair everywhere it appears in the plaintext with
    a single new symbol.
3.  Append the encoding of the pair as the new symbol to the dictionary.
4.  Repeat, until no pair of symbols occurs more than once in the
    plaintext.

There are more sophisticated approaches, of course, but for short
strings this greedy algorithm usually works as well as any other.

Decompressing a symbol from the compressed stream can be done with a
simple recursive procedure:

1.  Look up the symbol in the dictionary.
2.  If the symbol does not have an entry, output the symbol directly.
3.  Otherwise, decompress the left-hand symbol in the entry, and then
    decompress the right-hand symbol in the entry.

The main drawback of this scheme is that compression is slow, and
requires a fair amount of memory.

### The Current INTERCAL Quine

The INTERCAL quine presented here, written on 30 June 2004, is 3629
bytes long. The Re-Pair compression scheme is the main reason for the
improved compactness over previous quines. Also, the program\'s routines
were completely rewritten in order to make the source more amenable to
Re-Pair compression. Other techniques for shrinking the total size
include juggling the assignment of dictionary index values so that the
compressed string would require fewer characters when represented as
decimal values in the source code, and doing a heuristic search for a
set of line labels that maximized overall compression.

------------------------------------------------------------------------

The following is a detailed description of the quine program. Note that
the lines of code quoted here have been re-formatted for legibility; in
the program, they are completely bereft of whitespace.

As always when analyzing a quine, there are two possible incarnations of
the program to consider. One is the program that is executing, the other
is the program that is being output. From the latter point of view, the
program comes in three sections. The first section creates a hybrid
array, the second section initializes the array\'s elements, and the
third section contains everything else. The first section consists of a
single statement, and is output directly at the end of the
initialization routine. The second section is output by reconstructing
the initialization statements from the array values. The third section
is output by decompressing the bytestream stored in the array.

Here are the first two sections of the program:

            DO ;2 <- #255
            DO ;2SUB#1 <- #23948$#3181
            DO ;2SUB#2 <- #2568$#53882
            DO ;2SUB#3 <- #8776$#4650
            DO ;2SUB#4 <- #1260$#40490
        [ ... skipping 99 lines ... ]
            DO ;2SUB#104 <- #46820$#8021
            DO ;2SUB#105 <- #14955$#6781
            DO ;2SUB#106 <- #3484$#38981
            DO ;2SUB#107 <- #62208$#0

In order for the dictionary to be simple to store and consult, the quine
uses byte values above 128 for dictionary symbols. Values below 128 are
automatically treated as ASCII character values. Because output values
are bit-reversed, this translates into: even values represent ASCII
characters, odd values represent dictionary entries.

The dictionary is stored in the first 63 elements of the hybrid array,
with two entries per element. Since INTERCAL arrays don\'t have a zero
element, only 126 dictionary entries are available. Entries for symbols
129 through 191 are stored in the top 16 bits of each array element, and
entries for symbols 193 through 255 are stored in the bottom 16 bits.
Each 16-bit value in turn contains two 8-bit symbol values, the
left-hand symbol being in the top 8 bits.

The other 44 array elements comprise the bytestream that, when
decompressed, recreates the program\'s third and final section.

Note, by the way, that none of the above lines begin with `PLEASE`. All
of the quine\'s politesse is packed into the rest of the program.

The final element of `;2` is special in two ways. First and most
visibly, it is the only entry that has all zero bits in the interleaved
right half of its value. Second, it is the only entry that contains a
zero byte. That is to say, when the 32-bit entries are separated into
four sequential 8-bit values, this is the only entry that contains an
octet equal to zero. These two different \"zeroes\" are each used as
sentinels to indicate the end of the data. The former zero is used when
outputting the second section, and the latter zero is used when
outputting the third section.

The fact that `;2` is created with 255 elements when it only uses 107 is
due to a minor optimization, which is explained below.

Having dispensed with sections one and two, it\'s time to examine
section three. This is where the actual program is. To start, let\'s
look at the subroutines. There are five main subroutines:

`(4)    ` Call `(1001)`.\
`(24)   ` Print the (bit-reversed) character in `.2`.\
`(1)    ` Print `.1` as a decimal number.\
`(2)    ` Output the string represented by the compressed byte in `.2`.\
`(14)   ` Call `(2)` and then call `(1)`.

Let us examine these before turning to the main program, starting with
`(4)`.

    (4)     DO (1001) NEXT

This one isn\'t really a subroutine, but it should be explained up
front. The standard technique of handling conditionals is to set `.5` to
either `#1` or `#2` and then jump to a line which in turn jumps to
`(1001)`. In this program, however, most conditionals are handled by
setting `.5` to either `#2` or `#3`. (This is because it usually
requires fewer characters to create a `#2` vs. `#3` value than the more
traditional `#1` vs. `#2`.) This necessitates having an extra jump
before reaching `(1001)`, which is what this statement accomplishes.

Additionally, `(4)` is used in lieu of a `RESUME` statement, typically
by calling `(4)` with `.5` set to `#3`. The quine actually contains no
`RESUME` statements. Instead, each subroutine is arranged to fall
through to a `DO (4) NEXT` statement. In each case `.5` is known to have
the desired value, usually leftover from a previous test.

    (24)        DO STASH .1
        PLEASE .1 <- .4
        PLEASE .4 <- .2
            DO (1010) NEXT
        PLEASE RETRIEVE .1
            DO ,2SUB#1 <- .3~#255
        PLEASE READ OUT ,2
            DO (4) NEXT

`(24)` is a bare-bones character-output routine. It stores the previous
character output in `.4` so that it can subtract the following character
from it. (Thus, all output in the program must be done through this
routine.) `.1` is frequently used in the program as a loop counter, so
`(24)` `STASH`es `.1` before performing the subtraction. `,2` is created
as an one-element tail array --- and `.4` is set to `#0` --- at the
start of the program.

Note that `(24)` does not affect the value of `.5`, so as per the
comments in the previous section, the program can only safely
`DO (24) NEXT` when `.5` is already set to `#3`.

The next subroutine, `(1)`, is our \"itoa\" function. This is the
central component to outputting the second section:

    (1) PLEASE .5 <- '?"!1~.1'~#1"$#2'~#6
        PLEASE .2 <- #10
            DO (4) NEXT
            DO (1040) NEXT
        PLEASE .5 <- .1
        PLEASE .1 <- .3
            DO (1030) NEXT
            DO STASH .1
        PLEASE .1 <- .5
        PLEASE .2 <- .3
            DO (1010) NEXT
        PLEASE RETRIEVE .1
            DO STASH .3
            DO (1) NEXT
        PLEASE RETRIEVE .3
        PLEASE .2 <- .3$#3
        PLEASE .2 <- !2~#15'$!2~#240'
        PLEASE .2 <- !2~#15'$!2~#240'
            DO (24) NEXT
        PLEASE RESUME #1

This is a recursive subroutine. On each recursion, one decimal digit is
extracted from `.1` until it reaches zero. So, the first step of the
routine is to test the value of `.1`. If it is zero, then `(1)` returns
to where it was called. (Note that this means that a value of zero is
incorrectly rendered as an empty string. But see below.)

If `.1` is non-zero, the subroutine first divides it by ten. It then
takes the the resulting quotient and multiplies it by ten. By
subtracting that product from the original number, the value of the
lowest decimal digit is isolated. This value is stored in `.3` and
`STASH`ed. Then the quotient is `RETRIEVE`d and `(1)` is called
recursively. In this fashion the digits of the number are separated out
and stored in a stack of `STASH`ed `.3` values, lowest to highest. When
`.1` reaches zero and the recursion bottoms out, the individual digit
values are `RETRIEVE`d from highest to lowest. The part of the
subroutine after the recursion adds 48 to the digits, bit-reverses the
sum, and passes the resulting value to `(24)` to be output as an ASCII
digit.

Note, by the way, that the code does not actually call `(24)` as shown
above. Instead, the `(1)` subroutine is placed in the source file just
above `(24)` in the source file, and execution is simply allowed to fall
through. (In other words, the last two lines of the above subroutine are
fictional, added here for the sake of clarity.)

There are a couple of side effects of this subroutine which should be
mentioned here. The first one is that `.1` will always be equal to zero
by the time this subroutine returns to its caller. The second side
effect involves the value of the bottom four bits of `.2` when the
subroutine returns to its original caller. Typically, these bits will
always be equal to 12, as this is the top half of the bit-reversed value
of the ASCII digit characters. However, in the lone case where `(1)` was
called with `.1` equal to zero, `.2` will instead be equal to 10 (as you
can see by inspecting the first two lines of the subroutine).

The next subroutine to examine is `(2)`, the decompression routine. This
is the central component to outputting the third section. It is also
recursive; in fact, it is doubly recursive:

    (2) PLEASE .5 <- #1$!2~#1'
            DO (20) NEXT
            DO STASH :2
        PLEASE .5 <- #1$!2~#2'
            DO :2 <- ;2SUB!2~#508'
            DO (21) NEXT
        PLEASE .2 <- :2~#65280
            DO (2) NEXT
        PLEASE .2 <- :2~#255
        PLEASE RETRIEVE :2
            DO (2) NEXT
    (20)        DO (4) NEXT
        PLEASE .5 <- #1$"!2~.2'~#1"
            DO (10) NEXT
            DO (24) NEXT
            DO (1001) NEXT
    (21)        DO (4) NEXT
            DO :2 <- :2~'#65280$#65280'
        PLEASE .5 <- #3
    (10)        DO (4) NEXT
        PLEASE GIVE UP

First, the low bit of `.2` is tested. If it is zero, then `.2` contains
a valid bit-reversed ASCII character. In this case, the subroutine jumps
to `(20)`, where the character is output, and the subroutine immediately
returns to the caller. Otherwise, `.2`\'s value is an index into our
compression dictionary. The top six bits of the byte value in `.2` is
used as the index into `;2`. The second-lowest bit is used to determine
which half of `:2` to use. If this bit is zero, then the code at `(21)`
shifts the value in `:2` down 16 bits. Then the subroutine calls itself
recursively, once for each byte value stored in `:2`. In this way are
the dictionary entries expanded to their full string values when output.

Now, there are two important aspects to the subroutine that the above
paragraph skipped over. First, note that actually seven bits of `.2`,
not six, are used for the index into `;2`. The compression dictionary
only occupies entries 1 through 63, however; the entries beyond 63
contain the compressed bytestream. Thus, this routine is also used to
extract two bytes from the compressed string, and output their
decompressed values.

Second, note that the code under `(20)` tests if `.2` is equal to zero
before calling `(24)`. If so, the subroutine is diverted to the line
following `(10)`. So this means that the program can be made to end at
any time by attempting to output a zero byte.

The final subroutine, `(14)`, is very simple:

    (14)        DO (2) NEXT
            DO (1) NEXT
        PLEASE RESUME #1

The effect is to output the dictionary entry corresponding to the value
in `.2`, followed by the decimal number stored in `.1`. (But note, once
again, that the code does not actually call `(1)`. Rather the `(14)`
subroutine is placed before `(1)` in the source file, and execution is
allowed to just fall through.)

Having covered the subroutines, and the initialization of the hybrid
array, let us now turn to the main body of the program.

        PLEASE .1 <- #255
        PLEASE .2 <- .1
            DO ,2 <- #1
        PLEASE .4 <- #0
            DO (14) NEXT

The above lines complete the initialization section. The `,2` array is
created and `.4` is set to zero, as required by the `(24)` subroutine.
Both `.1` and `.2` are set to 255 just before `(14)` is invoked. The
`(14)` routine, remember, simply calls `(2)` and `(1)` sequentially.
`(2)` expands the value 255 in `.2` into the output string
\"`DO;2<-#`\", and `(1)` outputs the value in `.1` as the string
\"`255`\". The total effect is that the first line of the program is
output. This completes the printing of the first section.

        PLEASE COME FROM (3)
            DO (1020) NEXT
            DO STASH .1
        PLEASE .2 <- #155
            DO :2 <- ;2SUB.1
            DO (14) NEXT
        PLEASE .2 <- #11
        PLEASE .1 <- :2~'#65535$#0'
            DO (14) NEXT
        PLEASE .2 <- #15
        PLEASE .1 <- :2~'#0$#65535'
            DO (14) NEXT
        PLEASE RETRIEVE .1
        PLEASE .5 <- .2~#6
    (3)     DO (4) NEXT

This loop outputs section two of source code, i.e. the statements that
initialize `;2`. `.1` is the loop counter, initialally set to zero by
the previous call to `(2)`, and incremented at the start of each
iteration by `(1020)`. The body of the loop calls `(14)` three separate
times. The first time, `.2` is set to 155. `(2)` expands 155 to the
string \"`DO;2SUB#`\", and `(1)` prints the value of the loop counter.
The second time, `.2` is set to 11, which expands to the string
\"`<-#`\", and `.1` is set to the left-interleaved bits in `:2` (which
contains the current element of `;2`). For the third call to `(14)`,
`.2` is set to 15, which expands to the string \"`$#`\", and `.1` gets
the right-interleaved bits of `:2`. In this fashion, a single line of
source code is reconstructed and output.

Finally, at the bottom of the loop body, two bits from `.2` are
extracted and stored in `.5` before calling `(4)`. Recall that `(1)`
leaves a value of 12 in the bottom four bits of `.2`, and therefore `.5`
will get set to 2, thus causing `(4)` to do nothing. Except, that is, in
the case when `(1)` is called with `.1` set to zero --- in this case
case, `.2` will have a value of 10 in its bottom bits, which will put a
value of 1 in `.5`. The upshot of this is that the loop will exit when
it encounters an element of `;2` whose right-interleaved half is equal
to zero. Conveniently, this is true only for final element of `;2`.

At this point the program has completed the output of section two. The
third and final section to be output is what is encoded in the elements
of `;2`, in Re-Pair compressed form. All that remains is to decompress
and output this data. (Note, by the way, that the first character
encoded in this data is a \"`0`\" character. This is because the final
\"`0`\" character of section two hasn\'t been printed out yet, because
as noted above the `(2)` routine renders a zero value as an empty
string.)

    (4)     DO (1001) NEXT
        PLEASE .1 <- #255
        PLEASE COME FROM (34)
            DO (1020) NEXT
            DO (1020) NEXT
        PLEASE .2 <- .1
    (34)        DO (2) NEXT

In this loop, `.1` starts out equal to 255, which corresponds to the
final entry in the compression dictionary. On each iteration `.1` is
increased by two; on the first iteration this leaves `.1` equal to 257,
referring to the first two bytes of the compression string. This value
is then transferred to `.2` and `(2)` is called. This causes two bytes
from the bytestream stored in `;2` to be extracted, decompressed, and
output. The reason for increasing by two on each iteration is that the
value passed to `(2)` must always be odd; even values correspond to
literal ASCII character values.

This loop continues until the zero bytes at the end of the data are
reached, which, as noted above, cause `(2)` to end the program. The
quine has completed the printing of the third section, and thus the
entire quine.

------------------------------------------------------------------------

For the unadulterated awfulness of it all, here is what the quine looks
like in its entirety. Line breaks have been inserted, but the real
program contains no whitespace of any kind. (Be aware that these line
breaks will prevent this code from successfully compiling. If you want a
working copy of the quine, please use the link at the top of this page.)
Note that the part of the program that was so meticulously discussed
above occupies roughly a third of the source code. The long initial
sequence of assignment statements constitute the majority of the
program.

    DO;2<-#255DO;2SUB#1<-#23948$#3181DO;2SUB#2<-#2568$#53882DO;2SUB#3<-#8776$#4650D
    O;2SUB#4<-#1260$#40490DO;2SUB#5<-#27757$#26128DO;2SUB#6<-#54082$#1258DO;2SUB#7<
    -#32099$#811DO;2SUB#8<-#50248$#40237DO;2SUB#9<-#552$#55962DO;2SUB#10<-#56582$#8
    50DO;2SUB#11<-#29560$#2282DO;2SUB#12<-#3805$#21001DO;2SUB#13<-#37509$#7485DO;2S
    UB#14<-#9070$#6039DO;2SUB#15<-#2723$#25131DO;2SUB#16<-#57608$#6137DO;2SUB#17<-#
    418$#15338DO;2SUB#18<-#41351$#6397DO;2SUB#19<-#2955$#14435DO;2SUB#20<-#97$#1391
    3DO;2SUB#21<-#551$#23120DO;2SUB#22<-#19065$#58047DO;2SUB#23<-#60707$#12331DO;2S
    UB#24<-#8718$#59963DO;2SUB#25<-#2727$#27177DO;2SUB#26<-#32830$#14335DO;2SUB#27<
    -#21192$#6813DO;2SUB#28<-#18998$#59933DO;2SUB#29<-#18386$#40665DO;2SUB#30<-#104
    00$#42282DO;2SUB#31<-#49759$#63089DO;2SUB#32<-#51502$#38329DO;2SUB#33<-#2568$#2
    1154DO;2SUB#34<-#48931$#32803DO;2SUB#35<-#52561$#12495DO;2SUB#36<-#60975$#8931D
    O;2SUB#37<-#8953$#14941DO;2SUB#38<-#11269$#62899DO;2SUB#39<-#17007$#27305DO;2SU
    B#40<-#2883$#40763DO;2SUB#41<-#923$#38920DO;2SUB#42<-#13762$#1181DO;2SUB#43<-#2
    6919$#13475DO;2SUB#44<-#32110$#32805DO;2SUB#45<-#28197$#41531DO;2SUB#46<-#11397
    $#10933DO;2SUB#47<-#18954$#64311DO;2SUB#48<-#14979$#4735DO;2SUB#49<-#56758$#503
    31DO;2SUB#50<-#26785$#9765DO;2SUB#51<-#51412$#43774DO;2SUB#52<-#36740$#9147DO;2
    SUB#53<-#51101$#41909DO;2SUB#54<-#43553$#13603DO;2SUB#55<-#18585$#22919DO;2SUB#
    56<-#83$#63368DO;2SUB#57<-#16557$#22417DO;2SUB#58<-#8586$#29786DO;2SUB#59<-#165
    98$#38839DO;2SUB#60<-#849$#55195DO;2SUB#61<-#49734$#31353DO;2SUB#62<-#708$#2729
    9DO;2SUB#63<-#41475$#56753DO;2SUB#64<-#10232$#12153DO;2SUB#65<-#29478$#4389DO;2
    SUB#66<-#51348$#5783DO;2SUB#67<-#6226$#38397DO;2SUB#68<-#6779$#53847DO;2SUB#69<
    -#58337$#9053DO;2SUB#70<-#59323$#9495DO;2SUB#71<-#5868$#22011DO;2SUB#72<-#20324
    $#58283DO;2SUB#73<-#7818$#15727DO;2SUB#74<-#23283$#4831DO;2SUB#75<-#38054$#6651
    DO;2SUB#76<-#50574$#45010DO;2SUB#77<-#8951$#9943DO;2SUB#78<-#34349$#7969DO;2SUB
    #79<-#34468$#7641DO;2SUB#80<-#57018$#7647DO;2SUB#81<-#18727$#9134DO;2SUB#82<-#1
    3091$#22815DO;2SUB#83<-#17162$#14185DO;2SUB#84<-#8821$#12919DO;2SUB#85<-#51865$
    #6553DO;2SUB#86<-#62719$#7099DO;2SUB#87<-#36046$#27566DO;2SUB#88<-#39538$#13037
    DO;2SUB#89<-#13096$#37807DO;2SUB#90<-#24876$#43309DO;2SUB#91<-#9788$#13051DO;2S
    UB#92<-#9794$#55763DO;2SUB#93<-#41918$#44978DO;2SUB#94<-#19860$#5917DO;2SUB#95<
    -#9124$#7133DO;2SUB#96<-#17315$#5037DO;2SUB#97<-#16043$#56731DO;2SUB#98<-#26371
    $#8565DO;2SUB#99<-#57178$#30514DO;2SUB#100<-#1142$#32061DO;2SUB#101<-#43279$#12
    336DO;2SUB#102<-#31466$#2002DO;2SUB#103<-#5606$#14719DO;2SUB#104<-#46820$#8021D
    O;2SUB#105<-#14955$#6781DO;2SUB#106<-#3484$#38981DO;2SUB#107<-#62208$#0PLEASE.1
    <-#255PLEASE.2<-.1DO,2<-#1PLEASE.4<-#0DO(14)NEXTPLEASECOMEFROM(3)DO(1020)NEXTDO
    STASH.1PLEASE.2<-#155DO:2<-;2SUB.1DO(14)NEXTPLEASE.2<-#11PLEASE.1<-:2~'#65535$#
    0'DO(14)NEXTPLEASE.2<-#15PLEASE.1<-:2~'#0$#65535'DO(14)NEXTPLEASERETRIEVE.1PLEA
    SE.5<-.2~#6(3)DO(4)NEXT(2)PLEASE.5<-#1$!2~#1'DO(20)NEXTDOSTASH:2PLEASE.5<-#1$!2
    ~#2'DO:2<-;2SUB!2~#508'DO(21)NEXTPLEASE.2<-:2~#65280DO(2)NEXTPLEASE.2<-:2~#255P
    LEASERETRIEVE:2DO(2)NEXT(20)DO(4)NEXTPLEASE.5<-#1$"!2~.2'~#1"DO(10)NEXTDO(24)NE
    XT(4)DO(1001)NEXTPLEASE.1<-#255PLEASECOMEFROM(34)DO(1020)NEXTDO(1020)NEXTPLEASE
    .2<-.1(34)DO(2)NEXT(14)DO(2)NEXT(1)PLEASE.5<-'?"!1~.1'~#1"$#2'~#6PLEASE.2<-#10D
    O(4)NEXTDO(1040)NEXTPLEASE.5<-.1PLEASE.1<-.3DO(1030)NEXTDOSTASH.1PLEASE.1<-.5PL
    EASE.2<-.3DO(1010)NEXTPLEASERETRIEVE.1DOSTASH.3DO(1)NEXTPLEASERETRIEVE.3PLEASE.
    2<-.3$#3PLEASE.2<-!2~#15'$!2~#240'PLEASE.2<-!2~#15'$!2~#240'(24)DOSTASH.1PLEASE
    .1<-.4PLEASE.4<-.2DO(1010)NEXTPLEASERETRIEVE.1DO,2SUB#1<-.3~#255PLEASEREADOUT,2
    (21)DO(4)NEXTDO:2<-:2~'#65280$#65280'PLEASE.5<-#3(10)DO(4)NEXTPLEASEGIVEUP

\
[[INTERCAL](http://www.muppetlabs.com/~breadbox/intercal/)]{.small}\
[[Brian Raiter](http://www.muppetlabs.com/~breadbox/)]{.small}\
[[Muppetlabs](http://www.muppetlabs.com/)]{.small}
