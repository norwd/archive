The Teensy Executable Revisited
===============================

(or, \"Thunderclouds Gather on the Horizon\")

------------------------------------------------------------------------

On a couple of occasions, people have responded to my original essay
with the comment that what I\'ve created by the end isn\'t really an ELF
executable. Rather, it is a file that the Linux kernel, in its current
incarnation, happens to *mistake* for an ELF executable.

It\'s a fair point. That 45-byte file clearly doesn\'t conform to
numerous requirements of the ELF specification. But can you blame me?
How could I have stopped at the point just before I tossed the ELF
specification out the window, knowing what might still be possible?

But to satisfy these purists, and the puritan side in all of us, I\'ve
created this sequel.

------------------------------------------------------------------------

So. We have an executable that we whittled down to 45 bytes. We now want
to bring it into rigid conformance with published standards, while still
keeping it as small as possible.

The point at which we strayed from straight and narrow path was when we
started fiddling with \"unused\" fields in the ELF header. So let\'s
back up to before that point:

      BITS 32
      
                    org     0x08048000
      
      ehdr:                                                 ; Elf32_Ehdr
                    db      0x7F, "ELF", 1, 1, 1            ;   e_ident
            times 9 db      0
                    dw      2                               ;   e_type
                    dw      3                               ;   e_machine
                    dd      1                               ;   e_version
                    dd      _start                          ;   e_entry
                    dd      phdr - $$                       ;   e_phoff
                    dd      0                               ;   e_shoff
                    dd      0                               ;   e_flags
                    dw      ehdrsz                          ;   e_ehsize
                    dw      phdrsz                          ;   e_phentsize
                    dw      1                               ;   e_phnum
                    dw      0                               ;   e_shentsize
                    dw      0                               ;   e_shnum
                    dw      0                               ;   e_shstrndx
      ehdrsz        equ     $ - ehdr
      
      phdr:                                                 ; Elf32_Phdr
                    dd      1                               ;   p_type
                    dd      0                               ;   p_offset
                    dd      $$                              ;   p_vaddr
                    dd      $$                              ;   p_paddr
                    dd      filesz                          ;   p_filesz
                    dd      filesz                          ;   p_memsz
                    dd      5                               ;   p_flags
                    dd      0x1000                          ;   p_align
      phdrsz        equ     $ - phdr
      
      _start:
                    xor     eax, eax
                    inc     eax
                    mov     bl, 42
                    int     0x80
      
      filesz        equ     $ - $$

This was our ninety-one-byte version. So: are we stuck with this as our
best size? No, not quite. We violated no rules when we overlapped the
ELF header and the program header table by eight bytes. The ELF
specification explicitly permits overlap of different data structures
within the file. So let\'s do that here:

      ; tiny.asm
      
      BITS 32
      
                    org     0x08048000
      
      ehdr:
                    db      0x7F, "ELF", 1, 1, 1    ; e_ident
            times 9 db      0
                    dw      2                       ; e_type
                    dw      3                       ; e_machine
                    dd      1                       ; e_version
                    dd      _start                  ; e_entry
                    dd      phdr - $$               ; e_phoff
                    dd      0                       ; e_shoff
                    dd      0                       ; e_flags
                    dw      ehdrsz                  ; e_ehsize
                    dw      phdrsz                  ; e_phentsize
      phdr:         dd      1                       ; e_phnum       ; p_type
                                                    ; e_shentsize
                    dd      0                       ; e_shnum       ; p_offset
                                                    ; e_shstrndx
      ehdrsz        equ     $ - ehdr
                    dd      $$                                      ; p_vaddr
                    dd      $$                                      ; p_paddr
                    dd      filesz                                  ; p_filesz
                    dd      filesz                                  ; p_memsz
                    dd      5                                       ; p_flags
                    dd      0x1000                                  ; p_align
      phdrsz        equ     $ - phdr
      
      _start:       xor     eax, eax
                    inc     eax
                    mov     bl, 42
                    int     0x80
      
      filesz        equ     $ - $$

That gives us eighty-three bytes. What else can we do? Seems like there
isn\'t much. In desperation, we might turn back to the ELF specification
and read it over again, looking for something.

Are there any guarantees anything about the initial register values?
Only for one register: edx. And what is says is that it will contain
either zero, or the address of a final shutdown procedure. So, no
guarantees at all, really. Keep looking.

A-ha: The p\_paddr field of the program header table structure! Every
other field of the headers which doesn\'t apply to to Intel
architecture, or doesn\'t apply to an executable file --- or, at least,
not to our executable file --- is required by the ELF specification to
be set to zero. But for the p\_paddr field, the specification says the
field has *unspecified* contents. So we have four bytes that we can play
with, after all.

What can we do with them? Use it to hold part of our program, naturally.
Of course, we can\'t put the whole program there, so we\'ll need to
waste two of the four bytes on a jmp instruction, in order to get to the
rest of it. But that still leaves two bytes that we can use, and the
first instruction of our program is exactly two bytes long.

      ; tiny.asm
      
      BITS 32
      
                    org     0x08048000
      
      ehdr:
                    db      0x7F, "ELF", 1, 1, 1    ; e_ident
            times 9 db      0
                    dw      2                       ; e_type
                    dw      3                       ; e_machine
                    dd      1                       ; e_version
                    dd      _start                  ; e_entry
                    dd      phdr - $$               ; e_phoff
                    dd      0                       ; e_shoff
                    dd      0                       ; e_flags
                    dw      ehdrsz                  ; e_ehsize
                    dw      phdrsz                  ; e_phentsize
      phdr:         dd      1                       ; e_phnum       ; p_type
                                                    ; e_shentsize
                    dd      0                       ; e_shnum       ; p_offset
                                                    ; e_shstrndx
      ehdrsz        equ     $ - ehdr
                    dd      $$                                      ; p_vaddr
      _start:       xor     eax, eax                                ; p_paddr
                    jmp     short part2
                    dd      filesz                                  ; p_filesz
                    dd      filesz                                  ; p_memsz
                    dd      5                                       ; p_flags
                    dd      0x1000                                  ; p_align
      phdrsz        equ     $ - phdr
      
      part2:        inc     eax
                    mov     bl, 42
                    int     0x80
      
      filesz        equ     $ - $$

So. Eighty-one bytes. Is that all?

The next field after the p\_paddr field is the p\_filesz field. If only
we could overlap the jmp instruction with that, we could squeeze another
instruction in there. But alas, the first byte of that field is the size
of the entire file, which would be an unwise jump to make. And the
remaining bytes are zeros. That approach doesn\'t look too promising.

What about the field before p\_paddr? That\'s the address the program is
to be loaded at. Well, we already know we don\'t have to use the default
value of 0x08048000. We do need to keep the address page-aligned, at the
very least, but we should be able to fit a two-byte instruction into the
top half of the address. However, our xor won\'t work for that. Remember
that this is little-endian. The bytes of our program are currently:

      31C0              xor        eax, eax
      EB10              jmp        short part2
      
      40        part2:  inc        eax
      B32A              mov        bl, 42
      CD80              int        0x80

The xor instruction would leave C0 as the top byte, which has the high
bit set, and Linux doesn\'t appreciate us putting our code there. (As a
general rule, in a 32-bit executable, the top half of memory is reserved
for dynamically assigned addresses: the heap, the stack, and
shared-object libraries.)

