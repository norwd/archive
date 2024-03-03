/*
 *  "Chapter 1" interface to the Unix stat(2) system call.
 *  Written longer ago than I can remember just now;
 *  tweaked over the years; this comment written 1998-11-11.
 *  The required set of header files for successful compilation
 *  is tricky (particularly to get the major() and minor() macros
 *  for interpreting st_dev and st_rdev), and may need a certain
 *  amount of tuning.
 *
 *  Invoke "stat -help" for a list of invocation options.
 *  Ignore the "accum" and "dfs" options, which are ifdeffed out
 *  (#ifdef ACCUM and DFS) and obsolete.
 *
 *  -f lets you fully customize the output: the "format string"
 *  is a string containing % signs and other text, where the %
 *  signs introduce 2-character sequences which interpolate stat
 *  values in with the surrounding text.  (This is obviously
 *  modeled after C library functions such as printf and strftime.)
 *  The % sequences are:
 *
 *	%a	st_atime, as decimal number
 *	%A	st_atime, as ctime(3) string
 *	%c	st_ctime, as decimal number
 *	%C	st_ctime, as ctime(3) string
 *	%d	st_dev, as decimal number
 *	%D	st_dev, as (major, minor) pair (Unix only)
 *	%g	st_gid, as decimal number
 *	%G	st_gid, expanded as group name (Unix only)
 *	%i	st_ino
 *	%m	st_mtime, as decimal number
 *	%M	st_mtime, as ctime(3) string
 *	%n	st_nlink
 *	%N	file name
 *	%p	st_mode, as octal number
 *	%P	st_mode, as ls(1)-style string ("rw-r--r--")
 *	%r	st_rdev, as decimal number
 *	%R	st_rdev, as (major, minor) pair (Unix only)
 *	%s	st_size
 *	%u	st_uid, as decimal number
 *	%U	st_uid, expanded as user name (Unix only)
 *	%%	print one %
 *
 *  (Note that the % characters largely match the
 *  single-character command line flags.)
 *
 *  Copyright disclaimed; this program placed in the public
 *  domain 2001-10-17.
 *
 *  Steve Summit
 *  scs@eskimo.com
 *
 *  See http://www.eskimo.com/~scs/src/#stat for possible updates.
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef unix
#include <grp.h>
#include <pwd.h>
#endif
#ifdef linux
#include <sys/sysmacros.h>
#endif

#define TRUE 1
#define FALSE 0

#ifdef S_IFSOCK
#define BSD4_2		/* Ain't necessarily so, but close... */
#endif

#ifdef S_IFLNK
#define LSTAT
#endif

/* XXX probably other things to test for 64-bit ino_t and size_t, too */
#if defined (__USE_FILE_OFFSET64) || defined(__USE_FILE_OFFSET64)
#define LONGLONG
#endif

int devflag = FALSE;
int inoflag = FALSE;
int modeflag = FALSE;
int nlinkflag = FALSE;
int uidflag = FALSE;
int gidflag = FALSE;
int rdevflag = FALSE;
int sizeflag = FALSE;
int atimeflag = FALSE;
int mtimeflag = FALSE;
int ctimeflag = FALSE;
#ifdef BSD4_2
int blksizeflag = FALSE;
int blocksflag = FALSE;
#endif

struct tab
	{
	char *t_name;
	char t_char;
	int *t_flagp;
	} tab[] =
	{
	"dev",		'd',	&devflag,
	"ino",		'i',	&inoflag,
	"mode",		'p',	&modeflag,
	"nlink",	'n',	&nlinkflag,
	"uid",		'u',	&uidflag,
	"gid",		'g',	&gidflag,
	"rdev",		'r',	&rdevflag,
	"size",		's',	&sizeflag,
	"atime",	'a',	&atimeflag,
	"mtime",	'm',	&mtimeflag,
	"ctime",	'c',	&ctimeflag,
#ifdef BSD4_2
	"blksize",	0,	&blksizeflag,
	"blocks",	0,	&blocksflag,
#endif
	};

int tabsize = sizeof(tab) / sizeof(tab[0]);

char *progname = "stat";
char *usage = "usage: %s [options] [-f fmt] files\n";
#define VERSION "2.2"		/* 2003-02-18 */

int errs = 0;

char *lsmodes();
#ifndef SIMPLE_LS_MODE 
char *sttype();
#endif

extern char *ctime();
#ifdef unix
extern struct group *getgrgid();
extern struct passwd *getpwuid();
#endif

