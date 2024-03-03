#include <stdio.h>
#include "defs.h"
#include "game.h"
#include "utils.h"

#define MAXARGS 10

/* Second, slightly smarter version:				*/
/* splits command line into words,				*/
/* assumes "verb", "verb object", or				*/
/* "verb object preposition object2"				*/
/* (examples: "look", "north", "get axe", "drop vase",		*/
/* "hit nail with hammer").					*/

int
parseline(struct actor *actor, char *line, struct sentence *cmd)
{
int ac;
char *av[MAXARGS];

ac = getwords(line, av, MAXARGS);

if(ac < 1)
	{
	/* blank line */
	return FALSE;
	}

cmd->verb = cmd->preposition = NULL;
cmd->object = cmd->xobject = NULL;

if(ac > 4)
	{
	output(actor, "command too complicated\n");
	return FALSE;
	}

cmd->verb = av[0];

if(ac < 2)
	cmd->object = NULL;
else if((cmd->object = findobject(actor, av[1])) == NULL)
	{
	output(actor, "I see no %s here.\n", av[1]);
	return FALSE;
	}

if(ac > 2)
	{
	cmd->preposition = av[2];

	cmd->xobject = findobject(actor, av[3]);\
	if(cmd->xobject == NULL)
		{
		output(actor, "I see no %s here.\n", av[3]);
		return FALSE;
		}
	}

return TRUE;
}
