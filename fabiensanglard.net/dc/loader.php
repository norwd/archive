<html>
<head>
<style>
	* {
		font-size: 100%;
	}
	html {
	max-width: 900px;
	font-family : Verdana, "Bitstream Vera Sans", "DejaVu Sans", Tahoma, Geneva, Arial, Sans-serif;
	text-align: justify;
	hyphens: auto;
	margin: 0 auto;
    padding-left: 2%;
    padding-right: 3%;
    color:#444;
}

pre {
	background-color: #EEE;
	border: solid black 1px;
	padding: 1ch;
	padding-left:2ch;
	overflow: scroll;
}

code {
/*	font-size: 110%;*/
	font-weight: bold;
	background-color: #e1e1e1;
	border-radius: 0.5ch;
	padding-left: 0.3ch;
	padding-right: 0.3ch;
}

img {
	border: 1px solid black;
}

h1 {
	page-break-before: right;
	font-weight: bold;
	text-transform: uppercase;
	font-size: 140%;
	margin-top: 3ch;
	margin-bottom: 0.5ch;
}

h2 {
	margin-top: 3ch;
}

h3 {
	color: #999;
}
.lined th {
	background-color: #EEE;
	

}
table.lined, .lined th, .lined td{
   border: 1px solid black; 
   border-collapse: collapse; 
   border-spacing : 0x;
   text-align: center;
}

table {
	margin-top: 2ch;
	width: 100%;
}

td pre {
	vertical-align: top;
}

span.r{
	color:red;
	font-weight: bold; 
}

span.g{
	color:green;
	font-weight: bold; 
}

span.b{
	color:blue;
	font-weight: bold; 
}

span.h{
	font-weight: bold; 
}

span.k{
	font-weight: bold; 
	color:orange;
}

div.t {

	padding-left: 1ch;
	border-left: solid 1px black;
	margin-bottom: 2ch;
}
div.t:before {
	content: "Trivia:";
	white-space: nowrap;
	text-decoration: underline;
	font-weight: bold; 
}

  	a {
      color:#444;
      font-weight: bold;
    }

.arrow {
	text-decoration: none;
}    

.center {
  display: block;
  margin-left: auto;
  margin-right: auto;
}

</style>

<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=12.0, minimum-scale=1.0, user-scalable=yes">

<title>Driving Compilers</title>
</head>
<body>
	<a href="index.php">
<h1 style="text-align: center; margin-bottom:4ch;padding-top: 1ch;">Driving Compilers</h1>
</a>

<p style="float:left;font-size: 90%;">
By <b>Fabien Sanglard</b><br/>
May 3rd, 2023<br/>
</p>
<p style="float:right; font-size: 90%;padding-bottom: 4ch;text-align: center;">
<a href="https://github.com/fabiensanglard/dc">Mistake - Suggestion <br/> Feedback</a>
</p>
<div style="clear:both;">



	<h1>The Loader (5/5)</h1>
  <a class="arrow" href="ld.php">←</a> <a class="arrow"  style="visibility:hidden;" href="ld.php">→</a> 
	<hr/>

  <div style="width:30%;float: right; margin-left: 2ch; margin-bottom: 2ch;">
<table class="lined" style="width: 100%; text-align: center; margin-top: 0;">
  <tr>
   <td colspan="4">driver
    </td><td style="border-top-style: hidden; border-right-style: hidden;"></td>
  </tr>

  <tr>
    <td>cpp</td>
    <td>cc</td>
    <td>ld</td>
    <td>exec</td>
    <td>loader<span class="r">*</span></td>
  </tr>
</table>
</div>

	
	<p>This is beyond what a programmer needs to know but it can come handy to have a rough idea of how a program runs. This is what this page is for.
	</p>
	<p>
		The output of the linker is meant to be loaded by the OS loader when the program starts. The loader maps segments to memory, loads dynamic dependencies, resolves dynamic symbols, and points the CPU to the <code>_start</code> symbol.</p>

<h2>Finding the loader</h2>
<p>Linux finds the loader (a.k.a interpreter) by fetching the value in section <code>.interp</code>. It can be displayed using <code>file</code>.
</p>
<pre><b>$</b> file a.out
a.out: ELF 64-bit LSB pie executable, ARM aarch64, dynamically linked, interpreter <span class=r>/lib/ld-linux-aarch64.so.1</span></pre>











	<h2>Mapping segments to memory</h2>
	<p>The interpreter looks at the segments and simply follows instructions.</p>

	<pre>$ readelf -l -W a.out

Elf file type is DYN (Position-Independent Executable file)
Entry point 0x600
There are 9 program headers, starting at offset 64

Program Headers:
  Type           Offset   VirtAddr           PhysAddr           FileSiz  MemSiz   Flg Align
  PHDR           0x000040 0x0000000000000040 0x0000000000000040 0x0001f8 0x0001f8 R   0x8
  INTERP         0x000238 0x0000000000000238 0x0000000000000238 0x00001b 0x00001b R   0x1
      [Requesting program interpreter: /lib/ld-linux-aarch64.so.1]
  LOAD           0x000000 0x0000000000000000 0x0000000000000000 0x0008c4 0x0008c4 R E 0x10000
  LOAD           0x000dc8 0x0000000000010dc8 0x0000000000010dc8 0x000268 0x000270 RW  0x10000
  DYNAMIC        0x000dd8 0x0000000000010dd8 0x0000000000010dd8 0x0001e0 0x0001e0 RW  0x8
  NOTE           0x000254 0x0000000000000254 0x0000000000000254 0x000044 0x000044 R   0x4
  GNU_EH_FRAME   0x000794 0x0000000000000794 0x0000000000000794 0x00004c 0x00004c R   0x4
  GNU_STACK      0x000000 0x0000000000000000 0x0000000000000000 0x000000 0x000000 RW  0x10
  GNU_RELRO      0x000dc8 0x0000000000010dc8 0x0000000000010dc8 0x000238 0x000238 R   0x1

