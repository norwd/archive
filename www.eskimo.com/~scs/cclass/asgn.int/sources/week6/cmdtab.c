#include <string.h>
#include "cmdtab.h"

struct cmdtab *
findcmd(char *cmd, struct cmdtab cmdtab[], int ncmds)
{
int i;

for(i = 0; i < ncmds; i++)
	{
	if(strcmp(cmdtab[i].name, cmd) == 0)
		return &cmdtab[i];
	}

return NULL;
}