int
main(argc, argv)
int argc;
char *argv[];
{
struct stat stbuf;
int r;
int nument = 0;
#ifdef DFS
int dfsflag = FALSE;
#endif
#ifdef ACCUM
int accumflag = FALSE;
#endif
int verboselevel = 2;
#ifdef LSTAT
int lstatflag = FALSE;
#endif
char *fmt = NULL;
char *p;
int i, ii;
int l, len;
#ifdef unix
struct passwd *pwp;
struct group *grp;
#endif
int printedhelp = FALSE;

if(argc > 0)
	{
#ifndef vms
	p = strrchr(argv[0], '/');
	if(p != NULL)
		progname = p + 1;
	else
#endif
		progname = argv[0];
	}

#ifdef LSTAT

if(strcmp(progname, "lstat") == 0)
	lstatflag = TRUE;

#endif

for(i = 1; i < argc && argv[i][0] == '-'; i++)
	{
	if(strcmp(argv[i], "-") == 0)	/* means stdin */
		break;

	if(strcmp(argv[i], "--") == 0)	/* means end of arguments */
		{
		i++;
		break;
		}

	for(ii = 0; ii < tabsize; ii++)
		{
		if(strcmp(&argv[i][1], tab[ii].t_name) == 0)
			{
			*tab[ii].t_flagp = TRUE;
			nument++;
			break;
			}
		}

	if(ii < tabsize)
		continue;

	for(p = &argv[i][1]; *p != '\0'; p++)
		{
		switch (*p)
			{
			case '?':
			case 'h':
			case 'H':
				if(strcmp(p, "help") == 0)
					p = "x";	/* short circuit */
				printf(usage, progname);
				printf("options:\n");
				printf("-a\tprint access time (st_atime)\n");
				printf("-c\tprint inode change time (st_ctime)\n");
				printf("-d\tprint device information (st_dev)\n");
				printf("-f fmt\tprint formatted using fmt\n");
				printf("-g\tprint gid (st_gid)\n");
				printf("-i\tprint inode number (st_ino)\n");
#ifdef LSTAT
				printf("-l\tfor symlinks, print status of link%s\n",
					strcmp(progname, "lstat") == 0 ?
							" (default)" : "");
				printf("-L\tfor symlinks, print status of linked-to file%s\n",
					strcmp(progname, "lstat") == 0 ?
							"" : " (default)");
#endif
				printf("-m\tprint modification time (st_mtime)\n");
				printf("-n\tprint nlinks (st_nlink)\n");
				printf("-p\tprint mode (permission) flags (st_mode)\n");
#ifdef ACCUM
				printf("-q\tprint for \"accum\" program\n");
#else
				printf("-q\tquiet\n");
				printf("-qq\tvery quiet\n");
#endif
				printf("-r\tprint rdev (st_rdev)\n");
				printf("-s\tprint size (st_size)\n");
				printf("-u\tprint uid (st_uid)\n");
#ifdef ACCUM
				printf("-v\tquiet (antiverbose)\n");
				printf("-vv\tvery quiet (more antiverbose)\n");
#endif
				printf("-version print (this program's) version number\n");
#ifdef DFS
				printf("-x\tprint for dfs\n");
#endif
				printf("-?,-h\tprint this help\n");
				printedhelp = TRUE;
				break;

			case 'f':
				if(strcmp(p, "fmt") == 0)
					p = "x";	/* short circuit */
				if(i + 1 >= argc)
					fprintf(stderr,
					      "%s: missing format after -%c\n",
								progname, *p);
				else	fmt = argv[++i];
				break;
#ifdef LSTAT
			case 'l':
				lstatflag = TRUE;
				break;

			case 'L':
				lstatflag = FALSE;
				break;
#endif
			case 'q':
#ifdef vms
			case 'Q':
#endif
#ifdef ACCUM
				accumflag = TRUE;
#else
				verboselevel--;
#endif
				break;

			case 'v':
#ifdef vms
			case 'V':
#endif
				if(strcmp(p, "version") == 0)
					{
					printf("%s version %s\n",
							progname, VERSION);
					p = "x";	/* short circuit */
					printedhelp = TRUE;
					break;
					}

				verboselevel--;
				break;
#ifdef DFS
			case 'x':
#ifdef vms
			case 'X':
#endif
				dfsflag = TRUE;
				break;
#endif
			default:
				if(*p == '-' && p == &argv[i][1])
					break;	/* accept --arg */

				for(ii = 0; ii < tabsize; ii++)
					{
					if(*p == tab[ii].t_char)
						{
						*tab[ii].t_flagp = TRUE;
						nument++;
						break;
						}
					}

				if(ii >= tabsize)
					fprintf(stderr,
						"%s: unknown option -%c\n",
								progname, *p);
				break;
			}
		}
	}

if(i >= argc)
	{
	if(printedhelp)
		exit(0);

	fprintf(stderr, usage, progname);
	exit(1);
	}

len = 0;

for(ii = i; ii < argc; ii++)
	{
	l = strlen(argv[ii]);
	if(l > len)
		len = l;
	}

len++;		/* +1 for the colon */

for(; i < argc; i++)
	{
	errno = 0;

#ifdef unix
	if(strcmp(argv[i], "-") == 0)
		{
#ifdef LSTAT
		if(lstatflag)
			fprintf(stderr, "%s: warning: -l ignored for stdin\n",
								progname);
#endif
		r = fstat(0, &stbuf);
		}
	else
#endif
#ifdef LSTAT
	if(lstatflag)
		r = lstat(argv[i], &stbuf);
	else
#endif
		r = stat(argv[i], &stbuf);
#ifdef DFS
	if(dfsflag)
		{
		printf("%d", r);
		printf(" %d\n", errno);
		if(r >= 0)
		    printf("%u\n%lu\n%u\n%u\n%u\n%u\n%u\n%lu\n%ld\n%ld\n%ld\n",
			stbuf.st_dev, (long)stbuf.st_ino, stbuf.st_mode,
			    stbuf.st_nlink, stbuf.st_uid, stbuf.st_gid,
				stbuf.st_rdev, (long)stbuf.st_size, (long)stbuf.st_atime,
				    (long)stbuf.st_mtime, (long)stbuf.st_ctime);
		continue;
		}
#endif
	if(r < 0)
		{
		fprintf(stderr, "%s: can't stat %s: %s\n", progname,
						argv[i], strerror(errno));
		errs++;
		continue;
		}
#ifdef ACCUM
	if(accumflag)
		{
		printf("%s %o %ld %lu\n", argv[i],
			stbuf.st_mode, (long)stbuf.st_atime, (long)stbuf.st_mtime);
		continue;
		}
#endif
	if(fmt != NULL)
		{
		for(p = fmt; *p != '\0'; p++)
			{
			if(*p != '%')
				{
				putchar(*p);
				continue;
				}

			switch(*++p)
				{
				case 'a':
					printf("%ld", (long)stbuf.st_atime);
					break;

				case 'A':
					printf("%.24s", ctime(&stbuf.st_atime));
					break;

				case 'c':
					printf("%ld", (long)stbuf.st_ctime);
					break;

				case 'C':
					printf("%.24s", ctime(&stbuf.st_ctime));
					break;

				case 'd':
					printf("%u", stbuf.st_dev);
					break;
#ifdef unix
				case 'D':
					printf("%d, %d",
						major(stbuf.st_dev),
							minor(stbuf.st_dev));
					break;
#endif
				case 'g':
					printf("%d", stbuf.st_gid);
					break;
#ifdef unix
				case 'G':
					grp = getgrgid(stbuf.st_gid);
					printf("%s",
						(grp != NULL) ? grp->gr_name :
							"");
					break;
#endif
				case 'i':
#ifdef LONGLONG
					printf("%llu", (long long)stbuf.st_ino);
#else
					printf("%lu", (long)stbuf.st_ino);
#endif
					break;

				case 'm':
					printf("%ld", (long)stbuf.st_mtime);
					break;

				case 'M':
					printf("%.24s", ctime(&stbuf.st_mtime));
					break;

				case 'n':
					printf("%d", stbuf.st_nlink);
					break;

				case 'N':
					printf("%s", argv[i]);
					break;

				case 'p':
					printf("%o", stbuf.st_mode);
					break;

				case 'P':
					printf("%s", lsmodes(stbuf.st_mode));
					break;

				case 'r':
					printf("%u", stbuf.st_rdev);
					break;
#ifdef unix
				case 'R':
					printf("%d, %d",
						major(stbuf.st_rdev),
							minor(stbuf.st_rdev));
					break;
#endif
				case 's':
#ifdef LONGLONG
					printf("%llu", (long long)stbuf.st_size);
#else
					printf("%lu", (long)stbuf.st_size);
#endif
					break;

				case 'u':
					printf("%d", stbuf.st_uid);
					break;
#ifdef unix
				case 'U':
					pwp = getpwuid(stbuf.st_uid);
					printf("%s",
						(pwp != NULL) ? pwp->pw_name :
							"");
					break;
#endif
#ifdef notyet
#ifdef BSD4_2
				case '':
					printf("%lu", (long)stbuf.st_blksize);
					break;

				case '':
					printf("%lu", (long)stbuf.st_blocks);
					break;

				case '':
					printf("%lu.%dK", (long)(stbuf.st_blocks / 2),
					     stbuf.st_blocks % 2 == 0 ? 0 : 5);
#endif
#endif
				case '%':
					putchar('%');
					break;

				/* default ignored */
				}
			}

		putchar('\n');

		continue;
		}

	l = len - strlen(argv[i]) - 1;		/* -1 for the colon */

	if(verboselevel > 0)
		printf("%s:", argv[i]);

	if(nument == 0 || devflag)
		{
		if(verboselevel > 0)
			{
			printf("%*s st_dev = ", l, "");
			l = len;
			}
		printf("%u", stbuf.st_dev);
#ifdef unix
		if(verboselevel > 1)
			printf(" = %d, %d",
				major(stbuf.st_dev), minor(stbuf.st_dev));
#endif
		putchar('\n');
		}

	if(nument == 0 || inoflag)
		{
		if(verboselevel > 0)
			{
			printf("%*s st_ino = ", l, "");
			l = len;
			}
#ifdef LONGLONG
		printf("%llu\n", (long long)stbuf.st_ino);
#else
		printf("%lu\n", (long)stbuf.st_ino);
#endif
		}

	if(nument == 0 || modeflag)
		{
		if(verboselevel > 0)
			{
			printf("%*s st_mode = ", l, "");
			l = len;
			}
		printf("%o", stbuf.st_mode);
		if(verboselevel > 1)
			{
#ifdef SIMPLE_LS_MODE 
			printf(" = %s", lsmodes(stbuf.st_mode));
#else
			printf(" = %s, %s", sttype(stbuf.st_mode),
					lsmodes(stbuf.st_mode & 0777) + 1);
#ifdef S_ISUID
			if(stbuf.st_mode & S_ISUID)
				printf(", S_ISUID");
#endif
#ifdef S_ISGID
			if(stbuf.st_mode & S_ISGID)
				printf(", S_ISGID");
#endif
#ifdef S_ISVTX
			if(stbuf.st_mode & S_ISVTX)
				printf(", S_ISVTX");
#endif
#endif
			}
		putchar('\n');
		}

	if(nument == 0 || nlinkflag)
		{
		if(verboselevel > 0)
			{
			printf("%*s st_nlink = ", l, "");
			l = len;
			}
		printf("%d\n", stbuf.st_nlink);
		}

	if(nument == 0 || uidflag)
		{
		if(verboselevel > 0)
			{
			printf("%*s st_uid = ", l, "");
			l = len;
			}
		printf("%d", stbuf.st_uid);
#ifdef unix
		if(verboselevel > 1 && (pwp = getpwuid(stbuf.st_uid)) != NULL)
			printf(" = %s", pwp->pw_name);
#endif
		putchar('\n');
		}

	if(nument == 0 || gidflag)
		{
		if(verboselevel > 0)
			{
			printf("%*s st_gid = ", l, "");
			l = len;
			}
		printf("%d", stbuf.st_gid);
#ifdef unix
		if(verboselevel > 1 && (grp = getgrgid(stbuf.st_gid)) != NULL)
			printf(" = %s",	grp->gr_name);
#endif
		putchar('\n');
		}

	if(nument == 0 || rdevflag)
		{
		if(verboselevel > 0)
			{
			printf("%*s st_rdev = ", l, "");
			l = len;
			}
		printf("%u", stbuf.st_rdev);
#ifdef unix
		if(verboselevel > 1)
			printf(" = %d, %d",
				major(stbuf.st_rdev), minor(stbuf.st_rdev));
#endif
		putchar('\n');
		}

	if(nument == 0 || sizeflag)
		{
		if(verboselevel > 0)
			{
			printf("%*s st_size = ", l, "");
			l = len;
			}
#ifdef LONGLONG
		printf("%llu\n", (long long)stbuf.st_size);
#else
		printf("%lu\n", (long)stbuf.st_size);
#endif
		}

	if(nument == 0 || atimeflag)
		{
		if(verboselevel > 0)
			{
			printf("%*s st_atime = ", l, "");
			l = len;
			}
		printf("%ld", (long)stbuf.st_atime);
		if(verboselevel > 1)
			printf(" = %.24s", ctime(&stbuf.st_atime));
		putchar('\n');
		}

	if(nument == 0 || mtimeflag)
		{
		if(verboselevel > 0)
			{
			printf("%*s st_mtime = ", l, "");
			l = len;
			}
		/* XXX how to deal with subsec precision (if implemented) ? */
		printf("%ld", (long)stbuf.st_mtime);
		if(verboselevel > 1)
			printf(" = %.24s", ctime(&stbuf.st_mtime));
		putchar('\n');
		}

	if(nument == 0 || ctimeflag)
		{
		if(verboselevel > 0)
			{
			printf("%*s st_ctime = ", l, "");
			l = len;
			}
		printf("%ld", (long)stbuf.st_ctime);
		if(verboselevel > 1)
			printf(" = %.24s", ctime(&stbuf.st_ctime));
		putchar('\n');
		}
#ifdef BSD4_2
	if(nument == 0 || blksizeflag)
		{
		if(verboselevel > 0)
			{
			printf("%*s st_blksize = ", l, "");
			l = len;
			}
		printf("%lu\n", (long)stbuf.st_blksize);
		}

	if(nument == 0 || blocksflag)
		{
		if(verboselevel > 0)
			{
			printf("%*s st_blocks = ", l, "");
			l = len;
			}
		printf("%lu", (long)stbuf.st_blocks);
		if(verboselevel > 1)
			printf(" = %lu.%dK", (long)(stbuf.st_blocks / 2),
					stbuf.st_blocks % 2 == 0 ? 0 : 5);
		putchar('\n');
		}
#endif
	}

if(errs > 0)
	exit(1);

return 0;
}

