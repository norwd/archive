/* see if the object has the attribute */

int
hasattr(struct object *objp, char *attr)
{
struct list *lp;

for(lp = objp->attrs; lp != NULL; lp = lp->next)
	{
	if(strcmp(lp->item, attr) == 0)
		return TRUE;
	}

return FALSE;
}

/* set an attribute of an object (if it's not set already) */

void
setattr(struct object *objp, char *attr)
{
struct list *lp;

if(hasattr(objp, attr))
	return;

lp = chkmalloc(sizeof(struct list));

lp->item = chkstrdup(attr);
lp->next = objp->attrs;
objp->attrs = lp;
}

/* clear an attribute of an object */

void
unsetattr(struct object *objp, char *attr)
{
struct list *lp;
struct list *prevlp;

for(lp = objp->attrs; lp != NULL; lp = lp->next)
	{
	if(strcmp(lp->item, attr) == 0)
		{
		if(lp == objp->attrs)
			objp->attrs = lp->next;
		else	prevlp->next = lp->next;
		free(lp->item);
		free(lp);
		return;
		}
	prevlp = lp;
	}
}
