/*% clang -Wall -o # %
 * romint [-r num] [-a romnum] [-h]
 * Converts roman numerals into arabic ones
 * and vice versa.
 * Numbers must be smaller than 6000 for the
 * program to work nicely.
 * Note that the parser is totally ugly, but
 * so are roman numerals...
 * Using the program with -t will test if the
 * functions conv and rconv are more or less
 * bug free.
 */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static char *
conv(long i)
{
	static char res[64];
	char * p = res;

	if (i >= 6000 || i < 0) {
		strcpy(res, "Error");
		return res;
	}
	while (i) {
		if      (i >= 1000) { *p++ = 'M';             i -= 1000; }
		else if (i >= 900)  { *p++ = 'C', *p++ = 'M'; i -= 900;  }
		else if (i >= 500)  { *p++ = 'D';             i -= 500;  }
		else if (i >= 400)  { *p++ = 'C', *p++ = 'D'; i -= 400;  }
		else if (i >= 90)   { *p++ = 'X', *p++ = 'C'; i -= 90;   }
		else if (i >= 50)   { *p++ = 'L';             i -= 50;   }
		else if (i >= 40)   { *p++ = 'X'; *p++ = 'L'; i -= 40;   }
		else if (i >= 10)   { *p++ = 'X';             i -= 10;   }
		else if (i >= 9)    { *p++ = 'I'; *p++ = 'X'; i -= 9;    }
		else if (i >= 5)    { *p++ = 'V';             i -= 5;    }
		else if (i >= 4)    { *p++ = 'I'; *p++ = 'V'; i -= 4;    }
		else if (i >= 1)    { *p++ = 'I';             i -= 1;    }
	}
	*p = 0;
	return res;
}

static long
rconv(const char * s)
{
	int seen_C = 0, seen_I = 0, seen_X = 0;
	long i = 0;

	while (*s) {
		switch (*s++) {
		case 'M':
			if (seen_C) { seen_C = 0; i += 900; }
			else        { i += 1000; }
			break;
		case 'D':
			if (seen_C) { seen_C = 0; i += 400; }
			else        { i += 500; }
			break;
		case 'C':
			if (seen_X)      { seen_X = 0; i += 90; }
			else if (seen_C) { i += 100; continue; }
			else             { seen_C = 1; continue; }
			break;
		case 'L':
			if (seen_X) { seen_X = 0; i += 40; }
			else        { i += 50; }
			break;
		case 'X':
			if (seen_I)      { seen_I = 0; i += 9; }
			else if (seen_X) { i += 10; continue; }
			else             { seen_X = 1; continue; }
			break;
		case 'V':
			if (seen_I) { seen_I = 0; i += 4; }
			else        { i += 5; }
			break;
		case 'I':
			if (seen_I) i += 1;
			seen_I = 1;
			continue;
		}
		i += seen_C * 100 + seen_X * 10 + seen_I;
		seen_C = seen_I = seen_X = 0;
	}
	i += seen_C * 100 + seen_X * 10 + seen_I;
	return i;
}

int
main(int argc, char ** argv)
{
	int o;
	long n;

	while ((o=getopt(argc, argv, "thr:a:")) > 0)
		switch (o) {
		default:
		case '?':
			return 1;
		case 'a':
			printf("%s -> %li\n", optarg, rconv(optarg));
			break;
		case 'r':
			n = strtol(optarg, NULL, 10);
			printf("%ld -> %s\n", n, conv(n));
			break;
		case 't':
			for (n = 0; n < 6000; n++)
			    if (rconv(conv(n)) != n) printf("err on %ld\n", n);
			puts("done.");
			break;
		case 'h':
			puts("romint [-r num] [-a romnum] [-h]");
			return 0;
		}
	return 0;
}
