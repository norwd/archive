/* 
 *  count [ from ] to [ by [ fmt ]]
 *
 *  Counts from from to to, with an increment of by.
 *  (from and by default to 1.)
 *  A fourth argument is a printf format string to use other than %d.
 *
 *  Steve Summit   5/6/1982
 *
 *  Placed in the Public Domain 2002-01-05.
 *
 *  This is an older, simpler, standalone version of the program.
 *  See http://www.eskimo.com/~scs/src/#count for a newer, somewhat
 *  fancier version.
 */

#include <stdio.h>

main(argc, argv)
int argc;
char *argv[];
{
int from, to, by;
char *fmt = "%d";
int argi = 1;
int i;

if(argi >= argc)
	{
	fprintf(stderr,"usage: count [ from ] to [ by [ format ]]\n");
	exit(1);
	}

from = 1;
if(argi < argc-1) from = atoi(argv[argi++]);
to = atoi(argv[argi++]);
by = 1;
if(argi < argc) by = atoi(argv[argi++]);

if(argi < argc) fmt = argv[argi++];

for(i = from; by > 0 ? i <= to : i >= to; i += by)
	{
	printf(fmt, i, i, i, i, i); /* really need an arbitrary number of i's */
	putchar('\n');
	}
}
