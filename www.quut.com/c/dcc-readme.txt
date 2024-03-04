/* DCC.README */
			dcc version 0.19, December 22th, 1995

Introduction

dcc is a C checker program, described in the December 1995 issue of ACM SIGPLAN
Notices.


Copyright

//  Copyright Ecole Superieure d'Electricite, France, 1995.
//  All Rights Reserved.


Licence agreement

// SUPELEC 'dcc' END USER LICENSE AGREEMENT NO FEE VERSION
// 
// GRANT.  Ecole Superieure d'Electricite ("Supelec") hereby grants you a non-
// exclusive license to use its accompanying software product ("Software") free
// of charge if (a) you are a student, faculty member or staff member of an
// educational institution or an employee of a charitable non-profit organiza-
// tion; or (b) your use of the Software is for the purpose of evaluating whe-
// ther to purchase an ongoing license to the Software. The evaluation period
// for use by or on behalf of a commercial entity is limited to 90 days; evalu-
// ation use by others is not subject to this restriction. Government agencies
// are not considered charitable non-profit organizations for purposes of this
// license agreement.
// If you do not fit within the description above, a license fee is due to
// Supelec and no license is granted.
// If you fit within the above description, you may: use the Software on any
// single computer; use the Software on a second computer so long as the first
// and second computers are not used simultaneously; or copy the Software for
// archival purposes, provided any copy must contain all of the original
// Software's proprietary notices.
// You may not: permit other individuals to use the Software except under the
// terms listed above; copy the Software (except for back-up purposes); rent,
// lease, transfer or otherwise transfer rights to the Software; or remove any
// proprietary notices or labels on the Software.
// If you are using the Software free of charge, you will not be entitled to
// telephone assistance.
// 
// SOFTWARE.  This license does not grant you any right to any update.
// 
// TITLE.  Title, ownership rights, and intellectual property rights in and to
// the Software shall remain in Supelec and/or its suppliers. The Software is
// protected by international copyright treaties. Title, ownership rights, and
// intellectual property rights in and to the content accessed through the
// Software is the property of the applicable content owner and may be protec-
// ted by applicable copyright or other law. This License gives you no rights
// to such content.
// 
// DISCLAIMER OF WARRANTY.  Since the Software is provided free of charge, the
// Software is provided on an "AS IS" basis, without warranty of any kind,
// including without limitation the warranties of merchantability, fitness for
// a particular purpose and non-infringement. The entire risk as to the quality
// and performance of the Software is borne by you. Should the Software prove
// defective, you and not Supelec assume the entire cost of any service and
// repair. This disclaimer of warranty constitutes an essential part of the
// agreement. SOME STATES/COUNTRIES DO NOT ALLOW EXCLUSIONS OF AN IMPLIED WAR-
// RANTY, SO THIS DISCLAIMER  MAY NOT APPLY TO YOU AND YOU MAY HAVE OTHER LEGAL
// RIGHTS THAT VARY FROM STATE/COUNTRY TO STATE/COUNTRY OR BY JURISDICTION.
// 
// LIMITATION OF LIABILITY.  UNDER NO CIRCUMSTANCES AND UNDER NO LEGAL THEORY,
// TORT, CONTRACT, OR OTHERWISE, SHALL SUPELEC OR ITS SUPPLIERS OR RESELLERS
// BE LIABLE TO YOU OR ANY OTHER PERSON FOR ANY INDIRECT, SPECIAL, INCIDENTAL,
// OR CONSEQUENTIAL DAMAGES OF ANY CHARACTER INCLUDING, WITHOUT LIMITATION,
// DAMAGES FOR LOSS OF GOODWILL, WORK STOPPAGE, COMPUTER FAILURE OR MALFUNC-
// TION, OR ANY AND ALL OTHER COMMERCIAL DAMAGES OR LOSSES. IN NO EVENT WILL
// SUPELEC BE LIABLE FOR ANY DAMAGES IN EXCESS OF SUPELEC'S LIST PRICE FOR A
// LICENSE TO THE SOFTWARE, EVEN IF SUPELEC SHALL HAVE BEEN INFORMED OF THE 
// POSSIBILITY OF SUCH DAMAGES, OR FOR ANY CLAIM BY ANY OTHER PARTY. THIS
// LIMITATION OF LIABILITY SHALL NOT APPLY TO LIABILITY FOR DEATH OR PERSONAL 
// INJURY TO THE EXTENT APPLICABLE LAW PROHIBITS SUCH LIMITATION. FURTHERMORE,
// SOME STATES/COUNTRIES DO NOT ALLOW THE EXCLUSION OR LIMITATION OF INCIDENTAL
// OR CONSEQUENTIAL DAMAGES, SO THIS LIMITATION AND EXCLUSION MAY NOT APPLY TO
// YOU.
// 
// TERMINATION.  This license will terminate automatically if you fail to comply
// with the limitations described above. On termination, you must destroy all
// copies of the Software.
// 
// MISCELLANEOUS.  This Agreement represents the complete agreement concerning
// this license between the parties and supersedes all prior agreements and
// representations between them. It may be amended only by a writing executed
// by both parties. If any provision of this Agreement is held to be unenfor-
// ceable for any reason, such provision shall be reformed only to the extent
// necessary to make it enforceable. This Agreement shall be governed by and
// construed under France law as such law applies to agreements between France
// residents entered into and to be performed within France. The application
// the United Nations Convention of Contracts for the International Sale of
// Goods is expressly excluded.
// 
// Contractor/manufacturer is Ecole Superieure d'Electricite, Plateau de 
// Moulon, 91192 Gif-sur-Yvette Cedex, France.



