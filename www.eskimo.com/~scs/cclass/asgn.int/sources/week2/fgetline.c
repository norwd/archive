#include <stdio.h>
#include "utils.h"

/* read one line from fp */
/* does not return terminating \n in line */
/* returns line length: 0 for empty line, EOF for end-of-file */

int fgetline(FILE *fp, char line[], int max)
{
int nch = 0;
int c;
max = max - 1;			/* leave room for '\0' */

while((c = getc(fp)) != EOF)
	{
	if(c == '\n')
		break;

	if(nch < max)
		line[nch++] = c;
	}

if(c == EOF && nch == 0)
	return EOF;

line[nch] = '\0';

return nch;
}
