%{
/*
 
For the information of some:
 
B1FF is a fictitious person who is "new" on the 'net.
 
You can recognize his posts by:
 
  He always SHOUTS as he types.
 
  He sometimes spells FONET1KLEE (phonetically) the rest of the time, he  
    just misspells words or punctuates them incorrectly.
 
  He shortens some words (presumably for ease in typing)
   like '4' for 'for' or 'four'
   like '2' for 'two' or 'to' or 'too'
   like '&' for 'and'
   like 'U' for 'you' or 'ewe'
   like 'R' for 'are'
   like 'C' for 'sea' or 'see'
  
He can't see the difference between certain letters
       like '1' and 'i'
    or like '0' and 'o'
    or like '5' and 's'
    or like '2' and 'z'
 
  His speech is peppered with profanity.
 
  He never uses only one '!' or '?' when '!!!!!!!!' or '????!!!!' will do.
 
  He never uses the apostrophe (') and always uses the double quote (")
     instead.
 
  I have some vague memory of B1FF being mentioned in the New Hackers
dictionary, but I can't verify the validity of this.
 
  I can't even validate that his full name is NELSON 0TB1FF , but it sounds
correct.
*/
 
/*
Here's the promised and long-awaited 'b1ff.x' English->B1FF converter
that everyone's been clamoring for. I made a few small changes since the
last version and made sure that it compiled correctly.
 
To compile this, save it to the file 'b1ff.x' and execute the following
two commands:
	lex b1ff.x
	cc -o B1ff lex.yy.c -ll
 
Note that the flags on cc should be in that order. You'll end up with the
executable 'B1ff' (if you call it 'biff' with a lowercase 'b' you'll
conflict with the biff mail-checking program). 
 
Send me any bugs or patches; I'm good friends with B1FF and since this is 
the first program he's ever posted to the net, he wants to know if you
have any problems. 
 
mdw
*/
 /* 
  * B1FF.X by Matt Welsh (mdw@tc.cornell.edu) +1 607 253 2737
  *  modified and improved by David Whitten 
  *
  * $Id: b1ff.x,v 1.1 92/11/03 18:31:10 mdw Exp Locker: mdw $
  * $What: <@(#) b1ff.x,v	1.13> $
  *
  * Simulates our favorite guy, the B1FFSTER!!!!1!!!
  *
  * To compile, do the following:
  *
  *   lex b1ff.x
  *   cc -o B1ff lex.yy.c -ll
  *
  * Yes, this is very poorly written, and yes, it was a late-night hack.
  * But it seems to work, mail me if it doesn't compile, or if you find 
  * any bugs or make any additions.
  * Happy B1FFing,
  * 
  * mdw
  * 
  */
 
    char buf[128];
%}
 
 
BW [ 	]
EW [ 	.,;!?]
WC		[A-Za-z']
NW		[^A-Za-z']
 
%start		INW NIW 
%e 3000
%p 6000
%n 1000
%k 500
%a 4000
%o 15000
 
%%
 
\\[^ \n]+	ECHO;
 
{NW}		{ BEGIN NIW; ECHO; }
"..."           { BEGIN NIW;
			printf((rand()%2) ? "...C00L HUH!?! " : "...!! "); }
"."/{NW}	{ BEGIN NIW; printf((rand()%2) ? "." : "!!" ); }
".\""           { BEGIN NIW; printf((rand()%2) ? "!!!\"" : "!1!!\"" ); }
"!"$            { BEGIN NIW; printf("!!!!!!!!!!1"); }
"!"+/{NW}       { BEGIN NIW; printf("!1!"); }
"?"/{NW}        { BEGIN NIW; printf("??!!"); }
"?"             { BEGIN NIW; printf("?!");  }
":)"            { BEGIN NIW; printf(";-)!!! "); }
"8)"            { BEGIN NIW; printf(";-)!!! "); }
":*)"           { BEGIN NIW; printf(";-)!!!!  "); }
":-)"           { BEGIN NIW; printf(";-)!!!!  "); }
"'"             { BEGIN NIW; printf("\""); }
 
"ove"           { BEGIN INW; printf("UV "); }
"move"		{ BEGIN INW; printf("MOOV"); }
"ea"            { BEGIN INW; printf("EE"); }
"ies"           { BEGIN INW; printf("YS"); }
"please"        { BEGIN INW; printf("PLEEZ!"); }
"Please"        { BEGIN INW; printf("PLEEZ"); }
"Thanks"        { BEGIN INW; printf("THANX!!"); }
"thanks"        { BEGIN INW; printf("THANX"); }
"enough"        { BEGIN INW; printf("ENUF"); }
"Enough"        { BEGIN INW; printf("ENUFF"); }
"does"          { BEGIN INW; printf("DUZ"); }
"Does"          { BEGIN INW; printf("DUZ"); }
"fuck"/{NW}     { BEGIN INW; printf("FUCK !!!!!1 "); }
"Fuck"/{NW}     { BEGIN INW; printf("FUCK !!!!!1 "); }
"damn"          { BEGIN INW; printf("FUCK!! "); }
<NIW>"hell"/{NW}          { BEGIN INW; printf("FUCK!! "); }
"Damn"          { BEGIN INW; printf("FUCK!! "); }
"Shit"          { BEGIN INW; printf("FUCK!! "); }
"shit"          { BEGIN INW; printf("FUCK!! "); }
<NIW>"Hell"/{NW}          { BEGIN INW; printf("FUCK!! "); }
<NIW>"dick"/{NW}          { BEGIN INW; printf("FUCK!! "); }
<NIW>"Dick"/{NW}          { BEGIN INW; printf("FUCK!! "); }
<NIW>"mad"/{NW} { BEGIN INW; printf("PISSED 0FF!!!1! "); }
<NIW>"Mad"/{NW} { BEGIN INW; printf("PISSED 0FF!!!1! "); }
"ar"/{NW}       { BEGIN NIW; printf("RE"); }
"are"/{NW}      { BEGIN INW; printf("R"); }
"ain"/{NW}      { BEGIN NIW; printf("ANE"); }
"before"/{NW}	{ BEGIN NIW; printf("B4");}
"for"/{NW}	|
"fore"/{NW}	{ BEGIN NIW; printf("4");}
"four"/{NW}	{ BEGIN NIW; printf("FORE ");}
"sea"/{NW}	|
"see"/{NW}	{ BEGIN NIW; printf("C ");}
"to"/{NW}       |
"too"/{NW}      { BEGIN NIW; printf("2"); }
"two"/{NW}      { BEGIN NIW; printf("TO "); }
"one"/{NW}      { BEGIN NIW; printf("1"); }
<INW>"ould"/{NW} {BEGIN NIW; printf("UD ");}
"ic"/{NW}       { BEGIN NIW; printf("IK"); }
"le"/{NW}       { BEGIN NIW; printf("EL"); }
"by"/{NW}       { BEGIN NIW; printf("BUY"); }
"buy"/{NW}      { BEGIN NIW; printf("BY"); }
"bye"/{NW}      { BEGIN NIW; printf("BY"); }
"e"/{NW}        { BEGIN NIW;
			 printf((rand()%2) ? "E" : (rand()%2 ? "E" : "3"));}
"ewe"		|
"you"           { BEGIN INW; printf("U"); }
"your"          { BEGIN INW; printf("YOU'RE"); }
"there"         { BEGIN INW; printf("THARE"); }
"they're"       { BEGIN INW; printf("THARE"); }
"cause"         { BEGIN INW; printf("CUZ"); }
<INW>"or"       { BEGIN INW; printf((rand()%2) ? "OR" : "ER"); }
"and"           { BEGIN INW; printf("&"); }
"biff"          { BEGIN INW; printf("B1FFSTER!!!!!"); }
"BIFF"          { BEGIN INW; printf("B1FFSTERE!!!1!"); }
"Biff"          { BEGIN INW; printf("B1FFSTERE!!!1!"); }
"tion"          { BEGIN INW; printf("SHUN"); }
"good"		|
"cool"          { BEGIN INW; printf("C00L!!!"); }
"computer"      { BEGIN INW; printf("C-64"); }
"software"      { BEGIN INW; printf("WAREZ!1!!"); }
"program"       { BEGIN INW; printf("WAREZ!1!!"); }
"gal"		|
"girl"		|
"woman"		{ BEGIN INW; printf("BAB3"); }
"boy"		|
"dude"		|
"Mr"            |
"man"/{NW}      |
"Man" 		{ BEGIN INW; printf("D00D"); }
"some"          { BEGIN INW; printf("SUM"); }
 
"a"             { BEGIN INW; printf("A"); }
"b"             { BEGIN INW; printf("B"); }
"c"             { BEGIN INW; printf("C"); }
"d"             { BEGIN INW; printf("D"); }
"e"             { BEGIN INW; printf("E"); }
"f"             { BEGIN INW; printf("F"); }
"g"             { BEGIN INW; printf("G"); }
"h"             { BEGIN INW; printf("H"); }
"i"             { BEGIN INW; printf((rand()%2) ? "I" : "1"); }
"I"             { BEGIN INW; printf((rand()%2) ? "I" : "1"); }
"j"             { BEGIN INW; printf("J"); }
"k"             { BEGIN INW; printf("K"); }
"l"             { BEGIN INW; printf("L"); }
"ll"            { BEGIN INW;
			 printf((rand()%2) ? "LL" : (rand()%2 ? "L" : "LLL"));}
"m"             { BEGIN INW; printf("M"); }
"n"             { BEGIN INW; printf("N"); }
"nn"            { BEGIN INW;
			 printf((rand()%2) ? "NN" : (rand()%2 ? "N" : "NNN"));}
"o"             { BEGIN INW; printf("0"); }
"oo"            { BEGIN INW; 
			  printf((rand()%2) ? "00" : "UU"); }
"O" 		{ BEGIN INW; printf("0"); }
"OO"            { BEGIN INW; 
			  printf((rand()%2) ? "00" : "UU"); }
"ph"            { BEGIN INW; printf("F"); }
"Ph"            { BEGIN INW; printf("F"); }
"p"             { BEGIN INW; printf("P"); }
"q"             { BEGIN INW; printf("Q"); }
"r"             { BEGIN INW; printf("R"); }
"s"             { BEGIN INW; printf((rand()%2) ? "5" : "S"); }
"S"             { BEGIN INW; printf((rand()%2) ? "5" : "S"); }
"t"             { BEGIN INW; printf("T"); }
"u"             { BEGIN INW; printf("U"); }
"v"             { BEGIN INW; printf("V"); }
"w"             { BEGIN INW; printf("W"); }
"x"             { BEGIN INW; printf("X"); }
"y"             { BEGIN INW; printf("Y"); }
"z"             { BEGIN INW; printf((rand()%2) ? "2" : "Z"); }
.		printf(yytext);
\n		printf("\n");
.		{ BEGIN INW; ECHO; }
 
%%
 
main()
{
	srand(getpid());
	yylex();
	return(0);
}
