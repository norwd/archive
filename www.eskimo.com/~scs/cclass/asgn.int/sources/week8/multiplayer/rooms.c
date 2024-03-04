#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "defs.h"

#define MAXROOMS 100

static struct room rooms[MAXROOMS];
static int nrooms = 0;

struct room *
newroom(char *name)
{
struct room *roomp;
int i;

if(nrooms >= MAXROOMS)
	{
	fprintf(stderr, "too many rooms\n");
	exit(1);
	}

roomp = &rooms[nrooms++];

strcpy(roomp->name, name);
roomp->contents = NULL;
for(i = 0; i < NEXITS; i++)
	roomp->exits[i] = NULL;

return roomp;
}

struct room *
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

struct room *
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
listroom(struct actor *actp)
{
struct room *roomp = actp->location;
if(roomp == NULL)
	{
	output(actp, "Where are you?\n");
	return;
	}
output(actp, "%s\n", roomp->name);
if(roomp->contents != NULL)
	{
	output(actp, "room contains:\n");
	listobjects(actp, roomp->contents);
	}
}

/* Move the player to a new room.			*/
/* (Quite simple, for now.)				*/

int
gotoroom(struct actor *actor, struct room *room)
{
actor->location = room;
return TRUE;
}
