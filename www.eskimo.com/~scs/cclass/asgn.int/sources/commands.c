/*
 *  Text-based dungeon/adventure game, for the
 *  UW Experimental College course in Intermediate C Programming
 *
 *  Copyright 1996-1999 Steve Summit
 *  scs@eskimo.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "defs.h"

static dircommand(struct actor *, int);

/* Interpret a command verb and (optional) object */

/* This is the heart of the game, implementing each of the "commands"	*/
/* which the user may type.  Commands are very simple, consisting of	*/
/* just a verb and an optional object.					*/
/* The function simply compares the requested verb to the ones		*/
/* it knows about, and if a match is found, it then calls whatever	*/
/* functions are appropriate for implementing the requested action.	*/
/* In general, there are several steps to perform for each command:	*/
/* verify that an object (if required) has been specified,		*/
/* verify that the object is present and appropriate for the action	*/
/* requested, attempt to perform the action, and finally print		*/
/* a message indicating that the action has been performed		*/
/* or explaining why it couldn't be.					*/
/*									*/
/* In most cases, we start with the name of an object (i.e. as a	*/
/* string), but need the struct object which describes the object;	*/
/* we call the findobject() function (from object.c) whenever we	*/
/* need to look up an object by name.					*/
/*									*/
/* In general, the code here is still at a pretty high level;		*/
/* the work of moving between rooms is centralized in the		*/
/* dircommand() function, and the work of taking and dropping		*/
/* objects is performed by takeobject() and dropobject() in object.c.	*/

docommand(struct actor *player, char *verb, char *object)
{
struct object *objp;

if(strcmp(verb, "n") == 0 || strcmp(verb, "north") == 0)
	dircommand(player, NORTH);
else if(strcmp(verb, "s") == 0 || strcmp(verb, "south") == 0)
	dircommand(player, SOUTH);
else if(strcmp(verb, "e") == 0 || strcmp(verb, "east") == 0)
	dircommand(player, EAST);
else if(strcmp(verb, "w") == 0 || strcmp(verb, "west") == 0)
	dircommand(player, WEST);
else if(strcmp(verb, "take") == 0)
	{
	if(object == NULL)
		{
		printf("You must tell me what to take.\n");
		return FALSE;
		}
	objp = findobject(player, object);
	if(objp == NULL)
		{
		printf("I see no %s here.\n", object);
		return FALSE;
		}
	if(contains(player->contents, objp))
		{
		printf("You already have the %s.\n", object);
		return FALSE;
		}
	if(!takeobject(player, objp))
		{
		/* shouldn't happen */
		printf("You can't pick up the %s.\n", object);
		return FALSE;
		}
	printf("Taken.\n");
	}
else if(strcmp(verb, "drop") == 0)
	{
	if(object == NULL)
		{
		printf("You must tell me what to drop.\n");
		return FALSE;
		}
	objp = findobject(player, object);
	if(objp == NULL || !contains(player->contents, objp))
		{
		printf("You have no %s.\n", object);
		return FALSE;
		}
	if(!dropobject(player, objp))
		{
		/* shouldn't happen */
		printf("You can't drop the %s!\n", object);
		return FALSE;
		}
	printf("Dropped.\n");
	}
else if(strcmp(verb, "look") == 0)
	{
	listroom(player);
	}
else if(strcmp(verb, "i") == 0 || strcmp(verb, "inventory") == 0)
	{
	if(player->contents == NULL)
		printf("You are empty handed.\n");
	else	{
		printf("You are carrying:\n");
		listobjects(player->contents);
		}
	}
else if(strcmp(verb, "quit") == 0)
	{
	exit(0);
	}
else	{
	printf("I don't know the word \"%s\".\n", verb);
	return FALSE;
	}

return TRUE;
}

/* Common code for the n, e, w, and s commands.			*/
/* This function just picks the correct exit link (within the	*/
/* room structure) to act on; the gotoroom() function		*/
/* (in rooms.c) does the real work.				*/

dircommand(struct actor *player, int dir)
{
struct room *roomp = player->location;

if(roomp == NULL)
	{
	printf("Where are you?\n");
	return FALSE;
	}

/* If the exit does not exist, or if gotoroom() fails,	*/
/* the player can't go that way.			*/

if(roomp->exits[dir] == NULL || !gotoroom(player, roomp->exits[dir]))
	{
	printf("You can't go that way.\n");
	return FALSE;
	}

/* player now in new room */

listroom(player);

return TRUE;
}