</pre>

<p><code>LOAD</code> segments are mmaped to memory. The instructions in section <code>.text</code> and read-only data in section <code>.rodata</code> are grouped in the same segment to minimize the number of calls to <code>mmap</code>. This segment is loaded in <code>R_E</code> (Readable, Executable) memory. The second <code>LOAD</code> segment in our example contains mutable variables, and therefore has flag <code>RW_</code>.
	</p>
	<p>Notice how debug segments are not marked as <code>LOAD</code>, they are consulted on a needed basis. The <code>DYNAMIC</code> segment contains the information to load dynamic libraries and relocate symbols.</p>











	<h2>Dynamic libraries loading</h2>
	<p>The list of undefined symbols, expected to be found in dynamic libraries, can be examined with <code>nm</code>.
	</p>

	<pre><b>$</b> nm a.out
                 U abort@GLIBC_2.17
                 U __libc_start_main@GLIBC_2.34
0000000000000754 T main
                 U printf@GLIBC_2.17
0000000000000640 T _start
</pre>

	<p>
The list of dynamic libraries where these undefined symbols will be searched can be obtained via <code>ldd</code>.
	</p>
	


	<pre><b>$</b> ldd a.out
	linux-vdso.so.1 (0x0000ffff8de9b000)
	libc.so.6 => /lib/aarch64-linux-gnu/libc.so.6 (0x0000ffff8dc70000)
	/lib/ld-linux-aarch64.so.1 (0x0000ffff8de62000)</pre>

<p>Keep in mind that <code>ldd</code> is a convenient <a href="https://stuff.mit.edu/afs/sipb/project/phone-project/bin/arm-linux-ldd">script</a> which merely invokes <code>ld</code> on the current system.</p>

  <pre><b>$</b> <span class="r">LD_TRACE_LOADED_OBJECTS=1</span> <span class="b">ld</span> a.out
  linux-vdso.so.1 (0x0000ffff8de9b000)
  libc.so.6 => /lib/aarch64-linux-gnu/libc.so.6 (0x0000ffff8dc70000)
  /lib/ld-linux-aarch64.so.1 (0x0000ffff8de62000)</pre>


<p>In you are analyzing a file built for another system, it may fail. In this case you may want to look up the dynamic section and keep only <code>NEEDED</code> entries.</p>


<pre><b>$</b> readelf -d a.out | grep 'NEEDED'
 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
	</pre>


<div class="t"> The interpreter used to load an <code>.so</code> is not necessarily the same as the one used to load the "main" program. All <code>.so</code> have a hard-coded interpreter path.
</div>


<h2>Symbols relocation</h2>
<p>When everything is properly mapped to memory, the loader performs symbol relocation. This is something we already looked at in the linker when this data was being generated. We can recognize here the name of the undefined symbols <code>nm</code> revealed to us.</p>

<pre><b>$</b> readelf -r a.out

Relocation section '.rela.dyn' at offset 0x480 contains 8 entries:
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000010dc8  000000000403 R_AARCH64_RELATIV                    750
000000010dd0  000000000403 R_AARCH64_RELATIV                    700
000000010fd8  000000000403 R_AARCH64_RELATIV                    754
000000011030  000000000403 R_AARCH64_RELATIV                    11030
000000010fc0  000400000401 R_AARCH64_GLOB_DA 0000000000000000 _ITM_deregisterTM[...] + 0
000000010fc8  000500000401 R_AARCH64_GLOB_DA 0000000000000000 __cxa_finalize@GLIBC_2.17 + 0
000000010fd0  000600000401 R_AARCH64_GLOB_DA 0000000000000000 __gmon_start__ + 0
000000010fe0  000800000401 R_AARCH64_GLOB_DA 0000000000000000 _ITM_registerTMCl[...] + 0

Relocation section '.rela.plt' at offset 0x540 contains 5 entries:
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000011000  000300000402 R_AARCH64_JUMP_SL 0000000000000000 <span class="r">__libc_start_main@GLIBC_2.34</span> + 0
000000011008  000500000402 R_AARCH64_JUMP_SL 0000000000000000 __cxa_finalize@GLIBC_2.17 + 0
000000011010  000600000402 R_AARCH64_JUMP_SL 0000000000000000 __gmon_start__ + 0
000000011018  000700000402 R_AARCH64_JUMP_SL 0000000000000000 <span class="r">abort@GLIBC_2.17</span> + 0
000000011020  000900000402 R_AARCH64_JUMP_SL 0000000000000000 <span class="r">printf@GLIBC_2.17</span> + 0
</pre>



<h2>Branching the CPU</h2>
<p>Finally, everything is ready to run. The interpreter only needs to point the processor to the start of the program. The virtual address to use comes from the ELF header.</p>
<pre><b>$</b> readelf -h a.out
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              DYN (Position-Independent Executable file)
  Machine:                           AArch64
  Version:                           0x1
  <span class="r">Entry point address:               0x640</span>
  Start of program headers:          64 (bytes into file)
  Start of section headers:          8072 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         9
  Size of section headers:           64 (bytes)
  Number of section headers:         36
  Section header string table index: 35

</pre>

<p>And that's it for now :) !</p>



<hr/>
 <center>*</center>

</body>
</html>