/*% cc -o # %
 * hilbert N
 * Compute a PostScript rendering
 * of a Hilbert curve.
 * The size of the rendered curve
 * is 2^N, what comes on the
 * standard output is a valid
 * PostScript file.
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

enum D {
	Up,
	Right,
	Down,
	Left,
};

enum R {
	Clockwise,
	CounterClockwise,
};

struct P {
	unsigned x, y;
};

unsigned size;

struct P to(enum D dir, struct P p) {
	switch (dir) {
	case Up:    return (struct P){ .x = p.x, .y = p.y + 1 };
	case Right: return (struct P){ .x = p.x + 1, .y = p.y };
	case Down:  return (struct P){ .x = p.x, .y = p.y - 1 };
	case Left:  return (struct P){ .x = p.x - 1, .y = p.y };
	}
}

struct P step(enum D dir, struct P p) {
	p = to(dir, p);

	/* 8 inches by 8 inches square */
	printf("%d %d lineto\n",
		18  + (p.x*576)/(size-1),
		108 + (p.y*576)/(size-1));
	return p;
}

enum D turn(enum R rot, enum D dir) {
	switch (rot) {
	case Clockwise:
		return (dir+1) % 4;
	case CounterClockwise:
		return (dir+3) % 4;
	}
}

struct P h(int n, struct P p, enum D dir, enum R rot) {
	if (n == 0)
		return p;

	p = h(n-1, p, turn(rot, dir), 1-rot);
	p = step(dir, p);
	p = h(n-1, p, dir, rot);
	p = step(turn(rot, dir), p);
	p = h(n-1, p, dir, rot);
	p = step(turn(rot, turn(rot, dir)), p);
	p = h(n-1, p, turn(1-rot, dir), 1-rot);
	return p;
}

int main(int ac, char *av[]) {
	int n;

	if (ac<2) {
		puts("usage: hilbert N");
		exit(1);
	}

	n = atoi(av[1]);
	assert(n < 31);
	assert(n >= 0);

	size = 1 << n;

	printf("%%!PS\n\n");
	printf("18 108 moveto\n");
	h(n, (struct P) { 0, 0 }, Up, Clockwise);
	printf("stroke\n");
	printf("showpage\n");

	return 0;
}
