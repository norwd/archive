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
static int opencmd(struct actor *, struct object *, struct sentence *);
static int closecmd(struct actor *, struct object *, struct sentence *);
static int putcmd(struct actor *, struct object *, struct sentence *);
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
	"open",		opencmd,
	"close",	closecmd,
	"put",		putcmd,
	"quit",		quitcmd,
	};

#define Sizeofarray(a) (sizeof(a) / sizeof(a[0]))

extern void closeconnection(struct actor *);

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
int r;
struct cmdtab *cmdtp;

if(cmd->object != NULL && cmd->object->func != NULL)
	{
	r = (*cmd->object->func)(player, cmd->object, cmd);
	if(r != CONTINUE)
		return r;
	}
	
if(cmd->xobject != NULL && cmd->xobject->func != NULL)
	{
	r = (*cmd->xobject->func)(player, cmd->xobject, cmd);
	if(r != CONTINUE)
		return r;
	}
cmdtp = findcmd(cmd->verb, commands, Sizeofarray(commands));

if(cmdtp != NULL)
	{
	(*cmdtp->func)(player, cmd->object, cmd);
	return TRUE;
	}
else	{
	output(player, "I don't know the word \"%s\".\n", cmd->verb);
	return FALSE;
	}
}

static int
takecmd(struct actor *player, struct object *objp,
					struct sentence *cmd)
{
	if(objp == NULL)
		{
		output(player, "You must tell me what to take.\n");
		return FALSE;
		}
	if(contains(player->contents, objp))
		{
		output(player, "You already have the %s.\n", objp->name);
		return FALSE;
		}
	if(hasattr(objp, "immobile"))
		{
		output(player, "The %s cannot be picked up.\n", objp->name);
		return FALSE;
		}
	if(!takeobject(player, objp))
		{
		/* shouldn't happen */
		output(player, "You can't pick up the %s.\n", objp->name);
		return FALSE;
		}
	output(player, "Taken.\n");

return SUCCESS;
}

static int
dropcmd(struct actor *player, struct object *objp,
					struct sentence *cmd)
{
	if(objp == NULL)
		{
		output(player, "You must tell me what to drop.\n");
		return FALSE;
		}
	if(!contains(player->contents, objp))
		{
		output(player, "You have no %s.\n", objp->name);
		return FALSE;
		}
	if(!dropobject(player, objp))
		{
		/* shouldn't happen */
		output(player, "You can't drop the %s!\n", objp->name);
		return FALSE;
		}
	output(player, "Dropped.\n");

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
		output(player, "You are empty handed.\n");
	else	{
		output(player, "You are carrying:\n");
		listobjects(player, player->contents);
		}

return SUCCESS;
}
static int
opencmd(struct actor *player, struct object *objp,
					struct sentence *cmd)
{
	if(objp == NULL)
		{
		output(player, "You must tell me what to open.\n");
		return FALSE;
		}
	if(Isopen(objp))
		{
		output(player, "The %s is already open.\n", objp->name);
		return FALSE;
		}
	if(!hasattr(objp, "closable"))
		{
		output(player, "You can't open the %s.\n", objp->name);
		return FALSE;
		}
	setattr(objp, "open");
	output(player, "The %s is now open.\n", objp->name);

return SUCCESS;
}

static int
closecmd(struct actor *player, struct object *objp,
					struct sentence *cmd)
{
	if(objp == NULL)
		{
		output(player, "You must tell me what to close.\n");
		return FALSE;
		}
	if(!hasattr(objp, "closable"))
		{
		output(player, "You can't close the %s.\n", objp->name);
		return FALSE;
		}
	if(!Isopen(objp))
		{
		output(player, "The %s is already closed.\n", objp->name);
		return FALSE;
		}
	unsetattr(objp, "open");
	output(player, "The %s is now closed.\n", objp->name);

return SUCCESS;
}

static int
putcmd(struct actor *player, struct object *objp,
					struct sentence *cmd)
{
	if(objp == NULL)
		{
		output(player, "You must tell me what to put.\n");
		return FALSE;
		}
	if(!contains(player->contents, objp))
		{
		output(player, "You don't have the %s.\n", objp->name);
		return FALSE;
		}
	if(cmd->preposition == NULL || strcmp(cmd->preposition, "in") != 0 ||
			cmd->xobject == NULL)
		{
		output(player, "You must tell me where to put the %s.\n",
							objp->name);
		return FALSE;
		}
	if(!Iscontainer(cmd->xobject))
		{
		output(player, "You can't put things in the %s.\n",
							cmd->xobject->name);
		return FALSE;
		}
	if(hasattr(cmd->xobject, "closable") && !Isopen(cmd->xobject))
		{
		output(player, "The %s is closed.\n", cmd->xobject->name);
		return FALSE;
		}
	if(!putobject(player, objp, cmd->xobject))
		{
		/* shouldn't happen */
		output(player, "You can't put the %s in the %s!\n",
			objp->name, cmd->xobject->name);
		return FALSE;
		}
	output(player, "Now the %s is in the %s.\n",
			objp->name, cmd->xobject->name);

return SUCCESS;
}

static int
quitcmd(struct actor *player, struct object *objp,
					struct sentence *cmd)
{
	closeconnection(player);
}

/* Common code for the n, e, w, and s commands.			*/
/* This function just picks the correct exit link (within the	*/
/* room structure) to act on; the gotoroom() function		*/
/* (in rooms.c) does the real work.				*/

static int
dircmd(struct actor *player, struct object *objp,
					struct sentence *cmd)
{
room *roomp = (room *)player->container;	/* XXX assumes actor not in vehicle or container */
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
	output(player, "Where are you?\n");
	return ERROR;
	}

/* If the exit does not exist, or if gotoroom() fails,	*/
/* the player can't go that way.			*/

if(roomp->exits[dir] == NULL || !gotoroom(player, roomp->exits[dir]))
	{
	output(player, "You can't go that way.\n");
	return ERROR;
	}

/* player now in new room */

listroom(player);

return SUCCESS;
}
