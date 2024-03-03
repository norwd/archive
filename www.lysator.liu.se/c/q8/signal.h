/*
	signal.h -- signal handling

	This source code has been placed into the PUBLIC DOMAIN by its author.

	last edit:	1999/11/05	gwyn@arl.mil

	Implements subclause 7.14 of ISO/IEC 9899:1999 (E).

	This particular implementation requires the matching signal.c.

	This is a minimally functional version, solely for systems that don't
	already provide <signal.h> (such as the TMS320C6xxx DSP's compiler).
*/

#if	!defined(_SIGNAL_H) && !defined(_INC_SIGNAL)	/* usual lock names */
#define	_SIGNAL_H			/* idempotency lock (section 7.1.2) */
#define	_INC_SIGNAL

#include	<Q8defs.h>		/* defines __Q8_PARAMS */

#ifdef	__cplusplus
extern	"C"	{
#endif

/* atomic-access data type: */

typedef int	sig_atomic_t;		/* this type works nearly everywhere */

/* signal states: */

#define	SIG_DFL	((void (*)__Q8_PARAMS((int)))0)	/* default */
#define	SIG_ERR	__sig_err		/* error return from signal() */
#define	SIG_IGN	__sig_ign		/* ignore */

/* dummy functions for unique address */
extern void	__sig_err __Q8_PARAMS((int __sig));
extern void	__sig_ign __Q8_PARAMS((int __sig));

/* signal numbers (these are a subset of the traditional UNIX values): */

#define	SIGINT	(2)			/* interactive attention signal */
#define	SIGILL	(4)			/* invalid function image */
#define	SIGABRT	(6)			/* abnormal termination */
#define	SIGFPE	(8)			/* erroneous arithmetic operation */
#define	SIGSEGV	(11)			/* invalid access to storage */
#define	SIGTERM	(15)			/* termination request */
/* Note: SIGTERM is assumed by my signal.c to have the highest value. */

/*
	7.14.1 -- specify signal handling
*/

extern void	(*signal __Q8_PARAMS((int __sig, void (*__func)(int))))
			__Q8_PARAMS((int));

/*
	7.14.2 -- send signal
*/

extern int	raise __Q8_PARAMS((int __sig));

#ifdef	__cplusplus
		}
#endif

#endif	/* !defined(_SIGNAL_H) && !defined(_INC_SIGNAL) */
