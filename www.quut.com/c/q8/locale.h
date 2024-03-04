/*
	<locale.h> -- definitions for internationalization functions

	This source code has been placed into the PUBLIC DOMAIN by its author.

	last edit:	1999/08/20	gwyn@arl.mil

	Implements subclause 7.11 of ISO/IEC 9899:1999 (E).

	The standard allows additional macro definitions starting with
	"LC_" and an uppercase letter.
 */

/* This header doesn't need an idempotency lock; there are no typedefs here. */

#include	<Q8defs.h>		/* defines __Q8_NULL and __Q8_PARAMS */

#ifdef	__cplusplus
extern	"C"	{
#endif

struct lconv				/* members are in usual UNIX order */
	{
	/* The following are controlled by LC_NUMERIC: */
	char	*decimal_point;
	char	*thousands_sep;
	char	*grouping;
	/* The following are controlled by LC_MONETARY: */
	char	*int_curr_symbol;
	char	*currency_symbol;
	char	*mon_decimal_point;
	char	*mon_thousands_sep;
	char	*mon_grouping;
	char	*positive_sign;
	char	*negative_sign;
	char	int_frac_digits;
	char	frac_digits;
	char	p_cs_precedes;
	char	p_sep_by_space;
	char	n_cs_precedes;
	char	n_sep_by_space;
	char	p_sign_posn;
	char	n_sign_posn;
	char	int_p_cs_precedes;
	char	int_p_sep_by_space;
	char	int_n_cs_precedes;
	char	int_n_sep_by_space;
	char	int_p_sign_posn;
	char	int_n_sign_posn;
	};

/* The following have the usual UNIX values: */
#define	LC_CTYPE	(0)
#define	LC_NUMERIC	(1)
#define	LC_TIME		(2)
#define	LC_COLLATE	(3)
#define	LC_MONETARY	(4)
#define	LC_ALL		(6)
/* other categories may be added here: */
#define	LC_MESSAGES	(5)

#ifndef	NULL
#define	NULL	__Q8_NULL
#endif

extern char		*setlocale __Q8_PARAMS((int __category,
				const char *__locale));
extern struct lconv	*localeconv __Q8_PARAMS((void));

#ifdef	__cplusplus
		}
#endif
