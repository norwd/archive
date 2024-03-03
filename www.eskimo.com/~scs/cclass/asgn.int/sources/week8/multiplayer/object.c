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

static struct object *findobj2(struct object *, char *);
static struct object *findcontainer(struct object *, struct actor *, struct room *);
static struct object *findcont2(struct object *, struct object *);

struct object *
newobject(char *newname)
{
struct object *objp;

if(nobjects >= MAXOBJECTS)
	{
	fprintf(stderr, "too many objects\n");
	exit(1);
	}

objp = &objects[nobjects++];

strcpy(objp->name, newname);
objp->lnext = NULL;
objp->attrs = NULL;
objp->contents = NULL;
objp->func = NULL;
objp->script = NULL;

return objp;
}

/* Find a named object in the actor's vicinity.		*/
/* Returns a pointer to the object structure if found;	*/
/* returns NULL if not found.				*/

struct object *
findobject(struct actor *actp, char *name)
{
struct object *lp;

/* first look in actor's possessions: */

lp = findobj2(actp->contents, name);
if(lp != NULL)
	return lp;

/* now look in surrounding room: */

if(actp->location != NULL)
	{
	lp = findobj2(actp->location->contents, name);
	if(lp != NULL)
		return lp;
	}

/* didn't find it */

return NULL;
}

/* find a named object in an object list */
/* (return NULL if not found) */

static struct object *
findobj2(struct object *list, char *name)
{
struct object *lp;

for(lp = list; lp != NULL; lp = lp->lnext)
	{
	if(strcmp(lp->name, name) == 0)
		return lp;
	if(lp->contents != NULL)
		{
		struct object *lp2 = findobj2(lp->contents, name);
		if(lp2 != NULL)
			return lp2;
		}
	}

/* didn't find it */

return NULL;
}

/* find an object's container (in actor's possesion, or room) */
/* (return NULL if not found) */

static struct object *
findcontainer(struct object *objp, struct actor *actp, struct room *roomp)
{
struct object *lp, *lp2;

/* first look in possessions: */

for(lp = actp->contents; lp != NULL; lp = lp->lnext)
	{
	if(lp->contents != NULL)
		{
		lp2 = findcont2(objp, lp);
		if(lp2 != NULL)
			return lp2;
		}
	}

/* now look in room: */

for(lp = roomp->contents; lp != NULL; lp = lp->lnext)
	{
	if(lp->contents != NULL)
		{
		lp2 = findcont2(objp, lp);
		if(lp2 != NULL)
			return lp2;
		}
	}

return NULL;
}

static struct object *
findcont2(struct object *objp, struct object *container)
{
struct object *lp;

for(lp = container->contents; lp != NULL; lp = lp->lnext)
	{
	if(lp == objp)
		return container;
	if(lp->contents != NULL)
		{
		struct object *lp2 = findcont2(objp, lp);
		if(lp2 != NULL)
			return lp2;
		}
	}

return NULL;
}

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

/* Returns TRUE if object objp exists in list; FALSE otherwise. */
/* Used as a "predicate"; for example				*/
/*	if(!contains(actor->contents, obj))			*/
/*		printf("You don't have the %s.", obj->name);	*/

int
contains(struct object *list, struct object *objp)
{
struct object *lp;

for(lp = list; lp != NULL; lp = lp->lnext)
	{
	if(lp == objp)
		return TRUE;
	}

return FALSE;
}

/* Transfer object from actor's room to actor.				*/
/* The object shound exist somewhere in the room's contents list.	*/
/* We find it there, remove it from that list, and splice it		*/ 
/* into the actor's possessions.					*/

takeobject(struct actor *actp, struct object *objp)
{
struct room *roomp = actp->location;
struct object *lp;
struct object *prevlp = NULL;
struct object *containerp;

if(roomp == NULL)
	return FALSE;

/* search through room's contents */

for(lp = roomp->contents; lp != NULL; lp = lp->lnext)
	{
	if(lp == objp)				/* found it */
		{
		/* splice out of room's list */

		if(lp == roomp->contents)	/* head of list */
			roomp->contents = lp->lnext;
		else	prevlp->lnext = lp->lnext;

		/* splice into actor's list */

		lp->lnext = actp->contents;
		actp->contents = lp;

		return TRUE;
		}

	prevlp = lp;
	}


/* perhaps it's in a container */

containerp = findcontainer(objp, actp, roomp);

if(containerp != NULL)
	{
	/* this test should probably be up in commands.c) */

	if(hasattr(containerp, "closable") && !Isopen(containerp))
		{
		output(actp, "The %s is closed.\n", containerp->name);
		return FALSE;
		}

	/* re-find in container's list, for splicing */

	prevlp = NULL;

	for(lp = containerp->contents; lp != NULL; lp = lp->lnext)
		{
		if(lp == objp)				/* found it */
			{
			/* splice out of room's list */

			if(lp == containerp->contents)	/* head of list */
				containerp->contents = lp->lnext;
			else	prevlp->lnext = lp->lnext;

			/* splice into actor's list */

			lp->lnext = actp->contents;
			actp->contents = lp;

			return TRUE;
			}

		prevlp = lp;
		}
	}

/* didn't find it (error) */

return FALSE;
}

/* transfer object from actor to actor's room */

dropobject(struct actor *actp, struct object *objp)
{
struct room *roomp = actp->location;
struct object *lp;
struct object *prevlp = NULL;

if(roomp == NULL)
	return FALSE;

for(lp = actp->contents; lp != NULL; lp = lp->lnext)
	{
	if(lp == objp)				/* found it */
		{
		/* splice out of actor's list */

		if(lp == actp->contents)	/* head of list */
			actp->contents = lp->lnext;
		else	prevlp->lnext = lp->lnext;

		/* splice into room's list */

		lp->lnext = roomp->contents;
		roomp->contents = lp;

		return TRUE;
		}

	prevlp = lp;
	}

/* didn't find it (error) */

return FALSE;
}

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

/* print a list of objects, one per line		*/
/* (might be room's contents, or actor's possessions)	*/

void
listobjects(struct object *list)
{
struct object *lp;

for(lp = list; lp != NULL; lp = lp->lnext)
	{
	output(actp, "%s\n", lp->name);
	if(lp->contents != NULL)
		{
		output(actp, "The %s contains:\n", lp->name);
		listobjects(lp->contents);
		}
	}
}
