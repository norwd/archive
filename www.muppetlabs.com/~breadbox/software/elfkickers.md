::: {style="max-width:64em;margin:1em;"}
[Download
ELFkickers-3.2.tar.gz](http://www.muppetlabs.com/~breadbox/pub/software/ELFkickers-3.2.tar.gz)
(107k)\
[Github site](https://github.com/BR903/ELFkickers)

Kickers of ELF
==============

This distribution is a collection of programs that are generally
unrelated, except in that they all deal with ELF files.

The main purpose of these programs is to be illustrative and educational
\-- to help fellow programmers understand ELF files and something of how
they work under the Linux platform.

Each program is independent. There is very little shared code between
them, and in fact they all take slightly different approaches to
handling ELF files.

The distribution includes:

-   **sstrip**: a small utility that removes a few bytes from an
    executable that strip leaves behind.
-   **objres**: a \"compiler\" for including arbitrary binary resources
    in object files.
-   **elftoc**: a program that takes an ELF file and generates C code
    that defines a struct with the same memory image, using the structs
    and preprocessor symbols defined in \<elf.h\>.
-   **elfls**: a utility that displays an ELF file\'s program and/or
    section header tables, which serve as a kind of global roadmap to
    the file\'s contents.
-   **rebind**: a small utility that alters the binding of selected
    symbols in an object file.
-   **ebfc**: a compiler for a tiny programming language. The compiler
    can generate ELF executables, object files, and shared libraries.
-   **infect**: an example of how to modify an executable without
    affecting its original program.

Changelog
---------

-   May 2021: Version 3.2
    -   Updated ebfc for 64-bit executables, plus some cleanup.
-   November 2019: Version 3.1a
    -   Another bug-fix update.
-   November 2016: Version 3.1
    -   A handful of bug fixes that accumulated over five years.
-   November 2011: Version 3.0a
    -   Some changes made to improve portability.
    -   A couple of very minor bugs fixed.
-   May 2011: Version 3.0
    -   After a decade of inactivity, an update appears.
    -   All programs (except ebfc) have been modified to work with
        32-bit and 64-bit ELF files equally well.
    -   New programs objres and infect added to the collection.
    -   The [tiny
        programs](http://www.muppetlabs.com/~breadbox/software/tiny/)
        have been removed from ELF kickers --- they\'re already
        available on the web, and they tend to require more maintenance
        updates than the regular programs.
    -   General all-around code cleanup, and documentation added for the
        utilities that still needed it.
-   May 2001: Version 2.0a
    -   A couple of simple yet important bug fixes.
-   April 2001: Version 2.0
    -   Rewrite of several parts of elftoc.
    -   elftoc and elfls updated to be aware of new ELF structures.
-   March 2001
    -   New program rebind added to the collection.
    -   Two new tiny programs, others improved.
    -   Bug fix in elftoc and some of the READMEs.
-   February 2001
    -   Tiny programs updated for 2.2.17-compatibility.
-   January 2001
    -   -W option removed from the ebfc Makefile (left in as an
        oversight).
    -   keepalive.asm added to the tiny collection.
    -   New feature added to ebfc \-- namely, the acceptance of
        compressed source files.
-   August 2000
    -   Reordering of some header file inclusions and removal of -W from
        the gcc options in some of the Makefiles, to accommodate changes
        made to the 2.2 kernel and a new (spurious in this case) warning
        added to gcc 2.95.
    -   ls.asm added to the tiny collection.
-   July 1999
    -   Initial release.

All the programs in this distribution are available under the GNU
General Public License. Share and Enjoy. Contact me at
<breadbox@muppetlabs.com> if you have any questions or comments.

------------------------------------------------------------------------

\
[[Software](http://www.muppetlabs.com/~breadbox/software/)]{.small}\
[[Brian Raiter](http://www.muppetlabs.com/~breadbox/)]{.small}
:::