Bugs

No guarantee is given that this version of dcc is free of bugs, although every
efforts are made to chase and eliminate them.

Bug reports (at e-mail dccsupport@supelec.fr) are requested; they should
include a description of the problem and a short source file causing it, along
with the version/release number of dcc (see below, 'dcc options' paragraph) and
the machine/system used.


Files

There are four sets of files:

- program files:
   dccFiles.mngt
   configdcc.h
   dc.h
   dcrecdir.h
   dctxttok.h
   dcmsg.txt
   dcdecl.c
   dcdir.c
   dcext.c
   dcfmt.c
   dcinst.c
   dcrec.c

- installation files:
   makefile
   createlocalexec
   installfile
   descrip.mms

- execution files:
   adjustFiles.dcc
   *.adj   (adjustment files)
   starter.dccvms
   starter.dccgccalpha
   starter.dccgccmips
   dynarray.h

- test file:
   tstdcc


Configuration, compilation and installation of dcc

The configuration phase means possible adaptations of files configdcc.h,
dccFiles.mngt, and dcmsg.txt.

File 'configdcc.h' serves to configurate dcc (buffer sizes and so on); most
settings should be valid on any machine (except perhaps small memory machines);
comments are supposed to be meaningful enough to make clear the use of each
defined symbol.
EBCDIC character coding could be supported by changing the 'charInfo' array
(file dcrec.c).
Input/output is done entirely via fopen/fread/fputs/feof/fclose/setvbuf/fflush.
The only other system functions used are: malloc/realloc/free, setjmp/longjmp,
exit/abort and system (to pass control to the local compiler).

File 'dccFiles.mngt' is to be adapted to local conditions; it indicates the
directory where the adjustement files list and the starter file are to be found,
and the system header files directory.

File 'dcmsg.txt' contains the text of all messages (including errors/warnings);
since these messages are C string literals, they can be changed at will.
The character sequence '@x', where x is a digit in the range '1'-'9', is not
outputted as such, but replaced by a text generated by dcc.

On an UNIX system, once these files set, compilation is done by typing 'make'.
The 'make install' command installs dcc into the system (first edit file
'installfile' to define where you want it to be; unmodified, this file installs
dcc in /usr/local/bin/, and the 'execution' files in /usr/local/lib/
DccExecFiles/).

