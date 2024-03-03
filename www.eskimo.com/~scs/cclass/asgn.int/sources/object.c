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

/* Find a named object in the actor's vicinity.		*/
/* Returns a pointer to the object structure if found;	*/
/* returns NULL if not found.				*/

struct object *
findobject(struct actor *actp, char *name)
{
struct object *lp;

/* first look in actor's possessions: */

for(lp = actp->contents; lp != NULL; lp = lp->lnext)
	{
	if(strcmp(lp->name, name) == 0)
		return lp;
	}

/* now look in surrounding room: */

if(actp->location != NULL)
	{
	for(lp = actp->location->contents; lp != NULL; lp = lp->lnext)
		{
		if(strcmp(lp->name, name) == 0)
			return lp;
		}
	}

/* didn't find it */

return NULL;
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

/* print a list of objects, one per line		*/
/* (might be room's contents, or actor's possessions)	*/

void
listobjects(struct object *list)
{
struct object *lp;

for(lp = list; lp != NULL; lp = lp->lnext)
	{
	printf("%s\n", lp->name);
	}
}
