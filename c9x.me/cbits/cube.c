/*% cc % -lm -Wall -std=c99 -g -o #
 * cube [da [db [dc]]]
 * 3D Cube for the Terminal!
 * The three parameters control the
 * fraction of π that will turn the
 * cube every fifth of a second.
 * Defaults are da=40, db=50, dc=60.
 */

float aspect = 2.;        /* font height / font width */
char cols[7] = ";:.*=% "; /* faces color + background */

#define _DEFAULT_SOURCE
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159f

typedef struct Vec Vec;
typedef struct Mat Mat;

struct Vec { float x, y, z; };
struct Mat { Vec col[3]; };

Vec i = { 0, 0, -5 };   /* eye */
Vec s = { 0, 0, -3 };   /* screen */
float sdim = 1.8f;      /* screen dimensions */
Vec p[6] = {            /* cube */
	{  0,  0, -1 }, /* front */
	{  0,  0,  1 }, /* back */
	{ -1,  0,  0 }, /* right */
	{  1,  0,  0 }, /* left */
	{  0, -1,  0 }, /* down */
	{  0,  1,  0 }, /* up */
};
/* Note: since the universe is centered on
 * the cube, the normals are also the face
 * centers.
 */
int face[3][2] = {
	{ 2, 4 },  /* front & back */
	{ 0, 4 },  /* right & left */
	{ 0, 2 },  /* up & down */
};
float ca, sa, cb, sb, cc, sc;
int dbg;

Vec cross(Vec u, Vec v)  { return (Vec){u.y*v.z-u.z*v.y, u.z*v.x-u.x*v.z, u.x*v.y-u.y*v.x}; }
Vec add(Vec u, Vec v)    { return (Vec){u.x+v.x, u.y+v.y, u.z+v.z}; }
Vec mult(float k, Vec v) { return (Vec){v.x*k, v.y*k, v.z*k}; }
Vec diff(Vec u, Vec v)   { return add(mult(-1.f, v), u); }
float dot(Vec u, Vec v)  { return u.x*v.x + u.y*v.y + u.z*v.z; }
float norm2(Vec v)       { return dot(v, v); }

void rotate(Vec *v)
{
#define M(a,b,c) dot((Vec){a, b, c}, *v)
	*v = (Vec){M(1, 0, 0), M(0, ca, -sa), M(0, sa, ca)};
	*v = (Vec){M(cb, 0, sb), M(0, 1, 0), M(-sb, 0, cb)};
	*v = (Vec){M(cc, -sc, 0), M(sc, cc, 0), M(0, 0, 1)};
#undef M
}

int cube(Vec r)
{
	int f;
	Vec x, xc;
	float dt, c0, c1;

	r = mult(1.f/sqrtf(norm2(r)), r);
	for (f=0; f<6; f++) { /* find the face hit by the ray */
		dt = dot(r, p[f]);
		if (dt >= 0)
			/* not facing us */
			continue;
		x = add(i, mult(dot(diff(p[f], i), p[f])/dt, r));
		xc = diff(x, p[f]);
		c0 = norm2(cross(xc, p[face[f/2][0]]));
		c1 = norm2(cross(xc, p[face[f/2][1]]));
		if (fabs(c0) <= 1 && fabs(c1) <= 1)
			break;
	}
	return f;
}

int main(int ac, char *av[])
{
	struct winsize ws;
	Vec r;
	float x, y, da, db, dc;
	float ydim, xdim;
	int w, h, f;

	ioctl(0, TIOCGWINSZ, &ws);
	h = ws.ws_row-1;
	w = ws.ws_col-1;
	if (w > h * aspect) {
		xdim = (sdim * w) / (aspect * h);
		ydim = sdim;
	} else {
		xdim = sdim;
		ydim = (sdim * aspect * h) / w;
	}

	da = 40.; db = 50.; dc = 60.;
	if ((ac>1 && (da = strtof(av[1], 0)) == 0)
	||  (ac>2 && (db = strtof(av[2], 0)) == 0)
	||  (ac>3 && (dc = strtof(av[3], 0)) == 0)) {
		fputs("error: invalid argument\n", stderr);
		exit(1);
	}

	ca = cosf(PI/da); sa = sinf(PI/da);
	cb = cosf(PI/db); sb = sinf(PI/db);
	cc = cosf(PI/dc); sc = sinf(PI/dc);

	/* hide cursor \x1b[?251 */
	printf("\x1b[2J");
	for (;;) {
		printf("\x1b[;H");
		for (f=0; f<6; f++)
			rotate(&p[f]);
		for (y=ydim/2.f; y>-ydim/2.f; y-=ydim/h) {
			for (x=xdim/2.f; x>-xdim/2.f; x-=xdim/w) {
				r = diff(add(s, (Vec){x, y}), i);
				f = cube(r);
				putchar(cols[f]);
			}
			printf("\n");
		}
		usleep(1e6/5);
	}

	return 0;
}
