/*
	localeconv() -- numeric formatting convention inquiry
	setlocale() -- locale control function

	This source code has been placed into the PUBLIC DOMAIN by its author.

	last edit:	1999/08/20	gwyn@arl.mil

	Implements subclauses 7.11.1.1 & 7.11.2.1 of ISO/IEC 9899:1999 (E).

	This is a minimal implementation for environments where
	internationalization is not considered important.

	XXX -- UNTESTED -- XXX
*/

#include	<limits.h>		/* for CHAR_MAX */

#include	<locale.h>

static char	empty[] = "";

static struct lconv	c_lconv =	/* lconv for "C" locale */
	{
	/* WARNING: The following order must match the header! */
	".",				/* decimal_point */
	empty,				/* thousands_sep */
	empty,				/* grouping */
	empty,				/* int_curr_symbol */
	empty,				/* currency_symbol */
	empty,				/* mon_decimal_point */
	empty,				/* mon_thousands_sep */
	empty,				/* mon_grouping */
	empty,				/* positive_sign */
	empty,				/* negative_sign */
	CHAR_MAX,			/* int_frac_digits */
	CHAR_MAX,			/* frac_digits */
	CHAR_MAX,			/* p_cs_precedes */
	CHAR_MAX,			/* p_sep_by_space */
	CHAR_MAX,			/* n_cs_precedes */
	CHAR_MAX,			/* n_sep_by_space */
	CHAR_MAX,			/* p_sign_posn */
	CHAR_MAX,			/* n_sign_posn */
	CHAR_MAX,			/* int_p_cs_precedes */
	CHAR_MAX,			/* int_p_sep_by_space */
	CHAR_MAX,			/* int_n_cs_precedes */
	CHAR_MAX,			/* int_n_sep_by_space */
	CHAR_MAX,			/* int_p_sign_posn */
	CHAR_MAX,			/* int_n_sign_posn */
	};

struct lconv *
localeconv()
	{
	return &c_lconv;
	}

char *
setlocale(category, locale)
	int		category;
	const char	*locale;
	{
	switch ( category )
		{
	case LC_ALL:
	case LC_COLLATE:
	case LC_CTYPE:
	case LC_MONETARY:
	case LC_NUMERIC:
	case LC_TIME:
		return empty;		/* native "" == "C" == "POSIX" */
		/* The string doesn't have to be the same as the argument. */

	default:
		return NULL;		/* unsupported category */
		}
	}
