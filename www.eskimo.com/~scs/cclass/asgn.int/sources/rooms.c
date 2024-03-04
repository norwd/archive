#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "defs.h"

/* Tell the player about the room he's in -- its name and contents.	*/
/* Typically called upon entering a room, or in response to the		*/
/* "look" command.							*/

void
listroom(struct actor *actor)
{
struct room *roomp = actor->location;
if(roomp == NULL)
	{
	printf("Where are you?\n");
	return;
	}
printf("%s\n", roomp->name);
if(roomp->contents != NULL)
	{
	printf("room contains:\n");
	listobjects(roomp->contents);
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
