/*
 *  Program for extracting random lines from text files.
 *  Uses the classic one-pass algorithm described in Knuth, §xxx.
 *  (Since it's one-pass, works fine if input is a pipe.)
 *
 *  Also has a simple extension to select n random lines, rather
 *  than just one.
 *
 *  (Use the -help flag for information on options.)
 *
 *  Steve Summit, scs@eskimo.com
 *
 *  Placed in the Public Domain 2003-02-22.
 *
 *  This is an older, simpler, standalone version of the program.
 *  See http://www.eskimo.com/~scs/src/#randline for full documentation
 *  and for a newer, somewhat fancier version.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

#define MAXLINE 1000	/* XXX temporary */

struct aline
       {
       char *ptr;
       int nalloc;
       };

struct aline *keeplines;

int exitstatus = 0;

char *progname = "randline";
char usage[] = "usage: %s [-n #] [-s] [files]\n";

#define VERSION "1.0"

int nr = 1;
int sflag = FALSE;

#ifdef __STDC__

void randline(FILE *);
void randomize(void);
int randrange(int);
void savestr(struct aline *, char *);

#endif

void randline();
void randomize();
void savestr();

int
main(argc, argv)
int argc;
char *argv[];
{
int argi;
FILE *ifp;
int i;

for(argi = 1; argi < argc && argv[argi][0] == '-'; argi++)
	{
	char *p;

	if(strcmp(argv[argi], "-") == 0)	/* means stdin */
		break;

	if(strcmp(argv[argi], "--") == 0)	/* means end of opts */
		{
		argi++;
		break;
		}

	for(p = &argv[argi][1]; *p != '\0'; p++)
		{
		if(p == &argv[argi][1] && *p == '-')
			continue;		/* cheesily allow --longname */

		switch(*p)
			{
			case '?':
printhelp:			printf(usage, progname);
				printf("options:\n");
				printf("\t-n n\tselect n lines\n");
				printf("\t-?,-h\tprint this help\n");
				return 0;

			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				nr = atoi(p);
				p = "x";
				break;

			case 'h':
				if(strcmp(p, "help") == 0)
					p = "x";     /* short circuit */
				goto printhelp;

			case 'n':
				nr = atoi(argv[++argi]);
				break;

			case 's':
				sflag = TRUE;
				break;

			case 'v':
				if(strcmp(p, "version") == 0)
					{
					printf("%s version %s\n",
						progname, VERSION);
					return 0;
					}
				goto badopt;

			default:
badopt:				fprintf(stderr, "%s: unknown option -%c\n", progname, *p);
				break;
			}
		}
	}

keeplines = malloc(nr * sizeof(*keeplines));
if(keeplines == NULL)
	{
	fprintf(stderr, "%s: can't allocate space for %d lines\n",
						progname, nr);
	exit(1);
	}

for(i = 0; i < nr; i++)
	{ keeplines[i].nalloc = 0; keeplines[i].ptr = NULL; }

randomize();

if(argi >= argc)
	randline(stdin);
else for(; argi < argc; argi++)
	{
	if(strcmp(argv[argi], "-") == 0)
		ifp = stdin;
	else if((ifp = fopen(argv[argi], "r")) == NULL)
		{
		fprintf(stderr, "%s: can't open %s: %s\n", progname,
						argv[argi], strerror(errno));
		exitstatus = 1;
		continue;
		}

	randline(ifp);

	if(ifp != stdin)
		fclose(ifp);
	}

return exitstatus;
}

void
randline(ifp)
FILE *ifp;
{
int lineno;
char line[MAXLINE];
int nkeep = 0;
int i;

lineno = 1;

while(fgets(line, MAXLINE, ifp) != NULL)
	{
	if(randrange(lineno) < nr)
		{
		if(nkeep < nr)
			savestr(&keeplines[nkeep++], line);
		else	{
			i = 0;
			if(nr > 1)
				i = randrange(nr);
			if(nr == 1 || !sflag)
				savestr(&keeplines[i], line);
			else	{
				int nm = nr - i - 1;
				if(nm > 0)
					{
					struct aline tmp = keeplines[i];
					memmove(&keeplines[i], &keeplines[i+1],
						nm * sizeof(*keeplines));
					keeplines[nkeep-1] = tmp;
					}
				savestr(&keeplines[nkeep-1], line);
				}
			}
		}

	lineno++;
	}

if(nkeep < nr)
	fprintf(stderr, "%s: warning: input didn't contain %d lines\n", progname, nr);

for(i = 0; i < nkeep; i++)
	fputs(keeplines[i].ptr, stdout);
}

void
randomize()
{
unsigned int seed;

seed = (unsigned int)time((time_t *)NULL);
#ifdef unix
seed ^= getpid() << 8;
#endif

srand(seed);
}

int
randrange(N)
int N;
{
return rand() / (RAND_MAX / N + 1);
}

void
savestr(alp, line)
struct aline *alp;
char *line;
{
int need = strlen(line) + 1;
if(need > alp->nalloc)
	{
	alp->nalloc = need;
	if(alp->nalloc < 80)	/* arbitrary threshold */
		alp->nalloc = 80;

#ifndef SAFEREALLOC
	if(alp->ptr == NULL)
		alp->ptr = malloc(alp->nalloc);
	else
#endif
		alp->ptr = realloc(alp->ptr, alp->nalloc);

	if(alp->ptr == NULL)
		{
		fprintf(stderr, "%s: can't (re)allocate space for saved line\n",
								progname);
		exit(1);
		}
	}

strcpy(alp->ptr, line);
}
