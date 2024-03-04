#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chkmalloc.h"

void *
chkmalloc(size_t sz)
{
void *ret = malloc(sz);
if(ret == NULL)
	{
	fprintf(stderr, "Out of memory\n");
	exit(EXIT_FAILURE);
	}
return ret;
}

char *
chkstrdup(char *str)
{
char *ret = chkmalloc(strlen(str) + 1);
strcpy(ret, str);
return ret;
}
