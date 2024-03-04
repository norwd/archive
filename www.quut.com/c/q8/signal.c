/*
	signal -- specify signal handling
	raise -- send signal

	This source code has been placed into the PUBLIC DOMAIN by its author.

	last edit:	1999/08/20	gwyn@arl.mil

	Implements subclauses 7.14.1 & 7.14.2 of ISO/IEC 9899:1999 (E).

	These are minimally functional versions, solely for systems that don't
	already provide signal() (such as the TMS320C6xxx DSP's compiler).

	XXX -- UNTESTED -- XXX
*/

#include	<errno.h>
#include	<stdlib.h>		/* for abort() */

#include	<Q8defs.h>		/* for __Q8_PARAMS */
#include	<signal.h>
#include	<stdbool.h>

#define	NSIG	(SIGTERM+1)		/* max. supported signal number + 1 */

static void	(*handler[NSIG])__Q8_PARAMS((int));	/* current handlers */

static bool	inited = false;		/* for initializing above */

/* dummy functions for unique address */
void	__sig_err(sig) int sig; { }
void	__sig_ign(sig) int sig; { }

/*
	7.14.1 -- specify signal handling
*/

void	(*
signal(sig, func)
	)__Q8_PARAMS((int))		/* returns previous handler */
	register int	sig;
	void		(*func)__Q8_PARAMS((int));
	{
	register void	(*retval)__Q8_PARAMS((int));	/* previous handler */

	if ( sig <= 0 || sig >= NSIG )	/* safety check */
		{
		errno = EDOM;
		return SIG_ERR;
		}

	/* C language provides no good way to initialize handler[] */
	if ( !inited )			/* once only */
		{
		register int	i;

		for ( i = 0; i < NSIG; ++i )
			handler[i] = SIG_DFL;	/* initialize */

		inited = true;
		}

	retval = handler[sig - 1];	/* previous state */
	handler[sig - 1] = func;	/* new state */

	return retval;			/* previous handler */
	}

/*
	7.14.2 -- send signal
*/

int
raise(sig)
	int		sig;
	{
	register void	(*func)__Q8_PARAMS((int));	/* handler value */

	if ( sig <= 0 || sig >= NSIG )	/* safety check */
		{
		errno = EDOM;
		return 1;		/* indicate failure */
		}

	func = handler[sig - 1];

	if ( func == SIG_IGN )
		return 0;		/* indicate success */

	if ( func == SIG_DFL )
		{
		abort();		/* (an arbitrary decision) */
		return 1;		/* just in case, indicate failure */
		}

	handler[sig - 1] = SIG_DFL;	/* classic UNIX behavior */
	(*func)(sig);

	return 0;			/* indicate success */
	}
