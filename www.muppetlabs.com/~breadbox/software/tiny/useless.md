Other Teensy Programs
=====================

The programs listed here are provided as exhibitions of just how
compressed a Linux ELF executable can be and still perform a function.
All of them abuse the kernel\'s casual approach to validating ELF files
in order to reduce size. The assembler source code of each of these
programs includes details showing how the ELF header, the program
segment header table, and the x86 instructions of the actual program
overlap each other.

In order to use one of these programs, you can download the assembler
source and build it with [nasm](http://www.nasm.us). If you don\'t want
to install nasm, and you have reason to believe that I can be trusted,
you can download a pre-built binary and run it directly. (Note that you
will need to use chmod +x to mark a downloaded binary as executable.)

[true.asm source](true.asm.txt)\
[true binary](true)\
45 bytes

Despite the name, this program provides binaries for both true and
false. It returns an exit code of either zero or one, depending on
whether it is invoked with the name \"true\" or \"false\", respectively.
At 45 bytes, this program is the smallest it is possible for a Linux ELF
executable to be.

[keepalive.asm source](keepalive.asm.txt)\
[keepalive binary](keepalive)\
56 bytes

Here\'s a program that I\'ve actually used. It simply runs forever,
printing a bell character every four minutes or so. When I used it, I
would leave it running in the background after logging into a remote
machine that times out connections when they\'re idle. One can then
disable the terminal\'s bell to make the character completely invisible.
Admittedly, it\'s a bit longer than the one-line shell script I
originally used, but on the plus side it doesn\'t take up an extra
process in order to sleep.

[hello.asm source](hello.asm.txt)\
[hello binary](hello)\
62 bytes

Here is the program that started me off on this whole pursuit: hello
world. It is dense. With the program header table overlaid on top of the
ELF header, and program itself running through both of them, some of the
bytes have no less than three different purposes.

[Here](http://d.hatena.ne.jp/kikx/20061111) you can find an even smaller
hello-world program, apparently written by someone named Kikuyan
(菊やん). It is only 58 bytes long, and would have been 57 if the author
had used the same version of the greeting as myself. The program uses
the technique of loading to absolute address zero, which permits a
number of tricks that further reduce code size. I have not used this
technique myself, because current versions of Linux do not, by default,
permit executables to use a load address of zero. It is an ingenious
little program, though.

[hello-x64.asm source](hello-x64.asm.txt)\
[hello-x64 binary](hello-x64)\
85 bytes

And, for the record, here\'s a hello-world program for 64-bit ELF. It\'s
quite a bit larger than the 32-bit version, but nonetheless I find it
surprising that it\'s only five bytes larger than the smallest 64-bit
ELF executable. As with that program, I credit Oleg Finkelshteyn for
showing me the overlapping technique that it uses. In many ways, it is
reminiscient of Kikuyan\'s program, in that because the assembly program
starts at the very top, it becomes thoroughly interwoven with both ELF
headers.

[echo.asm source](echo.asm.txt)\
[echo binary](echo)\
76 bytes

While echo is actually a very useful and important utility, nobody
really needs a standalone binary of echo these days, so it still belongs
on this page. This was inspired by a couple of blog posts written by
[Jan Halsema](https://blog.mandejan.nl) about their own attempts to use
assembly to create a teensy version of echo. It\'s a good example of how
the choice of algorithm has as much to do with size optimization as
abusing the ELF standard. This program works by calling write() once per
character --- a terribly inefficient design choice that does wonders for
its overall size.

[bf.asm source](bf.asm.txt)\
[bf binary](bf)\
166 bytes

Brainfuck is a very simplistic programming language, which was invented
by Urban Müller solely for the purpose of being able to create a
compiler that was less than 256 bytes in size, for the Amiga OS. (A
description of the language can be found at [my Brainfuck
page](http://www.muppetlabs.com/~breadbox/bf/), among many other
places.) I decided to take up the challenge as well, and created a
Brainfuck compiler for Linux using less than 256 bytes. The compiler
works as a filter: redirect the source code to the compiler\'s input and
the compiler\'s output to a file. (And don\'t forget to chmod +x the
output file.) At the beginning I didn\'t expect that I would actually
succeed, since I thought I would need almost half of that just for the
headers. I think my first cut was 458 bytes in size. I was quite pleased
with myself when I trimmed that down to less than 300 bytes, ecstatic
when I finally reached the 255-byte goal, and downright triumphant when
I later got it to work in 238 bytes. By the time I had a 198-byte
version, I had to admit that I had no idea where it was going to end.
It\'s now at 166 bytes. And though I can\'t quite believe it, it works
just as well as the first one did. As useless as it is, I think this one
would have to be the crown jewel of my collection. It is quite possibly
also the ugliest and most opaque program I have ever written.

------------------------------------------------------------------------

\
[[Tiny](http://www.muppetlabs.com/~breadbox/software/tiny/)]{.small}\
[[Software](http://www.muppetlabs.com/~breadbox/software/)]{.small}\
[[Brian Raiter](http://www.muppetlabs.com/~breadbox/)]{.small}
