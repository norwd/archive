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
#include "cmdtab.h"

static int dircmd(struct actor *, struct object *, struct sentence *);
static int takecmd(struct actor *, struct object *, struct sentence *);
static int dropcmd(struct actor *, struct object *, struct sentence *);
static int lookcmd(struct actor *, struct object *, struct sentence *);
static int invcmd(struct actor *, struct object *, struct sentence *);
static int quitcmd(struct actor *, struct object *, struct sentence *);

static struct cmdtab commands[] =
	{
	"n",		dircmd,
	"north",	dircmd,
	"s",		dircmd,
	"south",	dircmd,
	"e",		dircmd,
	"east",		dircmd,
	"w",		dircmd,
	"west",		dircmd,
	"take",		takecmd,
	"drop",		dropcmd,
	"look",		lookcmd,
	"i",		invcmd,
	"inventory",	invcmd,
	"quit",		quitcmd,
	};

#define Sizeofarray(a) (sizeof(a) / sizeof(a[0]))

/* Interpret a command sentence (incorporating verb, optional object, etc.) */

/* This is the heart of the game, implementing each of the "commands"	*/
/* which the user may type.  Commands are very simple, consisting of	*/
/* a verb, an optional object, and an optional prepositional phrase	*/
/* (all wrapped up in a "struct sentence").				*/
/* The user's command (i.e. verb) is looked up in an array of		*/
/* verbs we know about, and if a match is found, the corresponding	*/
/* action function is called to implement that command.			*/
/*									*/
/* In general, there are several steps to perform for each command:	*/
/* verify that an object (if required) has been specified,		*/
/* verify that the object is present and appropriate for the action	*/
/* requested, attempt to perform the action, and finally print		*/
/* a message indicating that the action has been performed		*/
/* or explaining why it couldn't be.					*/
/*									*/
/* In general, the code here is still at a pretty high level;		*/
/* the work of moving between rooms is centralized in the		*/
/* dircommand() function, and the work of taking and dropping		*/
/* objects is performed by takeobject() and dropobject() in object.c.	*/

docommand(struct actor *player, struct sentence *cmd)
{
struct cmdtab *cmdtp;

cmdtp = findcmd(cmd->verb, commands, Sizeofarray(commands));

if(cmdtp != NULL)
	{
	(*cmdtp->func)(player, cmd->object, cmd);
	return TRUE;
	}
else	{
	printf("I don't know the word \"%s\".\n", cmd->verb);
	return FALSE;
	}
}

static int
takecmd(struct actor *player, struct object *objp,
					struct sentence *cmd)
{
	if(objp == NULL)
		{
		printf("You must tell me what to take.\n");
		return FALSE;
		}
	if(contains(player->contents, objp))
		{
		printf("You already have the %s.\n", objp->name);
		return FALSE;
		}
	if(!takeobject(player, objp))
		{
		/* shouldn't happen */
		printf("You can't pick up the %s.\n", objp->name);
		return FALSE;
		}
	printf("Taken.\n");

return SUCCESS;
}

static int
dropcmd(struct actor *player, struct object *objp,
					struct sentence *cmd)
{
	if(objp == NULL)
		{
		printf("You must tell me what to drop.\n");
		return FALSE;
		}
	if(!contains(player->contents, objp))
		{
		printf("You have no %s.\n", objp->name);
		return FALSE;
		}
	if(!dropobject(player, objp))
		{
		/* shouldn't happen */
		printf("You can't drop the %s!\n", objp->name);
		return FALSE;
		}
	printf("Dropped.\n");

return SUCCESS;
}

static int
lookcmd(struct actor *player, struct object *objp,
					struct sentence *cmd)
{
	listroom(player);

return SUCCESS;
}

static int
invcmd(struct actor *player, struct object *objp,
					struct sentence *cmd)
{
	if(player->contents == NULL)
		printf("You are empty handed.\n");
	else	{
		printf("You are carrying:\n");
		listobjects(player->contents);
		}

return SUCCESS;
}

static int
quitcmd(struct actor *player, struct object *objp,
					struct sentence *cmd)
{
	exit(0);
}

/* Common code for the n, e, w, and s commands.			*/
/* This function just picks the correct exit link (within the	*/
/* room structure) to act on; the gotoroom() function		*/
/* (in rooms.c) does the real work.				*/

static int
dircmd(struct actor *player, struct object *objp,
					struct sentence *cmd)
{
struct room *roomp = player->location;
char *verb = cmd->verb;
int dir;

if(strcmp(verb, "n") == 0 || strcmp(verb, "north") == 0)
	dir = NORTH;
else if(strcmp(verb, "s") == 0 || strcmp(verb, "south") == 0)
	dir = SOUTH;
else if(strcmp(verb, "e") == 0 || strcmp(verb, "east") == 0)
	dir = EAST;
else if(strcmp(verb, "w") == 0 || strcmp(verb, "west") == 0)
	dir = WEST;
else	return ERROR;

if(roomp == NULL)
	{
	printf("Where are you?\n");
	return ERROR;
	}

/* If the exit does not exist, or if gotoroom() fails,	*/
/* the player can't go that way.			*/

if(roomp->exits[dir] == NULL || !gotoroom(player, roomp->exits[dir]))
	{
	printf("You can't go that way.\n");
	return ERROR;
	}

/* player now in new room */

listroom(player);

return SUCCESS;
}
