/*% cc -O3 -g -o # %
 * pi [-n N] [-h]
 * Computes decimals of pi.
 * It uses a spigot algorithm by
 * Rabinowitz and Wagon, the idea is to
 * write pi in a mixed radix
 * representation and convert it to 10
 * radix representation with elementary
 * functions on integers.
 *
 * The program will abort if a carry
 * needs to go too far on predigits.
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

unsigned long long *a;
unsigned na;
char dgts[5];

#define F 10000ull
void
digit(void)
{
	static int pre;
	unsigned long long i, q, c, *d;

	d = &a[na - 1];
	c = 0;
	for (i=na; i>1; i--, d--) {
		*d = *d * F + c;
		q = *d / (2*i - 1);
		*d = *d % (2*i - 1);
		c = q*(i - 1);
	}
	*d = *d * F + c;
	if (*d/F >= F) {
		if (pre == F-1) abort(); /* Heck. */
		pre++;
	}
	sprintf(dgts, "%04d", pre);
	pre = *d/F;
	*d = *d % F;
}

int
main(int argc, char *argv[])
{
	int o;
	unsigned l, i, ndgts = 104;

	while ((o=getopt(argc, argv, "n:h"))>=0)
		switch (o) {
		case 'n':
			ndgts = strtol(optarg, 0, 0);
			if (!ndgts) goto usage;
			break;
		case 'h':
		case '?':
		usage:
			fputs("pi [-n N] [-h]\n", stderr);
			exit(0);
		}

	na = ndgts*10/3 + 6;
	if (!(a=malloc(sizeof *a * na))) {
		fputs("Not enough memory.\n", stderr);
		exit(1);
	}
	for (i=0; i<na; i++)
		a[i] = 2;

	digit();
	for (l=i=0; i<ndgts/4; i++, l++) {
		if (l==13) {
			putc('\n', stdout);
			l = 0;
		}
		digit();
		fputs(dgts, stdout);
	}
	putc('\n', stdout);

	free(a);
	exit(0);
}
