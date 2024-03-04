/*% cc -Wall -g -lm -ljpeg -lX11 -o # %
 * earth [-h] [-l LNG] [-m MAP] [-r] [-s] [-w]
 * Shows the earth. The program
 * accepts the following options.
 *
 * -l LNG will center the view on
 *    longitude LNG, use negative
 *    values for W longitudes and
 *    positive values for E
 *    longitudes. Use degrees.
 * -m MAP will use the jpeg file
 *    MAP as planisphere, it must
 *    be a plate carrée projection
 *    for best results.
 * -r will display on the root
 *    window, if not specified a
 *    new X window is created for
 *    rendering. With this option,
 *    no keyboard interaction is
 *    possible.
 * -s do not lock the sun on its
 *    approximate position. If
 *    in interactive mode,
 *    pressing the space bar
 *    will move the sun.
 * -w tries to simulate the milky
 *    way...
 * -h displays a succint and
 *    useless help message.
 *
 * A cool map can be found on the
 * NASA website:
 * http://visibleearth.nasa.gov/view.php?id=57752
 */

/* compile time settings */
#define MAP_FILE    "earth2048.jpg"
#define SHOW_SUN    False
#define EARTH_TILT -0.2
#define AMBIENT     0.1
#define INTERVAL    300


#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/select.h>
#include <X11/XKBlib.h>
#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <jpeglib.h>

Display *d;
int screen;
int xfd;
Window w;
int width, height;
XImage *im;
GC gc;
float slam, sphi, elam;
unsigned char *map;
int mapw, maph;
int sflag, rflag, wflag;


void die(char *);
void dosyn(void);
void draw(void);
unsigned getpixel(float, float, float);
void loadmap(char *);
void putim(void);
void usage(int);
void xconfigure(XConfigureEvent *);
void xinit(void);


void
die(char *m)
{
	fprintf(stderr, "dying, %s\n", m);
	exit(1);
}

void
dosyn(void)
{
	time_t t, tsol;
	struct tm *tm, tmsol;
	int n;

	t = time(0);
	tm = gmtime(&t);
	if (!tm)
		die("cannot get utc time");
	slam = M_PI - M_PI * (tm->tm_hour * 60 + tm->tm_min)/720.;

	/* http://en.wikipedia.org/wiki/Position_of_the_Sun */
	tmsol = (struct tm){
		.tm_mday = 21,
		.tm_mon = 11,
		.tm_year = tm->tm_year
	};
	tsol = mktime(&tmsol);
	n = difftime(t, tsol) / (3600 * 24);
	sphi = 23.44 * M_PI/180. * cos(M_PI/182.*n);
}

int
star(float x, float y)
{
	float z, k, i0, i1;

	if (!wflag)
		return rand() < RAND_MAX / 800;

	y = 0.25 * x + 0.96 * y;
	if (fabs(y/height*2) > 0.3)
		return rand() < RAND_MAX/height;
	if (rand() >= 3*(RAND_MAX/4))
		return 0;
	k = 5.24264;
	i0 = k*(y-1)/height;
	i1 = k*(y+1)/height;
	z = sqrtf(-logf((float)rand()/RAND_MAX));
	z *= cos(2*M_PI*(float)rand()/RAND_MAX);
	return i0 <= z && z <= i1;
}

