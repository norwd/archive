#include <stdio.h>
#include "utils.h"

/* read one line from standard input */
/* does not return terminating \n in line */
/* returns line length: 0 for empty line, EOF for end-of-file */

int getline(char line[], int max)
{
int nch = 0;
int c;
max = max - 1;			/* leave room for '\0' */

while((c = getchar()) != EOF)
	{
	if(c == '\n')
		break;

	if(nch < max)
		{
		line[nch] = c;
		nch = nch + 1;
		}
	}

if(c == EOF && nch == 0)
	return EOF;

line[nch] = '\0';
return nch;
}