char *
lsmodes(mode)
int mode;
{
static char retbuf[11];
int ifmt = mode & S_IFMT;

if(ifmt == S_IFDIR)
	retbuf[0] = 'd';
#ifdef S_IFCHR
else if(ifmt == S_IFCHR)
	retbuf[0] = 'c';
#endif
#ifdef S_IFBLK
else if(ifmt == S_IFBLK)
	retbuf[0] = 'b';
#endif
#ifdef S_IFLNK
else if(ifmt == S_IFLNK)
	retbuf[0] = 'l';
#endif
#ifdef S_IFSOCK
else if(ifmt == S_IFSOCK)
	retbuf[0] = 's';
#endif
#ifdef S_IFIFO
else if(ifmt == S_IFIFO)
	retbuf[0] = 'p';
#endif
else	retbuf[0] = '-';

lsrwx(&retbuf[1], mode);
lsrwx(&retbuf[4], mode << 3);
lsrwx(&retbuf[7], mode << 6);

#ifdef S_ISUID
if(mode & S_ISUID)
	retbuf[3] = (mode & S_IEXEC) ? 's' : 'S';
#endif

#ifdef S_ISGID
if(mode & S_ISGID)
	retbuf[6] = (mode & (S_IEXEC >> 3)) ? 's' : 'S';
#endif

#ifdef S_ISVTX
if(mode & S_ISVTX)
	retbuf[9] = (mode & (S_IEXEC >> 6)) ? 't' : 'T';
#endif

retbuf[10] = '\0';

return(retbuf);
}