void
draw(void)
{
	int x, y, r;
	float x2, y2, x2i, r2, l2;
	float s[3];
	int hw, hh;

	if (sflag)
		dosyn();

	hw = width / 2;
	hh = height / 2;
	y2 = hh * hh;
	x2i = hw * hw;

	s[0] = sinf(slam-elam) * cosf(sphi);
	s[1] = sinf(sphi);
	s[2] = cosf(slam-elam) * cosf(sphi);

	r = hh;
	r2 = r * r;
	l2 = 2 * r2 / 3;

	srand(0);

	for (y = -hh; y + hh < height; y++) {
		for (x2 = x2i, x = -hw; x + hw < width; x++) {
			float R2 = x2 + y2;
			float alpha, D, p[3], z, d;
			float lam, phi;

			if (R2 > l2) {
				XPutPixel(im, x+hw, y+hh, 0);
				if (star(x, y))
					XPutPixel(im, x+hw, y+hh, 0xffffff);
				goto next;
			}

			alpha = sqrtf(R2)/(4*r);
			D = r2 - R2 - 2*alpha*r*sqrtf(R2);
			z = r - alpha*sqrtf(R2) - sqrtf(D);
			z /= alpha*alpha + 1;

			/* normalized dot product */
			p[0] = x*(1 + z*alpha/sqrtf(R2 + 16*r2));
			p[1] = y*(1 + z*alpha/sqrtf(R2 + 16*r2));
			p[2] = r - z;
			d = s[0]*p[0] + s[1]*p[1] + s[2]*p[2];
			d /= r;

			if (d < 0)
				d = 0;
			d += AMBIENT;
			if (d > 1)
				d = 1;

			/* latitude & longitude
			 * we tilt latitude a bit to have a
			 * better view */
			lam = asinf(p[0]/hypotf(p[0], p[2]));
			phi = asinf(p[1]/r) + EARTH_TILT;

			XPutPixel(im, x + hw, y + hh, getpixel(d, lam, phi));
		next:
			x2 += 2 * x + 1;
		}
		y2 += 2 * y + 1;
	}
}

unsigned
getpixel(float d, float lam, float phi)
{
	int i, mapx, mapy;

	mapx = (int)(mapw * (M_PI+lam+elam)/(2*M_PI)) % mapw;
	mapy = maph * (M_PI_2+phi)/M_PI;
	i = mapy * 3*mapw + 3*mapx;
#if SHOW_SUN
	if (d>0.99)
		return 0xffff00;
#endif

	return ((int)(d*map[i])<<16) + ((int)(d*map[i+1])<<8) + (int)(d*map[i+2]);
}

void
loadmap(char *file)
{
	FILE *f;
	struct jpeg_decompress_struct j;
	struct jpeg_error_mgr jerr;
	JSAMPARRAY buffer;
	unsigned char *p;
	int rowsz;

	j.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&j);

	f = fopen(file, "r");
	if (!f)
		die("cannot open image file");
	jpeg_stdio_src(&j, f);

	jpeg_read_header(&j, TRUE);
	jpeg_start_decompress(&j);
	printf("loading jpeg (%dx%d, %d components)\n",
		j.output_width, j.output_height, j.output_components);
	if (j.output_components != 3)
		die("jpeg format unsupported");

	mapw = j.output_width;
	maph = j.output_height;
	rowsz = 3*mapw;
	map = malloc(rowsz * maph);
	if (!map)
		die("allocation failed");
	buffer = j.mem->alloc_sarray((void *)&j, JPOOL_IMAGE, rowsz, 1);

	p = map;
	while (j.output_scanline < j.output_height) {
		jpeg_read_scanlines(&j, buffer, 1);
		memcpy(p, buffer[0], rowsz);
		p += rowsz;
	}

	jpeg_finish_decompress(&j);
	jpeg_destroy_decompress(&j);
	fclose(f);
}

void
putim(void)
{
	Pixmap p;

	if (!im)
		return;

	if (rflag) {
		p = XCreatePixmap(d, w, width, height, DefaultDepth(d, screen));
		XPutImage(d, p, gc, im, 0, 0, 0, 0, width, height);
		XSetWindowBackgroundPixmap(d, w, p);
		XFreePixmap(d, p);
		XClearWindow(d, w);
	} else
		XPutImage(d, w, gc, im, 0, 0, 0, 0, width, height);
}

void
usage(int r)
{
	fputs("usage: earth [-h] [-l LNG] [-m MAP] [-r] [-s] [-w]\n", r?stderr:stdout);
	exit(r);
}

