/*
 *  Text-based dungeon/adventure game, for the
 *  UW Experimental College course in Intermediate C Programming
 *
 *  Copyright 1996-1999 Steve Summit
 *  scs@eskimo.com
 */

#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "utils.h"
#include "defs.h"

#define MAXLINE 100

/* Declare the objects which will exist in the game.		*/
/* Each object contains a "next" field, so that the set of	*/
/* objects in a particular room (or in an actor's possession)	*/
/* can be implemented as a linked list.				*/
/* We can see that the hammer and the pliers (objects 3 and 4)	*/
/* are linked together and so must be in the same room;		*/
/* similarly for the pick and shovel.				*/

static struct object objects[] =
	  {
/* [0] */ {"bed", NULL},
/* [1] */ {"diamond", NULL},
/* [2] */ {"kettle", NULL},
/* [3] */ {"hammer", NULL},
/* [4] */ {"pliers", &objects[3]},
/* [5] */ {"doormat", NULL},
/* [6] */ {"pick", NULL},
/* [7] */ {"shovel", &objects[6]},
	  };


/* Declare the rooms which will make up the playing field.	*/
/* This is an array of structures, one per room.		*/
/* The structure instance describing one room gives not only	*/
/* the room's name, but also the room's initial contents	*/
/* (expressed as a pointer to one of the room's objects,	*/
/* where the rest of the objects, if any, are linked together	*/
/* in a list).  Finally, up to 4 exits from the room are	*/
/* listed, expressed as pointers to the adjoining room(s).	*/
/*								*/
/* These structures describe only the initial configuration of	*/
/* the game; the pointers will be adjusted as the actor begins	*/
/* picking up objects and moving them around.			*/
/* (Also, this is a particularly awkward way to specify the	*/
/* initial game configuration.  We'll be making it cleaner and	*/
/* easier later.)						*/

static struct room rooms[] =
	   {
/* [0]  */ {"field", NULL, {&rooms[1], NULL, NULL, NULL}},
/* [1]  */ {"house", NULL, {&rooms[2], &rooms[0], NULL, NULL}},
/* [2]  */ {"entry", NULL, {&rooms[3], &rooms[2], &rooms[5], NULL}},
/* [3]  */ {"hall", NULL, {&rooms[6], &rooms[2], NULL, &rooms[4]}},
/* [4]  */ {"bedroom", &objects[0], {NULL, NULL, &rooms[3], NULL}},
/* [5]  */ {"closet", &objects[1], {NULL, NULL, NULL, &rooms[2]}},
/* [6]  */ {"kitchen", &objects[2], {&rooms[9], &rooms[3], &rooms[7], NULL}},
/* [7]  */ {"stairway", NULL, {NULL, NULL, &rooms[6], &rooms[8]}},
/* [8]  */ {"basement", &objects[4], {NULL, NULL, &rooms[7], &rooms[10]}},
/* [9]  */ {"porch", &objects[5], {NULL, &rooms[6], NULL, NULL}},
/* [10] */ {"tunnel", &objects[7], {NULL, NULL, NULL, NULL}},
	   };

static struct actor player = {&rooms[0], NULL};

/* The main loop of the game.  At the top level, the action is	*/
/* simple: print a prompt, read a command string, parse the	*/
/* string, and try to execute it.  The parseline() and		*/
/* docommand() functions do most of the work; main() is just	*/
/* the conductor, directing the top-level flow.			*/

main()
{
char line[MAXLINE];
char *verb, *object;

listroom(&player);

while(TRUE)
	{
	printf("? ");
	fflush(stdout);
	
	if(getline(line, MAXLINE) == EOF)
		break;

	if(!parseline(line, &verb, &object))
		continue;

	docommand(&player, verb, object);
	}

return 0;
}
