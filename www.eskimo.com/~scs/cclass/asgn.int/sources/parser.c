#include <stdio.h>
#include "defs.h"
#include "game.h"
#include "utils.h"

#define MAXARGS 10

/* First, simpleminded version:					*/
/* splits command line into words,				*/
/* assumes either "verb" or "verb object"			*/
/* (examples: "look", "north", "get axe", "drop vase").		*/
/* Returns both verb and object as strings, using pointers.	*/
/* So verbp and objp parameters are type "pointer to string",	*/
/* or pointer-to-pointer-to-char.				*/
/* (Typically, the caller will declare char * variables		*/
/* to receive these two words, and will pass pointers to them	*/
/* when calling parseline, e.g. the call			*/
/*	parseline(line, &verb, &object)				*/
/* in main.c.)							*/

int
parseline(char *line, char **verbp, char **objp)
{
int ac;
char *av[MAXARGS];

ac = getwords(line, av, MAXARGS);

if(ac < 1)
	{
	/* blank line */
	return FALSE;
	}

if(ac > 2)
	{
	printf("command too complicated\n");
	return FALSE;
	}

*verbp = av[0];
if(ac > 1)
	*objp = av[1];
else	*objp = NULL;

return TRUE;
}