The \"mov bl, 42\" instruction, on the other hand, will give us a
perfectly acceptable top address byte. So, we can change the load
address to 0x2AB30000, and with a little rearranging we have:

      ; tiny.asm
      
      BITS 32
      
                    org     0x2AB30000
      
      ehdr:
                    db      0x7F, "ELF", 1, 1, 1    ; e_ident
            times 9 db      0
                    dw      2                       ; e_type
                    dw      3                       ; e_machine
                    dd      1                       ; e_version
                    dd      _start                  ; e_entry
                    dd      phdr - $$               ; e_phoff
                    dd      0                       ; e_shoff
                    dd      0                       ; e_flags
                    dw      ehdrsz                  ; e_ehsize
                    dw      phdrsz                  ; e_phentsize
      phdr:         dd      1                       ; e_phnum       ; p_type
                                                    ; e_shentsize
                    dd      0                       ; e_shnum       ; p_offset
                                                    ; e_shstrndx
      ehdrsz        equ     $ - ehdr
                    dw      0                                       ; p_vaddr
      _start:       mov     bl, 42
                    xor     eax, eax                                ; p_paddr
                    jmp     short part2
                    dd      filesz                                  ; p_filesz
                    dd      filesz                                  ; p_memsz
                    dd      5                                       ; p_flags
                    dd      0x1000                                  ; p_align
      phdrsz        equ     $ - phdr
      
      part2:        inc     eax
                    int     0x80
      
      filesz        equ     $ - $$