lsrwx(p, mode)
char *p;
int mode;
{
if(mode & S_IREAD)
	p[0] = 'r';
else	p[0] = '-';

if(mode & S_IWRITE)
	p[1] = 'w';
else	p[1] = '-';

if(mode & S_IEXEC)
	p[2] = 'x';
else	p[2] = '-';
}

char *
sttype(mode)
int mode;
{
switch(mode & S_IFMT)
	{
#ifdef S_IFREG
	case S_IFREG:
		return "S_IFREG";
#endif
#ifdef S_IFDIR
	case S_IFDIR:
		return "S_IFDIR";
#endif
#ifdef S_IFCHR
	case S_IFCHR:
		return "S_IFCHR";
#endif
#ifdef S_IFBLK
	case S_IFBLK:
		return "S_IFBLK";
#endif
#ifdef S_IFLNK
	case S_IFLNK:
		return "S_IFLNK";
#endif
#ifdef S_IFSOCK
	case S_IFSOCK:
		return "S_IFSOCK";
#endif
#ifdef S_IFIFO
	case S_IFIFO:
		return "S_IFIFO";
#endif
	default:
		{
		static char tmpbuf[10];
		/* XXX too cute */
		sprintf(tmpbuf, "S_IF%03o", (mode & S_IFMT) >> 12);
		return tmpbuf;
		}
	}
}