On a VMS system, mms can be used (file descrip.mms).

On other systems, you are on your own...

Note: each dcc source file begins with an /* <fileName> */ comment, and ends
      with an /* End <fileName> */ comment, to make it easy to check that it
      has not been truncated by error.


'Execution' files

There are several files needed by dcc to execute correctly:
- a starter file ('starter.dcc'),
- a number of adjustment files ('xxx.adj'),
- an adjustment files list file ('adjustFiles.dcc'), giving the name of the
  adjustment file corresponding to each system header file needing adaptation
  to fit dcc requirements. By convention, for a system header file named
  'xxx.h', the corresponding adjustment file is named 'xxx.adj'.


Starter file

Its purpose is to define the symbols that are predefined by the local compiler.
It also gives the name of the compiler (via a string literal, that must be the
value of the '__dcc' symbol), and can override local 'exotic' features (such as
the "globalvalue" specifier of the VMS C compiler).
Starter files for the VMS C compiler, the ULTRIX gcc compiler and the OSF1 gcc
compiler are included.


Adjustement files

Their purpose is to amend system header files, so that their declarations are
acceptable to dcc. Conceptually, an adjustment file is appended to the end of
the corresponding header file .

An adjustment file should not declare/define anything not declared/defined by
the corresponding header file (except if something is missing in it, such as
the prototype for the "sbrk" function in stdlib.h), but they can redefine at
will function prototypes, external objects, typedefs (even already used ones)
and macros.

Any preprocessor feature can be used in them.

Adjustment files for ctype.h, setjmp.h, stddef.h, stdio.h, stdlib.h, string.h,
time.h and unistd.h are included.


Test File

This command file just checks dcc on its own source files; this check should not
generate any error or warning.
There are many more non-regression check files, but they are not included.


Implemented d-pragmas (as of now)

In the following, a 'header' file is a file whose name contains a '.' followed
somewhere after by a 'h', and included via the '#include' directive; a 'system
header' file is a header file whose '#include' directive use the '<'...'>' form;
a 'body' file is a file whose name is anything but a header file name.

/*~BackBranch*/	avoids warning on backward branchs:
			goto alrdDefLabel /*~BackBranch*/;

/*~DccCompliant*/ in a system header file, indicates that the (remaining portion
		of the) file conforms to dcc requirements, and that used
		'typedefs' will create parallel types for strict synonyms,

/*~DefinedBy <bodyFileName> */ indicates in which file the (following)
		declared objects/functions are defined; can appear anywhere in
		a header file; scope: until next /*~DefinedBy*/; an '#include'
		of (another) header file creates a hole in that scope,

/*~DollarSign*/	at beginning of module; autorizes '$' in identifiers,

/*~DynInit*/	avoids warning on dynamic initialization (by constants) of
		composite objects:
			[auto] struct _s toto = /*~DynInit*/ {...};

/*~IndexType <type> */ inside an array declaration, specifies bound type
		(default type: any arithmetic type) : 
			tab[/*~IndexType Tcouleur */ 5];

/*~LocalAdr*/	avoids warning on returning the address of an 'auto' object, or
		assigning it to a global/external pointer:
			gblPtr = &localObject  /*~ LocalAdr */;

/*~Masking*/	avoids warning if a macro name is the same than an already
		existing identifier:
			#define /*~Masking*/ macroName macroBody

/*~NoBreak*/	avoids warning if falling through the end of a 'case' statement:
			case C1 : i = 1;  /*~NoBreak*/
			case C2 : i++;  break;

/*~NoDefault*/	avoids warning if no 'default' at end of 'switch' (will become
		needless if the type of the driving expression of the switch is
		an enum of which all constants have been used as case values):
			case Cn : i = ... ;
			/*~NoDefault*/