So we are now at seventy-nine bytes. If we can just find room for one
more byte, for the \"inc eax\" instruction, we could replace the jump in
the p\_addr field with the \"int 0x80\", and thus have the entire
program *legally* inside the headers! Just one more lousy byte ...

Perhaps we could just let the last byte of the program spill over into
the next field? That would be the p\_filesz field, which specifies the
size of the program segment in the file. The last byte of the program is
0x80, which is certainly too big to be our file size. That is to say:
Yes, we could lie about the file\'s size, and Linux will look the other
way --- but we\'re supposed to be on the straight and narrow here.

The field after p\_filesz, however, is p\_memsz. If only these two
fields were reversed, there wouldn\'t be a problem. We\'ve looked at
this field before: it specifies how much memory to allocate when loading
the program into memory. Setting that field to be larger than the file
size is perfectly fine.

But here is a way that we can use this field: We can jump over p\_filesz
and into p\_memsz. If we try this, we will find that we can, in fact,
come out ahead:

      ; tiny.asm
      
      BITS 32
      
                    org     0x2AB30000
      
      ehdr:
                    db      0x7F, "ELF", 1, 1, 1    ; e_ident
            times 9 db      0
                    dw      2                       ; e_type
                    dw      3                       ; e_machine
                    dd      1                       ; e_version
                    dd      _start                  ; e_entry
                    dd      phdr - $$               ; e_phoff
                    dd      0                       ; e_shoff
                    dd      0                       ; e_flags
                    dw      ehdrsz                  ; e_ehsize
                    dw      phdrsz                  ; e_phentsize
      phdr:         dd      1                       ; e_phnum       ; p_type
                                                    ; e_shentsize
                    dd      0                       ; e_shnum       ; p_offset
                                                    ; e_shstrndx
      ehdrsz        equ     $ - ehdr
                    dw      0                                       ; p_vaddr
      _start:       mov     bl, 42
                    xor     eax, eax                                ; p_paddr
                    jmp     short part2
                    dd      filesz                                  ; p_filesz
      part2:        inc     eax                                     ; p_memsz
                    int     0x80
                    db      0
                    dd      7                                       ; p_flags
                    dd      0x1000                                  ; p_align
      phdrsz        equ     $ - phdr
      
      filesz        equ     $ - $$

And we have arrived at seventy-six bytes!

This version has the disadvantage that the program requests a fair chunk
of memory. 0x0080CD40 bytes, to be precise, or eight megabytes. (And
note that we now have to add the writeable flag to p\_flags, to allow
that memory to be zero-initialized.) Of course the memory is never
actually accessed, so it hardly matters, what with virtual memory and
all. All this number really indicates is at what address Linux will
report a segfault instead of trying to allocate a page of RAM. So
there\'s no real harm done.

