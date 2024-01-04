
BrainFuck compiler 1.0 for MSX-DOS Made By: NYYRIKKI 2002
---------------------------------------------------------

Files in this package:
----------------------
BF8     .COM	BrainFuck compiler
BF8     .BF	BrainFuck compiler sourcecode.
BF8     .TXT	BrainFuck compiler manual.
BITDBL  .BF	Bit Doubler. (Run 16bit BF in 8bit environment)
BITDBL  .TXT	Bit Doubler manual.
HELLOYOU.BF	"Hello you" programming example
TRIANGLE.BF	Sierpinski Triangle fractal written with BF
99BOTLES.BF	Prints out words of "99 botles of beer" song.
2D_TABLE.BF	Example of using 2D tables in BF
DECSS   .BF	DVD decryption algorithm (DeCSS) written in BF
README  .TXT    This file
LINKS   .TXT    Internet links to BrainFuck sources (like DeCSS and Game of life).


BrainFuck
---------

Brainfuck is an incredibly easy to learn language. It is annoying to program, but it has a great teaching value. It was most probably created around 1993. It's author is Urban Müller from Switzerland, who also wrote the original interpreter for brainfuck and a compiler for the Amiga.

Brainfuck is designed to be one the most compact languages possible while still being turing complete. While brainfuck has only 8 commands, it is still possible to do anything in it that can be done in other languages.

The Language
------------
A Brainfuck program has an implicit byte pointer, called "the pointer", which is free to move around within an array of about 30000 bytes, initially all set to zero. The pointer itself is initialized to point to the beginning of this array. 

The Brainfuck programming language consists of eight commands, each of which is represented as a single character. They are:

+  Increment byte under pointer  
-  Decrement byte under pointer  
>  Increment pointer  
<  Decrement pointer  
[  Loop while byte under pointer is nonzero  
]  End of loop  
,  Read character from keyboard and store it in the byte at the pointer
.  Output byte under pointer to screen  


I think, that Ben Olmstead wrote very well description of this language: "Believe it or not this language is indeed Turing complete. It combines the speed of BASIC with the ease of INTERCAL and the readability of an IOCCC entry."

I hope you find it interesting writing programs to this language. Read the sources and learn. :-)

			    ,_____.
		    _=_=_=_=!_MSX_!=_=_=_=_=_=_=_=_,
		   ! A1GT ~--- - I  ( o o o o o o )i
		  /--------------------------------`,
		 / .::::::::::::::::::::::;::;	::::.,
		/ :::.:.:.:::____________:::::!.  -=- `,
		~======================================
		                NYYRIKKI