/*~NeverReturns*/ specifies that a void function never returns control:
			static void errExit (...) /*~NeverReturns*/;

/*~NotUsed*/	indicates that an enum constant or a formal parameter (function
		or macro) is not used:
			enum {ce1, ce2 /*~NotUsed*/, ce3 ...}
			static void shift (Tstring x, TtypeElt y /*~NotUsed*/);
			#define Sink(x /*~ NotUsed */)

/*~NoWarn*/	to be used when fed up with warnings; usable anywhere; some
		warning strains are nevertheless resistant to that drug,

/*~OddCast*/	to make dcc swallow a cast it frowns upon:
			ptrInt = (int * /*~OddCast*/) ptrStruct;

/*~PortableQM*/ to make dcc swallow a cast it has good reasons to believe not
		portable:
			ptrFloat = (float * /*~PortableQM*/)ptrDbl;

/*~PrivateTo "<bodyFileName>" [, "<bodyFileName>"]* */ indicates that struct/
		union members' or enum constants' declared thereafter are only
		visible from the indicated file(s), or from macros defined in
		the current header file (or called by such macros); can appear
		anywhere in a header file; scope: until next /*~PrivateTo*/ or
		/*~Public*/; an '#include' of (another) header file creates a
		hole in that scope,

/*~PseudoVoid*/	specifies that a non void-returning function can be used as a
		statement:
			char *strcpy(char *x, const char *y) /*~PseudoVoid*/;

/*~Public*/	indicates end of last /*~PrivateTo*/ scope,

/*~ResultType*/	indicates that the type of the result of a function call is the
		type of the current actual parameter corresponding to the
		indicated formal parameter:
			void *realloc(void *old /*~ResultType*/, size_t size);

/*~VoidToOther*/ autorizes automatic conversion from 'void *' type to any other
		pointer type:
			ptrObj = /*~VoidToOther*/ malloc(sizeof(obj));

/*~Warn*/	to be used when the lack of warning becomes unbeareable
		(antidote for /*~NoWarn*/); usable anywhere,

/*~zif <boolExp> <stringLiteral> */ causes emission on stderr of <stringLiteral>
		if <boolExp> true (at dcc checking time); can be used anywhere
		(for example inside macros):
			/*~ zif sizeof(natTyp)/sizeof(natTyp[0]) != __extent(
				     TtypName)+1 "Array 'natTyp': bad length" */

Note: for dcc, a d-pragma is made up of tokens, perfectly macro-substitutable.
      For instance, the /*~LocalAdr*/ d-pragma consists of the three following
      tokens:

			/*~         (pseudo-token)
			LocalAdr    (identifier)
			*/          (normal token)

An empty d-pragma name is legal; the d-pragma is then ignored.


dcc options

They can be obtained by executing a dcc command with no argument; the version/
release number is also given.


Badly implemented features (as of now)

- floating constants are recognized lexically, but ill converted,
- 'sizeof' does not take into account alignment holes,
- d-pragmas not all heeded at macro expansion time,
- commas in macro body not always correctly interpreted.

Unimplemented features (as of now)

- check that enum constants have differing values (and /*~SameValue*/ d-pragma),
- check that all enum constants have been used in a switch statement
  (/*~NoDefault*/ d-pragma still needed in that case),
- /*~OwnConstants*/ d-pragma (to impose a parallel type to accept only constants
  of its own type),
- check for lack of 'volatile' qualifier in the reach of a setjmp()/longjmp()
  pair,
- check for non-ambiguity of external identifiers,
- check for ill-parenthetized macro bodies,
- check for side-effects via macro parameters,
- size of objects not given ('+zsy' option).
- check that local variables are initialized before use,
- computation of floating-point constant expressions,
- portability not checked in all cases.


Known bug(s)

Queer things happen sometimes when concatenation (##) is used in macro
parameters.


'16 bits int' machines

dcc should work on them, but portage has not been attempted yet.


/* End DCC.README */
