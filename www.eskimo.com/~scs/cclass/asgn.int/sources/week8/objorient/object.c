/*
 *  Text-based dungeon/adventure game, for the
 *  UW Experimental College course in Intermediate C Programming
 *
 *  Copyright 1996-1999 Steve Summit
 *  scs@eskimo.com
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game.h"
#include "defs.h"

#define MAXOBJECTS 100

static struct object objects[MAXOBJECTS];
static int nobjects = 0;

static object *findobj2(object *, char *);

object::object(const char *newname)
{
strcpy(name, newname);
lnext = NULL;
attrs = NULL;
contents = NULL;
container = NULL;
objp->func = NULL;
objp->script = NULL;
}

object::~object(void)
{
}

/* not sure where this belongs (essentially a stub constructor...) */

actor::actor() : object("")
{
}

/* Find a named object in the actor's vicinity.		*/
/* Returns a pointer to the object if found;		*/
/* returns NULL if not found.				*/

object *
findobject(actor *actp, char *name)
{
object *lp;

/* first look in actor's possessions: */

lp = findobj2(actp->contents, name);
if(lp != NULL)
	return lp;

/* now look in surrounding room: */

if(actp->container != NULL)
	{
	lp = findobj2(actp->container->contents, name);
	if(lp != NULL)
		return lp;
	}

/* didn't find it */

return NULL;
}

/* find a named object in an object list */
/* (return NULL if not found) */

static object *
findobj2(object *list, char *name)
{
object *lp;

for(lp = list; lp != NULL; lp = lp->lnext)
	{
	if(strcmp(lp->name, name) == 0)
		return lp;
	if(lp->contents != NULL)
		{
		object *lp2 = findobj2(lp->contents, name);
		if(lp2 != NULL)
			return lp2;
		}
	}

/* didn't find it */

return NULL;
}

/* see if the object has the attribute */

int
hasattr(object *objp, char *attr)
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
setattr(object *objp, char *attr)
{
struct list *lp;

if(hasattr(objp, attr))
	return;

lp = (struct list *)chkmalloc(sizeof(struct list));

lp->item = chkstrdup(attr);
lp->next = objp->attrs;
objp->attrs = lp;
}

/* clear an attribute of an object */

void
unsetattr(object *objp, char *attr)
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

/* Returns TRUE if object objp exists in list; FALSE otherwise. */
/* Used as a "predicate"; for example				*/
/*	if(!contains(actor->contents, obj))			*/
/*		printf("You don't have the %s.", obj->name);	*/

int
contains(object *list, object *objp)
{
object *lp;

for(lp = list; lp != NULL; lp = lp->lnext)
	{
	if(lp == objp)
		return TRUE;
	}

return FALSE;
}

/* Transfer object from actor's room to actor.				*/
/* The object shound exist somewhere in the room's contents list.	*/

takeobject(actor *actp, object *objp)
{
return transferobject(objp, actp);
}

/* transfer object from actor to actor's room */

dropobject(actor *actp, object *objp)
{
return transferobject(objp, actp->container);
}

/* transfer object from actor to container */

putobject(actor *actp, object *objp, object *container)
{
return transferobject(objp, container);
}

/* transfer object from one general container to another */

transferobject(object *objp, object *newcontainer)
{
object *lp;
object *prevlp = NULL;

if(objp->container != NULL)
	{
	object *oldc = objp->container;
	for(lp = oldc->contents; lp != NULL; lp = lp->lnext)
		{
		if(lp == objp)				/* found it */
			{
			/* splice out of old container's list */
			if(lp == oldc->contents)	/* head of list */
				oldc->contents = lp->lnext;
			else	prevlp->lnext = lp->lnext;
			break;
			}
		prevlp = lp;
		}
	}

/* splice into new container's list */

if(newcontainer != NULL)
	{
	objp->lnext = newcontainer->contents;
	newcontainer->contents = objp;
	}

objp->container = newcontainer;

return TRUE;
}
/* print a list of objects, one per line		*/
/* (might be room's contents, or actor's possessions)	*/

void
listobjects(struct object *list)
{
struct object *lp;

for(lp = list; lp != NULL; lp = lp->lnext)
	{
	printf("%s\n", lp->name);
	if(lp->contents != NULL)
		{
		printf("The %s contains:\n", lp->name);
		listobjects(lp->contents);
		}
	}
}
