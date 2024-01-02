[Jan\'s Blog!](https://blog.mandejan.nl/)\

[**Start**](/). [**About**](/about.html).

::: {role="main"}
Smallest Echo, Part 1: Zig
==========================

**30.08.2020 22:11**

<div>

I was inspired by reading this blog
<https://briancallahan.net/blog/20200812.html> Where the author wants is
building the smallest executable echo binary for an x86\_64 linux
system. In the blog he gets to 848 bytes with programming in assembly
and to 840 bytes when compiling a C version of the program with Clang. I
really like optimizing code for size so I made myself this challenge to
see how much further this could be pushed! Since the original post
already covered C, lets start with a naive implementation of echo in my
favorite compiled language, [Zig](https://ziglang.org)!

9568 bytes {#9568-bytes}
----------

::: {.highlight}
``` {.chroma}
const std = @import("std");
const io = std.io;
const process = std.process;


pub fn main() !void {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    const allocator = &arena.allocator;
    var args = try process.argsAlloc(allocator);
    defer process.argsFree(allocator, args);

    const stdout_stream = io.getStdOut().outStream();

    var arg_idx: usize = 1; // skip exe name
    
    while (nextArg(args, &arg_idx)) |arg| {
        try stdout_stream.writeAll(arg);
        if (arg_idx != args.len) {
            try stdout_stream.writeByte(' ');
        }
    }
    try stdout_stream.writeByte('\n');
}

fn nextArg(args: [][]const u8, idx: *usize) ?[]const u8 {
    if (idx.* >= args.len) return null;
    defer idx.* += 1;
    return args[idx.*];
}
```
:::

build with:
`zig build-exe echo.zig --release-small --single-threaded && strip echo`
this produces a binary thats 9568 bytes in size, that not bad and
certainly a lot smaller than the echo included with a linux distribution
(though we have a lot less options). But it's certainly not as small as
the 840 bytes Brian managed to achieve with C in his blogpost. So where
do we start saving? The current program is quite naive, so naive infact
that when you add `-target native-windows` to the Zig compile options it
even works on windows! While building crossplatfrom code is very neat,
assuming a linux os can save us a lot of bytes. So lets rewrite our code
to be compatible with linux only.

1752 bytes {#1752-bytes}
----------

::: {.highlight}
``` {.chroma}
const std = @import("std");
const linux = std.os.linux;

pub fn main() void {
    const args = std.os.argv;
    
    for (args[1..]) |arg, i| {
        _ = linux.write(1, arg, std.mem.len(arg));
        if (i != args.len - 2) _ = linux.write(1, " ", 1);
    }
    _ = linux.write(1, "\n", 1);
}
```
:::

Now that we've thrown away a lot of code that was helping us make our
program cross platform we no longer need code for allocating arguments
and we can use linux syscalls directly. This brings the size down to
just 1752 bytes, but that's still not anywhere near 840, so next up lets
see whats actually in the binary!

running `readelf -s echo` reveals there are still several functions in
included in the binary, they are: `_start`,
`std.start.posixCallMainAndExit`, `std.os.abort`, `std.os.raise`

Apart from our entrypoint `_start`, we don't really need those other
functions, so lets ditch them! posixCallMainAndExit is Zig's "main"
function. Luckily it is really easy to get rid of the main function in
Zig and define your own entry point:

800 bytes {#800-bytes}
---------

::: {.highlight}
``` {.chroma}
const std = @import("std");
const linux = std.os.linux;

pub export fn _start() callconv(.Naked) noreturn {
    const starting_stack_ptr: [*]usize = asm (""
        : [argc] "={rsp}" (-> [*]usize)
    );
    const argc = starting_stack_ptr[0];
    const argv = @ptrCast([*][*:0]u8, starting_stack_ptr + 1);

    for (argv[1..argc]) |arg, i| {
        _ = linux.write(1, arg, std.mem.len(arg));
        if (i != argc - 2) _ = linux.write(1, " ", 1);
    }
    _ = linux.write(1, "\n", 1);

    linux.exit(0);
}
```
:::

By looking at [Zig's main
function](https://github.com/ziglang/zig/blob/master/lib/std/start.zig)
and only taking the parts we actually need and building our own
entrypoint we manged to save almost an entire kilobyte. We finally beat
Brian's original C implementation by 40(!) bytes. But why stop here?
Let's analyze the binary and see if there is more to be saved! Running
`readelf -S echo` reveals that there some sections left, even after
running the `strip` command, not all of which are neccesary, like the
`.comment` section. While you could carve out sections of an elf file
like so: `objcopy --remove-section .comment echo`. There is a very nice
command line utility from the
[ELFKickers](http://www.muppetlabs.com/~breadbox/software/elfkickers.html)
collection called `sstrip` this amazing little tool can really strip out
every unneeded byte from an elf file, so lets try it! running
`sstrip -z echo` instead of `strip` on the echo binary from the previous
code snippet results in a 425 bytes file. Wow! this tool almost cut the
size of out binary in half! Without affecting the functionallity of the
program at all. Incredible. Unfortunatly running the tools twice does
not make the binary half in size again magically. So lets take another
look at our algorithm and see if we can do some more optimizations in
the code!

408 bytes {#408-bytes}
---------

::: {.highlight}
``` {.chroma}
const std = @import("std");
const linux = std.os.linux;

pub export fn _start() callconv(.Naked) noreturn {
    const starting_stack_ptr = asm (""
        : [argc] "={rsp}" (-> [*]usize)
    );
    const argc = starting_stack_ptr[0];
    var argv = @ptrCast([*][*:0]u8, starting_stack_ptr + 1);

    for (argv[1..argc]) |arg, i| {
        var len: u64 = std.mem.len(arg);
        arg[len] = ' ';
        if (i == argc - 2) len -= 1;
        _ = linux.write(1, arg, len + 1);
    }
    _ = linux.write(1, "\n", 1);

    linux.exit(0);
}
```
:::

One optimization we can make is using the space the linux kernel kindly
provided to us when it allocated the program arguments for us for our
echo program we need to write a space after every argument except the
last, then we need to write a newline. Instead of storing a string with
a space in the binary, loading a pointer to it and doing a seperate
syscall, we can store the space at place of the null byte at the end of
the string. It would save even more bytes if we could do the same for
the newline, unfortunatly the newline also needs to be printed if there
are no arguments supplied to the echo program.

277 bytes {#277-bytes}
---------

::: {.highlight}
``` {.chroma}
const std = @import("std");
const linux = std.os.linux;

pub export fn _start() callconv(.Naked) noreturn {
    const starting_stack_ptr = asm (""
        : [argc] "={esp}" (-> [*]usize)
    );
    const argc = starting_stack_ptr[0];
    var argv = @ptrCast([*][*:0]u8, starting_stack_ptr + 1);

    for (argv[1..argc]) |arg, i| {
        const len = @intCast(u32, std.mem.len(arg));
        arg[len] = ' ';
        _ = linux.write(1, arg, len + 1);
        if (i == argc - 2) break;
    }
    _ = linux.write(1, "\n", 1);

    linux.exit(0);
}
```
:::

For this massive save we can thank intel and linux for 35 years of
backwards compatibility! I modified the program slightly so it could be
compiled for the intel i386 architecture. I then added
`-target i386-native` to the Zig compile flags and it produced a 32 bit
elf. 32 bit elfs are a lot smaller simply due to the wordsize being half
as large as on a 64 bit platform. This saves a lot in header space, and
also in instruction size! Our echo binary doesn't need 64 bit words
anyway. The only difference in functionality is that the stringlength of
one argument may not exceed 2^32^. Which is far larger than the linux
kernel allows anyways. I think it's reasonable to say this is the
farthest it can be pushed with ordinary programming languages, if we
want to make it smaller we'll have to start getting our hands dirty with
assembly... That's it for now! In the next part we'll leave Zig behind,
and venture into the depths of the x86 programming manual.

[Part 2](/posts/smallest-echo-2.html)

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
