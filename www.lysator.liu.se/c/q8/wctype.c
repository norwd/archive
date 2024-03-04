/*
	wctype -- wide character classification and mapping utilities

	This source code has been placed into the PUBLIC DOMAIN by its author.

	last edit:	1999/11/05	gwyn@arl.mil

	Implements subclause 7.25 of ISO/IEC 9899:1999 (E).

	This particular implementation requires the matching <wctype.h>.

	This is a minimal implementation for environments where
	internationalization is not considered important.

	It supports an encoding where all char codes are mapped
	to the *same* code values within a wchar_t or wint_t,
	so long as no other wchar_t codes are used by the program.

	XXX -- UNTESTED -- XXX
*/

#include	<ctype.h>
#include	<errno.h>
#include	<string.h>

#include	<wctype.h>		/* defines __Q8_CONST and __Q8_PARAMS */

/*
	7.25.2	Wide character classification utilities
*/

int
iswalnum(wc)
	wint_t	wc;
	{
	return isalnum((int)(unsigned char)wc);
	}

int
iswalpha(wc)
	wint_t	wc;
	{
	return isalpha((int)(unsigned char)wc);
	}

int
iswblank(wc)
	wint_t	wc;
	{
	return isblank((int)(unsigned char)wc);
	}

int
iswcntrl(wc)
	wint_t	wc;
	{
	return iscntrl((int)(unsigned char)wc);
	}

int
iswdigit(wc)
	wint_t	wc;
	{
	return isdigit((int)(unsigned char)wc);
	}

int
iswgraph(wc)
	wint_t	wc;
	{
	return isgraph((int)(unsigned char)wc);
	}

int
iswlower(wc)
	wint_t	wc;
	{
	return islower((int)(unsigned char)wc);
	}

int
iswprint(wc)
	wint_t	wc;
	{
	return isprint((int)(unsigned char)wc);
	}

int
iswpunct(wc)
	wint_t	wc;
	{
	return ispunct((int)(unsigned char)wc);
	}

int
iswspace(wc)
	wint_t	wc;
	{
	return isspace((int)(unsigned char)wc);
	}

int
iswupper(wc)
	wint_t	wc;
	{
	return isupper((int)(unsigned char)wc);
	}

int
iswxdigit(wc)
	wint_t	wc;
	{
	return isxdigit((int)(unsigned char)wc);
	}

/*
	wctype() usually encodes properties as ORed bit combinations;
	for this *minimal implementation* I can take a lazy approach.	
*/

static struct
	{
	__Q8_CONST char	*name;
	int		(*func)__Q8_PARAMS((int));
	}	cmap[] =
	{
	"alnum",	iswalnum,
	"alpha",	iswalpha,
	"blank",	iswblank,
	"cntrl",	iswcntrl,
	"digit",	iswdigit,
	"graph",	iswgraph,
	"lower",	iswlower,
	"print",	iswprint,
	"punct",	iswpunct,
	"space",	iswspace,
	"upper",	iswupper,
	"xdigit",	iswxdigit
	};
#define	NCMAP	(sizeof cmap / sizeof cmap[0])

int
iswctype(wc, desc)
	wint_t		wc;
	wctype_t	desc;
	{
	register int	i;

	if ( desc <= 0 || desc > NCMAP )	/* undefined behavior */
		{
		errno = EDOM;	
		return 0;		/* a form of not having the property */
		}

	return cmap[desc-1].func(wc);
	}

wctype_t				/* returns map index + 1 */
wctype(property)
	__Q8_CONST char	*property;
	{
	register int	i;

	for ( i = 0; i < NCMAP; ++i )
		if ( strcmp(property, cmap[i].name) == 0 )
			return i+1;

	return 0;			/* indicates "not valid" */
	}

/*
	7.25.3	Wide character case mapping utilities
*/

wint_t
towlower(wc)
	wint_t	wc;
	{
	return tolower((int)(unsigned char)wc);
	}

wint_t
towupper(wc)
	wint_t	wc;
	{
	return toupper((int)(unsigned char)wc);
	}

/*
	For this *minimal implementation* I can take a lazy approach.	
*/

static struct
	{
	__Q8_CONST char	*name;
	int		(*func)__Q8_PARAMS((int));
	}	tmap[] =
	{
	"lower",	towlower,
	"upper",	towupper
	};
#define	NTMAP	(sizeof tmap / sizeof tmap[0])

wint_t
iswctrans(wc, desc)
	wint_t		wc;
	wctrans_t	desc;
	{
	register int	i;

	if ( desc <= 0 || desc > NTMAP )	/* undefined behavior */
		{
		errno = EDOM;	
		return 0;		/* a form of not having the property */
		}

	return tmap[desc-1].func(wc);
	}

wctrans_t				/* returns map index + 1 */
wctrans(property)
	__Q8_CONST char	*property;
	{
	register int	i;

	for ( i = 0; i < NTMAP; ++i )
		if ( strcmp(property, tmap[i].name) == 0 )
			return i+1;

	return 0;			/* indicates "not valid" */
	}
