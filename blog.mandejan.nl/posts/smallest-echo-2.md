[Jan\'s Blog!](https://blog.mandejan.nl/)\

[**Start**](/). [**About**](/about.html).

::: {role="main"}
(Draft) Smallest Echo, Part 2: x86 Assembly
===========================================

**04.10.2020 14:02**

<div>

Notice: Draft
=============

I'll publish it once its finished thanks :)

------------------------------------------------------------------------

Hi all, last time we left off on our journey toward the smallest
implementation of an echo binary for linux we where using
[Zig](https://ziglang.org)! Check out [Part
1](/posts/smallest-echo.html) if you haven't already. At the end of the
post I concluded at 277 bytes. It was at this point I concluded that we
needed to leave the final niceties from the realm of mortal programming
languages behind. But before we start venturing deep into the pages of
the x86 Software Developers
[Manual](https://software.intel.com/content/www/us/en/develop/articles/intel-sdm.html)
lets see if we can cling on to the final shreds of hope Zig can provide
for us. By shreds of hope I meant assembly and by providing I meant
flexing with your radare2 skills and running `r2 -qc'af' -c'pdf'` on
your binary. You could also go the convienient way by running your Zig
code through
[Godbolt](https://godbolt.org/z/eobTcG)^[1](#fn:1){.footnote-ref}^ and
going from there. The radare2 way comes with the advantage of printing
you some gourgeous comments for every line of assembly. After cleaning
the assembly up a bit (naming things and commenting) I ended up with the
following file:

182 bytes {#182-bytes}
---------

::: {.highlight}
``` {.chroma}
[bits 32]
global _start
section .text

_start:                                         ; bytes      ; r2 comment
        mov     esi, dword [esp]                ; 8b3424     ; 005-32bit.zig:4 pub export fn _start() callconv(.Naked) noreturn {
        xor     ebp, ebp                        ; 31ed       ;
        mov     ebx, 1                          ; bb01000000 ; i386.zig:31     return asm volatile ("int $0x80"
        lea     edi, [esi - 1]                  ; 8d7eff     ; 005-32bit.zig:11     for (argv[1..argc]) |arg, i| {
        add     esi, -2                         ; 83c6fe     ; 005-32bit.zig:0
.loop:  ; for every argv
        cmp     ebp, edi                        ; 39fd       ; 005-32bit.zig:11     for (argv[1..argc]) |arg, i| {
        je      .exit                           ; 7422       ;
        mov     ecx, dword [esp + 4*ebp + 8]    ; 8b4cac08   ;
        xor     edx, edx                        ; 31d2       ; 005-32bit.zig:0
.strlen: ; increment edx until we find a 0 byte
        cmp     byte [ecx + edx], 0             ; 803c1100   ; mem.zig:710     while (ptr[i] != sentinel) {
        lea     edx, [edx + 1]                  ; 8d5201     ; mem.zig:711         i += 1;
        jne     .strlen                         ; 75f7       ; mem.zig:710     while (ptr[i] != sentinel) {
        mov     byte [ecx + edx - 1], ' '       ; c64411ff20 ; 005-32bit.zig:13         arg[len] = ' '; ; [0x20:1]=255 ; 32
        mov     eax, 4                          ; b804000000 ; i386.zig:31     return asm volatile ("int $0x80"
        cmp     ebp, esi                        ; 39f5       ; 005-32bit.zig:15         if (i == argc - 2) break;
        lea     ebp, [ebp + 1]                  ; 8d6d01     ; 005-32bit.zig:11     for (argv[1..argc]) |arg, i| {
        int     0x80                            ; cd80       ; i386.zig:31     return asm volatile ("int $0x80"
        jne     .loop                           ; 75da       ; 005-32bit.zig:15         if (i == argc - 2) break;
.exit:  ; Write newline and call exit(0)
        mov     eax, 4                          ; b804000000 ; i386.zig:31     return asm volatile ("int $0x80"
        mov     ebx, 1                          ; bb01000000 ;
        mov     ecx, newline                    ; b9b4004000 ; 0x4000b4 ; "\n"
        mov     edx, 1                          ; ba01000000 ;
        int     0x80                            ; cd80       ;
        mov     eax, 1                          ; b801000000 ; i386.zig:12     return asm volatile ("int $0x80"
        xor     ebx, ebx                        ; 31db       ;
        int     0x80                            ; cd80       ;

newline:
        db      0x0a
```
:::

If you can build the above code as follows
`yasm -felf32 -o echo.o 006-start.asm && ld -m elf_i386 -s -n -Ttext-segment=0x10000 -o echo echo.o && sstrip -z echo`.
This will leave you with a binary 182 bytes in size. But wait you ask,
since you so nicely provided the dissassembled bytes next to the
instructions, when I add those all up I only get 86 bytes? Good
question! Let's inspect the binary! (`xxd echo`)

::: {.highlight}
``` {.chroma}
00000000: 7f45 4c46 0101 0100 0000 0000 0000 0000  .ELF............
00000010: 0200 0300 0100 0000 6000 0100 3400 0000  ........`...4...
00000020: 0000 0000 0000 0000 3400 2000 0100 2800  ........4. ...(.
00000030: 0000 0000 0100 0000 6000 0000 6000 0100  ........`...`...
00000040: 6000 0100 5600 0000 5600 0000 0500 0000  `...V...V.......
00000050: 1000 0000 0000 0000 0000 0000 0000 0000  ................
00000060: 8b34 2431 edbb 0100 0000 8d7e ff83 c6fe  .4$1.......~....
00000070: 39fd 7422 8b4c ac08 31d2 803c 1100 8d52  9.t".L..1..<...R
00000080: 0175 f7c6 4411 ff20 b804 0000 0039 f58d  .u..D.. .....9..
00000090: 6d01 cd80 75da b804 0000 00bb 0100 0000  m...u...........
000000a0: b9b5 0001 00ba 0100 0000 cd80 b801 0000  ................
000000b0: 0031 dbcd 800a                           .1....
```
:::

As you can see, the first instruction `mov esi, dword [esp]` hex
`8b3424` appears at address `0x60`, that means that there are 96 bytes
before it that are not cpu instructions but that still contribute to the
binary size. If we want the smallest binary possible, we need to be able
to controll *every* byte in our binary and letting our assembler and
linker make the elf header for us is just not feasable anymore. Luckily
yasm has the option to emit binaries directly via the `-f bin` flag.
This also omits the need for a linker and our sstrip utility. On the
other hand, this tasks us with reading the elf specification
([Wikipedia](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format)
has a good summary). The smallest elf header I could find online was
described in this [excellent
essay](https://muppetlabs.com/~breadbox/software/tiny/teensy.html)
coincedentally written by the same talented author as the ELFKicker
tools. (from which I used the `sstrip` utility). I adapted his findings
slightly to fit my program. I also made a template with just a program
that returns 42 if you want to give size coding a try. You can find the
template here:

::: {.section .footnotes role="doc-endnotes"}

------------------------------------------------------------------------

1.  ::: {#fn:1}
    Or as [some](https://twitter.com/mattgodbolt) prefer to call it:
    [Compiler Explorer](https://godbolt.org)
    [↩︎](#fnref:1){.footnote-backref}
    :::
:::

</div>
:::

<div>

<div>

### LATEST POSTS

</div>

<div>

-   [(Draft) Smallest Echo, Part 2: x86
    Assembly](/posts/smallest-echo-2.html)
-   [Smallest Echo, Part 1: Zig](/posts/smallest-echo.html)

</div>

</div>

© 2021 [**Jan\'s Blog!**](https://blog.mandejan.nl/).
