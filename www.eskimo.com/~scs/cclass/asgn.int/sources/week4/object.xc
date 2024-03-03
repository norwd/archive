/* transfer object from actor to container */

putobject(struct actor *actp, struct object *objp, struct object *container)
{
struct object *lp;
struct object *prevlp = NULL;

for(lp = actp->contents; lp != NULL; lp = lp->lnext)
	{
	if(lp == objp)				/* found it */
		{
		/* splice out of actor's list */

		if(lp == actp->contents)	/* head of list */
			actp->contents = lp->lnext;
		else	prevlp->lnext = lp->lnext;

		/* splice into container's list */

		lp->lnext = container->contents;
		container->contents = lp;

		return TRUE;
		}

	prevlp = lp;
	}

/* didn't find it (error) */

return FALSE;
}