But it turns out there is a way to use a single byte to jump over four
bytes. How? By using a five-byte instruction, of course! Consider a
nice, innocuous instruction like \"cmp eax, imm32\". The only effect it
has is to set the flags. Well, that and it advances the instruction
pointer:

      ; tiny.asm
      
      BITS 32
      
                    org     0x2AB30000
      
      ehdr:
                    db      0x7F, "ELF", 1, 1, 1    ; e_ident
            times 9 db      0
                    dw      2                       ; e_type
                    dw      3                       ; e_machine
                    dd      1                       ; e_version
                    dd      _start                  ; e_entry
                    dd      phdr - $$               ; e_phoff
                    dd      0                       ; e_shoff
                    dd      0                       ; e_flags
                    dw      ehdrsz                  ; e_ehsize
                    dw      phdrsz                  ; e_phentsize
      phdr:         dd      1                       ; e_phnum       ; p_type
                                                    ; e_shentsize
                    dd      0                       ; e_shnum       ; p_offset
                                                    ; e_shstrndx
      ehdrsz        equ     $ - ehdr
                    dw      0                                       ; p_vaddr
      _start:       mov     bl, 42
                    xor     eax, eax                                ; p_paddr
                    inc     eax
                    cmp     eax, strict dword filesz                ; p_filesz
                    int     0x80                                    ; p_memsz
                    dw      0
                    dd      7                                       ; p_flags
                    dd      0x1000                                  ; p_align
      phdrsz        equ     $ - phdr
      
      filesz        equ     $ - $$

The first byte of the compare instruction is at the last byte of the
p\_paddr field, leaving the four bytes of immediate data. Our program
gets a ride across an intact p\_filesz value at half the fare, and that
lets us move the increment instruction out of the p\_memsz field. This
leaves that field holding a value of 0x000080CD, or a little over 32K
--- a much friendlier amount of useless memory to allocate.

------------------------------------------------------------------------

This is the final version of our new program. It is 76 bytes long, so we
have established conformance with the ELF specification at a cost of 31
bytes. Not bad, all things considered. And now we have *two* programs
for which we can say that every byte has been accounted for.

But have we truly silenced the purists?

Some of them, yes. But a few are still present, tapping an accusing
index finger on our int instruction. Oh, yeah. That. Direct system calls
are not actually part of the documented interface with the kernel. (Not
for the likes of us, anyway.) The fact that system call no. 1 is exit
isn\'t guaranteed to stay the same under future revisions. Who knows?
It\'s possible that a later kernel will need to introduce new
functionality to the exit function, and so, in order to maintain binary
backwards-compatibility, they\'ll introduce a new exit function with a
currently-unused system call number, and deprecate the old one.

Admittedly, this is extremely unlikely to happen with such a basic
necessity as exit. But it does happen. For example, there are no less
than *three* system calls that implement the uname function, the first
two having both been deprecated. In order to add more information to the
utsname structure, new system calls had to be introduced, permitting the
older ones to continue to adhere to the original ABI for
backwards-compatibility with older binaries. (If, at some point,
everyone was confident that there were no more older binaries floating
around, those system calls could be removed entirely, and then perhaps
new ones could reuse those numbers. Except of course there are obnoxious
people like me who impede such progress by hard-coding direct system
calls!)

So, okay. If we\'re trying to be completely above-board, then we\'re
still in the doghouse. And the only way out is to strictly adhere to the
documented ABI. In this case, that means we need to exit by using
\_exit. Not the system call, the function. The one that\'s supplied by
libc. Which means that *(groan)* we need to re-introduce all that
dynamic linking overhead that we\'ve so gratefully avoided so far.

That means we need to learn exactly how ELF binaries make dynamic
linking happen, so that we can do it ourselves (and in hopefully less
space). That\'s not a trivial subject, however, so we\'re going to have
to save it for the next essay.

 

[(next)](somewhat.html)

------------------------------------------------------------------------

\
[[Tiny](http://www.muppetlabs.com/~breadbox/software/tiny/)]{.small}\
[[Software](http://www.muppetlabs.com/~breadbox/software/)]{.small}\
[[Brian Raiter](http://www.muppetlabs.com/~breadbox/)]{.small}
