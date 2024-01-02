Useful Teensy Programs
======================

The programs listed here are provided as exhibitions of just how
compressed a Linux ELF executable can be and still accomplish something
useful. Because they are potentially useful, they all adhere to the ELF
specification (though most of them still bypass libc in favor of making
direct system calls).

In order to use one of these programs, you can download the assembler
source and build it with [nasm](http://www.nasm.us). If you don\'t want
to install nasm, and you have reason to believe that I can be trusted,
you can download a pre-built binary and run it directly. (Note that you
will need to use chmod +x to mark a downloaded binary as executable.)

[cls.asm source](cls.asm.txt)\
[cls binary](cls)\
98 bytes

Admittedly, this program is trivial, no more than a variant on
hello-world. Yet the fact is that I use this program almost daily. It
just clears the terminal screen, in the process also clearing any odd
persistent state such as reverse video. It\'s both shorter to type than
\"clear\" and faster than \"reset\". (For some reason the standard reset
utility takes a full second to complete.) Admittedly this program
assumes an ANSI-compatible terminal without testing for same, or even if
stdout is connected to a terminal, but I have yet to find such shortcuts
to be problematic. The name \"cls\", short for \"clear screen\", is
deeply embedded in my muscle memory, thanks to the TRS-80 and MS-DOS
both using it, and I find myself typing it habitually.

[hexdump.asm source](hexdump.asm.txt)\
[hexdump binary](hexdump)\
202 bytes

This is your classic hexdump program. I wrote it one day in a fit of
pique, after trying (and failing) to convince the standard Linux
programs to output bytes in the formatting style that I\'ve been
accustomed to since before reaching my majority. (I\'ve since stopped
using this program, as the default output of xxd(1) is nearly
identical.) My original version simply read from standard input, but I
quickly found this irritating enough that I sacrificed a few more bytes
in order to allow it to accept a filename on the command line.

[base64.asm source](base64.asm.txt)\
[base64 binary](base64)\
256 bytes

This is a simple base64 decoder utility. Like hexdump, it can either
accept a filename on the command line, or work on standard input. Since
sometimes very large files are encoded in base64, I allowed the program
to be slightly larger than strictly necessary in order to optimize for
speed. This version is actually noticeably faster than the utility
included in GNU coreutils for 32-bit Linux.

[ls.asm source](ls.asm.txt)\
[ls binary](ls)\
1017 bytes

This utility was my attempt to tackle an important yet complex tool. ls
is one of those programs that you really can\'t do without, in part
because its functionality has almost no overlap with other standard
tools, but also because it\'s tailored to provide multiple pieces of
information at a glance. My version is missing a few standard features,
such as sorting, but it does recognize many commonly-used command-line
options, such as `-l`, `-a`, `-F`, and `-R`. The \"long\" output format
only displays numeric user IDs, timestamps are displayed as ages instead
of actual times, and the columnar output is not particularly clever. But
beyond these things, it conforms pretty closely to the standard ls
program we all know and love.

[factor.asm source](factor.asm.txt)\
[factor binary](factor)\
1020 bytes

This is an implementation of the standard Unix utility. It displays the
prime factors of the integers provided on the command line, or on
standard input if no arguments are given. Instead of simply trying to
achieve the smallest possible size, I decided to shoot for real
portability with this program, for a change. It not only conforms to the
requirements of the ELF specification, it also avoids making direct
system calls and instead dynamically links with libc. It should continue
to work with any future version of Linux, as long as new versions of the
libc ABI and the ELF specification remain backwards-compatible. It also
includes online help, version information, and error messages, and
therefore arguably stands as a completely functional replacement for the
standard utility in GNU coreutils. Because factoring huge prime numbers
can sometimes run for a long time, I attempted to optimize for speed and
size both. This program makes significant use of the FPU in order to
increase parallelization in the inner loop. (Back when I first wrote it,
it was significantly faster than the standard GNU program. Since then,
the coreutils program has been updated with some advanced mathematics,
and it\'s now the faster program.)

[puzzle.asm source](puzzle.asm.txt)\
[puzzle binary](puzzle)\
995 bytes

The final program in this list is a game. And not just a game, but one
that runs under X. You\'ve probably seen the 15 sliding-tile puzzle at
some point in your life. Some of you may even remember the program that
came with the original 1984 Macintosh operating system. But are you
aware that, in order to justify including the puzzle in the limited
memory and disk space available, the author squeezed its size down to
under 600 bytes? (See
[here](http://www.folklore.org/StoryView.py?story=Puzzle.txt) for the
details.) Alas, while I would have loved to be able to present a Linux
binary that matched that size, the complexities of interfacing with an X
server and mimicking the details of the original put it well over that
target. I\'m still working to reduce it further, but for now here\'s my
hefty rendition. It uses the same graphics as the original, which
unfortunately means that the window is only slightly larger that its own
title bar on a modern display. But it is a faithful recreation of the
original Macintosh program that runs under X Windows. And despite all of
my hedging about its bloat, I\'d wager that it\'s the only X program
you\'ve ever seen under 1k.

(Usage note: This program does not go through normal channels to find
the X server; it assumes that your X server is running locally and that
you are the only (or at least the first) user. If the program
nevertheless fails immediately when run, you may need to give yourself
permission to start X programs directly. This can be done by running
`xhost si:localuser:$USER`. Afterwards, you can repeat the command with
a prepended minus sign to remove these permissions:
`xhost -si:localuser:$USER`.)

------------------------------------------------------------------------

\
[[Tiny](http://www.muppetlabs.com/~breadbox/software/tiny/)]{.small}\
[[Software](http://www.muppetlabs.com/~breadbox/software/)]{.small}\
[[Brian Raiter](http://www.muppetlabs.com/~breadbox/)]{.small}
