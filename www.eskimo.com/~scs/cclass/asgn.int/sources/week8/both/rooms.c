#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "defs.h"

#define MAXROOMS 100

static struct room rooms[MAXROOMS];
static int nrooms = 0;

room::room(const char *newname) : object(newname)
{
int i;

if(nrooms >= MAXROOMS)
	{
	fprintf(stderr, "too many rooms\n");
	exit(1);
	}

roomp = &rooms[nrooms++];

for(i = 0; i < NEXITS; i++)
	exits[i] = NULL;
}

room *
findroom(char *name)
{
int i;

for(i = 0; i < nrooms; i++)
	{
	if(strcmp(rooms[i].name, name) == 0)
		return &rooms[i];
	}

return NULL;
}

room *
getentryroom(void)
{
if(nrooms == 0)
	return NULL;
return &rooms[0];	/* temporary */
}

/* Tell the player about the room he's in -- its name and contents.	*/
/* Typically called upon entering a room, or in response to the		*/
/* "look" command.							*/

void
listroom(actor *actp)
{
room *roomp = (room *)actp->container;	/* XXX assumes actor not in vehicle or container */
if(roomp == NULL)
	{
	output(actp, "Where are you?\n");
	return;
	}
output(actp, "%s\n", roomp->name);
/* if room contains objects *other* than actor... */
if(roomp->contents != NULL &&
		(roomp->contents != actp || roomp->contents->lnext != NULL))
	{
	output(actp, "room contains:\n");
	listobjects(actp, roomp->contents);
	}
}

/* Move the player to a new room.			*/
/* (Quite simple, for now.)				*/

int
gotoroom(actor *actor, room *room)
{
return transferobject(actor, room);
}