void
xconfigure(XConfigureEvent *e)
{
	XImage *i;
	char *b;

	if (width == e->width && height == e->height)
		return;

	i = im; /* avoid race with alrm */
	im = 0;
	width = e->width;
	height = e->height;
	if (i)
		XDestroyImage(i);
	b = malloc(width * height * 4);
	i = XCreateImage(d, DefaultVisual(d, screen), 24, ZPixmap, 0, b, width, height, 32, 0);
	if (!b || !i)
		die("allocation failed");
	im = i;

	draw();
	putim();
}

void
xinit(void)
{
	Window root;
	XWindowAttributes wa;
	XConfigureEvent ce;

	d = XOpenDisplay(0);
	if (!d)
		die("cannot open display");
	xfd = ConnectionNumber(d);
	root = DefaultRootWindow(d);
	screen = DefaultScreen(d);
	if (rflag) {
		w = root;
		XGetWindowAttributes(d, w, &wa);
		ce.type = ConfigureNotify;
		ce.width = wa.width;
		ce.height = wa.height;
		XSelectInput(d, w, StructureNotifyMask);
		XSendEvent(d, w, False, StructureNotifyMask, (XEvent *)&ce);
	} else {
		width = 640;
		height = 480;
		w = XCreateSimpleWindow(d, root, 0, 0, width, height, 0, 0, BlackPixel(d, screen));
		XStoreName(d, w, "earth");
		XSelectInput(d, w, StructureNotifyMask | KeyPressMask | ExposureMask);
		XMapWindow(d, w);
	}
	gc = XCreateGC(d, w, 0, 0);
	XSetForeground(d, gc, 0xffffffff);
	XSetBackground(d, gc, 0x00000000);
}

int
main(int argc, char *argv[])
{
	int o, n;
	char *mapf;
	XEvent e;
	KeySym k;
	fd_set fs;

	mapf = MAP_FILE;
	sflag = 1;
	rflag = 0;
	wflag = 0;
	while ((o = getopt(argc, argv, "hl:m:rsw")) != -1)
		switch (o) {
		case 'l':
			elam = strtof(optarg, 0) * M_PI/180.;
			break;
		case 'm':
			mapf = optarg;
			break;
		case 'r':
			rflag = 1;
			break;
		case 's':
			sflag = 0;
			break;
		case 'w':
			wflag = 1;
			break;
		case 'h':
			usage(0);
		case '?':
		default:
			usage(1);
		}

	xinit();
	loadmap(mapf);
	while (1) {
		if (!XPending(d)) {
			FD_ZERO(&fs);
			FD_SET(xfd, &fs);
			n = select(xfd+1, &fs, 0, 0, &(struct timeval){INTERVAL});
			if (n == -1) {
				if (errno == EINTR)
					continue;
				die("select failed");
			}
			if (n == 0) {
				if (rflag) {
					draw();
					putim();
				}
				continue;
			}
		}
		XNextEvent(d, &e);
		switch (e.type) {
		case ConfigureNotify:
			xconfigure(&e.xconfigure);
			break;
		case Expose:
			putim();
			break;
		case KeyPress:
			k = XkbKeycodeToKeysym(d, e.xkey.keycode, 0, 0);
			if (k == XK_space && !sflag) {
				slam += M_PI/12;
				if (slam > 2*M_PI) slam -= 2*M_PI;
				draw();
				putim();
			}
			if (k == XK_Left || k == XK_Right) {
				if (k == XK_Left)
					elam += M_PI/12;
				else
					elam -= M_PI/12;
				if (elam > 2*M_PI) elam -= 2*M_PI;
				if (elam < 0) elam += 2*M_PI;
				draw();
				putim();
			}
			if (k == XK_q) {
				if (im)
					XDestroyImage(im);
				XFreeGC(d, gc);
				XDestroyWindow(d, w);
				XCloseDisplay(d);
				free(map);
				exit(0);
			}
			break;
		}
	}
}
