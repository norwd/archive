/*% cc -O3 -o # %
 * permut N
 * Compute permutations of N objects.
 * It uses an elementary algorithm to
 * enumerate all N! possible permutations.
 * Every integer between 0 and N!-1 is
 * decomposed as a sequence
 * a_{n-1} + (n-1)*(a_{n-2} + (n-2)*(... 1*a_1) ... )
 * where 0 <= a_k < k. Then each a_k is
 * used to swap the current permutation.
 *
 * Note that each permutation of N
 * elements can be viewed as a the
 * identity permutation where the first
 * element has been swapped with one of
 * the N-1 following elements, the second
 * with one of the N-2 following, etc.
 */
#include <stdlib.h>
#include <stdio.h>
#define N 30

unsigned
fact(unsigned n)
{
	unsigned f=1;

	for (; n; n--)
		f*=n;
	return f;
}

#define swap(a,b,t) t=a, a=b, b=t
int
main(int argc, char **argv)
{
	unsigned n, f, i, j, x, t;
	int a[N];

	if (argc<2 || !(n=strtol(argv[1], 0, 0)) || n>N) {
		fputs("usage: permut N\n", stderr);
		exit(1);
	}
	f=fact(n);
	for (i=0; i<f; i++) {
		for (j=0; j<n; j++)
			a[j]=j;
		for (x=i, j=0; j<n; x/=n-j, j++) {
			swap(a[j+x%(n-j)], a[j], t);
			printf("%d ", a[j]);
		}
		putchar('\n');
	}
	exit(0);
}
