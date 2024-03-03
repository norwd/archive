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

class actor player;

int multiplayer = FALSE;

extern int domultiplayer(void);

/* The main loop of the game.  At the top level, the action is	*/
/* simple: print a prompt, read a command string, parse the	*/
/* string, and try to execute it.  The parseline() and		*/
/* docommand() functions do most of the work; main() is just	*/
/* the conductor, directing the top-level flow.			*/

int main(int argc, char *argv[])
{
char line[MAXLINE];
struct sentence cmd;

if(argc > 1 && strcmp(argv[1], "-m") == 0)
	multiplayer = TRUE;

if(!readdatafile())
	exit(1);

if(multiplayer)
	{
	domultiplayer();
	exit(0);
	}

gotoroom(&player, getentryroom());	/* put player in initial room */
listroom(&player);

while(TRUE)
	{
	printf("? ");
	fflush(stdout);
	
	if(getline(line, MAXLINE) == EOF)
		break;

	if(!parseline(&player, line, &cmd))
		continue;

	docommand(&player, &cmd);
	}

return 0;
}
