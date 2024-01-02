Some Final Breezes (a postscript)
=================================

I wrote \"A Whirlwind Tutorial \...\" back in July 2, 1999, almost
entirely in one sitting. Having spent months figuring out the ELF
executable file format, and having had all that effort actually pay off
well beyond my original expectations, I wanted to write down all the
paths and blind alleys I had just finished exploring.

I had created a 45-byte executable, and I wanted to share it with the
world.

Over time, I\'ve had a few omissions in the original essay pointed out
to me, which I couldn\'t fix in the original without derailing. (And I
don\'t feel comfortable making significant modifications to the original
at this late date.) So I\'ve put those updates in this postscript
instead.

------------------------------------------------------------------------

When I wrote the original essay, I was unfamiliar with the fact that the
-R option to strip, which removes sections by name, allows you to name
sections that do not get removed by default. With careful use of this
feature of strip, both the C version and the assembly version of the
executable can be reduced a bit more.

Of course, stripping arbitrary sections can easily render your
executable nonfunctional. Even if the sections aren\'t being used, an
executable can\'t be correctly memory-mapped if any file offset doesn\'t
match its equivalent memory-page offset. And in any case, strip won\'t
remove the section header table itself, nor the section header string
table, so hand-coding the binary image is still necessary to get below
the 200-byte mark.

------------------------------------------------------------------------

After producing the seven-byte version of the program, I made the
comment: \"I think it\'s pretty safe to say that we\'re not going to
make this program any smaller than that.\"

Well, actually, it could be made smaller. When Linux starts up a new
executable, one of the things it does is zero out the accumulator (as
well as most of the other registers). Taking advantage of this fact
would have allowed me to remove the xor, bringing the program down to
five bytes. However, this behavior is certainly not documented, and
there\'s no guarantee that it can be counted on to stay that way (other
than the lack of any obvious reason to change it). Anyway, such a change
wouldn\'t have had any effect on the size of the final versions.

------------------------------------------------------------------------

Of course, the biggest omission in the original document is a question I
left unanswered. The following passage used to appear near the end:

> \... it turns out that, contrary to every expectation, the executable
> bit can be dropped from the p\_flags field, and Linux will set it for
> us anyway. Why this works, I honestly don\'t know --- maybe because
> Linux sees that the entry point goes to this segment? In any case, it
> works.

As it turns out, my guess was right --- but only in a twistedly pedantic
way.

I knew, of course, that Linux uses a flat-memory model, in which every
selector register points to the same physical memory area. What I
didn\'t know was that Linux memory is even flatter than that: every
process (except the kernel) uses the exact same set of selectors.

When the kernel boots up, it creates the global descriptor table. One of
the entries in this table is marked as being readable and executable,
and another is marked as being readable and writeable. These two
descriptors are then used as every program\'s cs and ds/es/ss registers.
Changing what these selectors actually point to is then handled at the
paging level, in the linear-to-physical memory translation.

Of course, memory pages have their own, independent protection flags,
but they only indicate read-write vs. read-only. You can\'t mark a page
as being executable or non-executable. (As it turns out, you never need
to set more than one bit of the p\_flags field. Setting either the
readable or the executable bit will create a read-only page, and setting
the writeable bit will create a read-write page.)

So, the actual error in my thinking was assuming that Linux was
allocating selectors for every process. I couldn\'t see why Linux would
even create an executable selector when none of the loadable segments of
the ELF file were marked as being executable. But in reality, Linux had
created the executable selector long before my program was even
compiled.

------------------------------------------------------------------------

Finally, it must be confessed that I have had to make some minor changes
to some of the versions of the program in the essay, as the Linux kernel
has (over the years) become less forgiving about some of the liberties I
originally took.

The first time this happened, it was because the kernel stopped
accepting executables that had an invalid value in the ELF header\'s
e\_phsize field. This only affect one or two of the intermediate
versions of the program, and was relatively easy to fix up.

On the second occasion, one of the early versions of the assembler
started crashing, specifically the one that used \_start and called the
libc exit() function. I had to change it to use \_exit(), and added a
short paragraph to the essay explaining the difference between the two
functions.

The third and most serious change was when the kernel stopped allowing
non-writable memory to be zero-initialized. This required changing the
final versions of the program so that the p\_filesz and p\_memsz were
equal, as well as inserting another explanatory paragraph.

(No further breakages have occurred since that one, and hopefully as
32-bit kernels become obsolete, the kernel code supporting 32-bit
executables will remain as-is for the foreseeable future.)

 

[(next)](revisit.html)

------------------------------------------------------------------------

\
[[Tiny](http://www.muppetlabs.com/~breadbox/software/tiny/)]{.small}\
[[Software](http://www.muppetlabs.com/~breadbox/software/)]{.small}\
[[Brian Raiter](http://www.muppetlabs.com/~breadbox/)]{.small}
