The Return 42 Collection
========================

These programs all do the same thing, which is exit with a value of 42.
In other words, the absolute minimum while still being able to
demonstrate that they did, in fact, do something. Several of these
programs are described in detail in other essays; they are included here
for the sake of completeness.

If you wish to verify for yourself that these programs do, in fact,
work, you can download the assembler source files and build them with
[nasm](http://www.nasm.us). Each program includes explicit build
instructions at the top of the source file.

[tiny-i386.asm source](tiny-i386.asm.txt)\
[tiny-i386 binary](tiny-i386)\
45 bytes

This is the final version of the program from [the original
essay](teensy.html). This is the smallest a Linux ELF executable can be.

[tiny-elf32.asm source](tiny-elf32.asm.txt)\
[tiny-elf32 binary](tiny-elf32)\
76 bytes

This is the final version of the program from [the second
essay](revisit.html). This is the smallest a Linux ELF executable can be
without violating the requirements described in the ELF specification.

[tiny-libc.asm source](tiny-libc.asm.txt)\
[tiny-libc binary](tiny-libc)\
297 bytes

This is the final version of the program from [the third
essay](somewhat.html). This is the smallest Linux ELF executable I have
been able to create while being fully standards-compliant and linking
with libc. I do not know if a smaller executable is possible.

[tiny-x64.asm source](tiny-x64.asm.txt)\
[tiny-x64 binary](tiny-x64)\
80 bytes

Occasionally people wonder if Linux\'s handling of 64-bit ELF files
allows for a similar range of devious compression. In general, 64-bit
ELF files are both larger and less forgiving of invalid values than
their 32-bit counterparts. But that doesn\'t mean that nothing can be
done. This 80-byte binary is a minor variation of one that was created
by Oleg Finkelshteyn, making use of an excellent but narrow window for
overlap. (In contrast to the 32-bit ELF, I do *not* know if a smaller
64-bit ELF is possible. We know that a 64-bit ELF binary cannot be
smaller than 64 bytes, so that leaves a 16-byte range in which a smaller
ELF file might exist. I currently do not see a way to make a working
file less than 80 bytes, but that doesn\'t mean it can\'t be done.)

[tiny-elf64.asm source](tiny-elf64.asm.txt)\
[tiny-elf64 binary](tiny-elf64)\
120 bytes

For the sake of completeness, here\'s a 64-bit executable that adheres
to all requirements of the ELF specification. Frustratingly, I have been
entirely unable to overlap the program segment header table at all with
the ELF header, so the only creative space-saving in this program comes
from storing the program instructions in the p\_vaddr and p\_paddr
fields.

[tiny-aout.asm source](tiny-aout.asm.txt)\
[tiny-aout binary](tiny-aout)\
35 bytes

ELF is hardly the only executable file format that Linux kernels can
support. Though it\'s uncommon now, at one time the native Linux
executable format was a.out files. The a.out format is very simple,
having only limited support for dynamic linking. The a.out header is
only 32 bytes, so it can easily be smaller than the smallest ELF
executable. (Note: the last time I tested this binary --- admittedly
many years ago --- the kernel would complain about a.out binaries with a
size that was not evenly divisible by 4K, but it would still allow them
to run.)

------------------------------------------------------------------------

\
[[Tiny](http://www.muppetlabs.com/~breadbox/software/tiny/)]{.small}\
[[Software](http://www.muppetlabs.com/~breadbox/software/)]{.small}\
[[Brian Raiter](http://www.muppetlabs.com/~breadbox/)]{.small}
