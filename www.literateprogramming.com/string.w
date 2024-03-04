% bibiliographic macros adapted from Wynter Snow's {\sl TeX for the Beginner}
\newdimen\biblioindent\biblioindent=.25in
\def\bibitem#1{\par\medskip\noindent
	\hangindent=\biblioindent
	\hbox to \biblioindent{\cite{#1}\hfil}%
	\ignorespaces
}
\def\bibstart{\bgroup\frenchspacing}
\def\bibend{\egroup}
\def\cite#1{[\csname#1\endcsname]}
\def\xcite#1#2{[\csname#1\endcsname, #2]}
%

\def\cweb/{\.{CWEB}}
\def\cee/{C}
\def\cpp/{\cee/{\tt++}}
\def\strous{1}

%\skip\footins=12pt plus 1fil
\def\title{Listing~5}

\def\quotation#1{\par\bgroup\narrower\medskip\noindent\ignorespaces#1\par\medskip\egroup}
\def\cnotice{Copyright \copyright~1994 by Lee Wittenberg.
\par\noindent
Portions copyright \copyright~1991 by AT\AM T Bell Telephone
Laboratories, Inc.}
\ifx\cujstuff\undefined
\let\covernote=\cnotice
\else
\medskip\hrule
\bgroup
\medskip\noindent
\cnotice
\par\egroup
\fi
@*A \cpp/ String Class.
To demonstrate the use of \cweb/ for \cpp/ programming, we
adapt the |string| class described by
Stroustrup~\xcite{strous}{pages~248--251}.  Explanations in {\sl slanted
type\/} (including inline
comments, when possible) are direct quotes from the original.  We make a
few minor changes along the way, but on the whole, we
stick to Stroustrup's design.

@ We put the interface part of our class in the header file
\.{xstring.h}.  We call our class ``|Xstring|'' rather than
``|string|'' to avoid confusion with the
original and other (more useful) string classes.  We restrict
ourselves to a lowercase file name to maintain portability
among operating systems with case-insensitive file names.
@s string int
@s Xstring int	@q -- a hint for the typesetter -- @>
@(xstring.h@>=
#ifndef XSTRING_H
#define XSTRING_H	// prevent multiple inclusions
@#
class Xstring {
	@<Private |Xstring| members@>@;
public:@/
	@<Public |Xstring| members@>@;
};
@#
#endif

@ We implement the class members
in a single ``unnamed chunk'' that will be tangled to
\.{xstring.c} (or \.{xstring.cc} or \.{xstring.cpp}, depending
on your compiler's preference).  We include the contents of
|@(xstring.h@>| directly, rather than relying on \&{\#include},
because we can.
@c
@<Header files@>@;
@(xstring.h@>@;
@<|Xstring| members and friends@>@;

@*1Representing an {\bf Xstring}.
The internal representation of an |Xstring| is simple.  {\sl It
counts the references to a string to minimize copying and uses
standard \cpp/ character strings as constants}.
@<Private...@>=
struct srep {
	char *s;	// {\sl pointer to data}
	int   n;	// {\sl reference count}
	srep() @+ {@+ n = 1; @+}
};
srep *p;

@*1Construction and Destruction.
{\sl The constructors and the destructor are trivial}.  We use
the null string as a default constructor argument rather than a
null pointer to protect against possible \.{string.h} function
anomalies.
@<Public...@>=
Xstring(const char *s = "");	// |Xstring x = "abc"|
Xstring(const Xstring &);	// |Xstring x = Xstring|~$\ldots$
~Xstring();

@ An |Xstring| constructed from a standard string needs space to hold
the characters:
@<|Xstring|...@>=
Xstring::Xstring(const char* s)
{
	p = new srep;
	@<Allocate space for the string and put a copy of |s| there@>;
}

@ There is always the possibility that a client will try
something like ``|Xstring x = NULL|.''  We substitute the null
string whenever we are given a null pointer.
@<Allocate...@>=
if (s==NULL) s="";
p->s = new char[ strlen(s)+1 ];
strcpy(p->s, s);

@ @<Header...@>=
#include <string.h>	// Standard~\cee/ header for |strcpy|

@ On the other hand, to build an |Xstring| from another
|Xstring|, we only have to increment the reference count:
@<|Xstring|...@>=
Xstring::Xstring(const Xstring& x)
{
	x.p->n++;
	p = x.p;
}

@ The destructor also has to worry about the reference count:
@<|Xstring|...@>=
Xstring::~Xstring()
{
	@<Decrement reference count, and remove |p| if necessary@>;
}

@ @<Decrement...@>=
if (--p->n == 0) {
	delete[] p->s;
	delete p;
}

@*1Assignment.
{\sl As usual, the assignment operators are similar to the
constructors.  They must handle cleanup of their first
(left-hand) operand:}
@<Public...@>=
Xstring&  @!@[operator=@](const char *);
Xstring& @!@[operator=@](const Xstring &);
@ @<|Xstring|...@>=
Xstring&
Xstring::@!@[operator=@](const char* s)
{
	if (p->n > 1) {		// {\sl disconnect self}
		p->n--;
		p= new srep;
	} @+ else @/			// {\sl free old string}
		delete[] p->s;
	@<Allocate...@>;
	return *this;
}

Xstring&
Xstring::@!@[operator=@](const Xstring& x)
{
	x.p->n++;		// {\sl protect against ``\\{st}${}\K{}$\\{st}''}
	@<Decrement...@>;
	p = x.p;
	return *this;
}

@*1Miscellaneous Operations.
We provide a conversion operator to translate |Xstring|'s into
ordinary strings.  This allows us to pass them to standard
functions like |strlen| (and gives us an output operator for
free).  We convert to |const| strings to prevent strange things
from happening if a client should try to use a standard
function like |strcat|
to modify an |Xstring|.
@<Public...@>=
operator @t @> const char *() @+ {@+ return p->s; @+}

@ {\sl The subscript operator is provided for access to
individual characters.  The index is checked.}  However, we
depart from the original design by returning a dummy element when the index is
out of bounds rather than generating an error message (or an
exception).
@<Public...@>=
char& operator[](int i) @+ {@+ return ((i<0)||(strlen(p->s)<i)
? dummy : p->s[i]); @+ }

@ @<Private...@>=
static char dummy;

@ @<|Xstring|...@>=
char Xstring::dummy;

@*References.
\bibstart

\bibitem{strous}
Bjarne Stroustrup. {\sl The \cpp/~Programming
Language}. Addison-Wesley, second edition, 1991.

\bibend

@*Index.
