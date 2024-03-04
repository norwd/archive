/*% clang -Wall -o # %
 * hanoi [-m] [-n N]
 * Solves the Hanoi problem for N
 * disks. If -m is used, the output
 * is intended to be piped in the 'hanoi'
 * test program of the ncurses library.
 * You will see disks move nicely.
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

static bool human = true;

static void
hanoi(char n, char from, char to, char pivot)
{
	if (n == 0)
		return;
	hanoi(n - 1, from, pivot, to);
	if (!human) {
		fflush(stdout);
		usleep(500000);
	}
	printf(human ? "from %d to %d\n" : "%d%d", (int)from, (int)to);
	hanoi(n - 1, pivot, to, from);
} 

int
main(int argc, char ** argv)
{
	char n = 5;
	int c;

	while ((c = getopt(argc, argv, "mn:")) != -1)
		switch (c) {
		case 'm':
			human = false;
			break;
		case 'n':
			n = atoi(optarg);
			break;
		}
	if (human) {
		puts("Welcome to Hanoi.");
		puts("-----------------");
		puts("");
	}
	hanoi(n, 1, 3, 2);
	return 0;
}
