/*%cc -Wall -g -lm -lX11 -o # %
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

/* Graphical settings. */
#define DOTRADIUS 5
#define DOTCOLOR "blue"
#define LINECOLOR "black"
#define LINESTEPS 100

static void xexpose(XEvent *);
static void xconfigure(XEvent *);
static void xbutton(XEvent *);
static void xkey(XEvent *);

static void (*xhandler[LASTEvent])(XEvent *) = {
	[Expose] = xexpose,
	[ConfigureNotify] = xconfigure,
	[ButtonPress] = xbutton,
	[KeyPress] = xkey,
};

static struct {
	Display *dsp;
	Window  win;
	GC      pgc, lgc;
	int     scr;
	int     w, h;
} xc;

#define MAXPTS 32
#define D 2

static struct {
	float    a[MAXPTS][D];
	unsigned i;
} pts;

#include "spline.c"


static void
die(const char *m)
{
	fprintf(stderr, "error: %s.\n", m);
	exit(1);
}

static void
draw(void)
{
	static const char helpm[]=
		"Left button: Add a point | Q: Quit.";
	struct Spline *s;
	unsigned i;
	float t, tmax, dt;
	float *p, old[D];

	XClearWindow(xc.dsp, xc.win);
	XDrawString(xc.dsp, (Drawable)xc.win, xc.lgc, 0, 10, helpm, sizeof helpm-1);

	for (i=0; i<pts.i; i++) {
		XFillArc(xc.dsp, (Drawable)xc.win, xc.pgc,
		         pts.a[i][0]*xc.w-DOTRADIUS, pts.a[i][1]*xc.h-DOTRADIUS,
		         DOTRADIUS*2, DOTRADIUS*2, 0, 360*64);
	}
	if (pts.i<2)
		goto done;

	s=spnew(pts.a, pts.i);
	spinterp(s, FiniteDiff, 0);
	sptbounds(s, &t, &tmax);
	dt=(tmax-t)/LINESTEPS;
	p=spget(s, t);
	memcpy(old, p, sizeof old);
	for (t=dt; t<tmax; t+=dt) {
		p=spget(s, t);
		XDrawLine(xc.dsp, (Drawable)xc.win, xc.lgc,
		          old[0]*xc.w, old[1]*xc.h, p[0]*xc.w, p[1]*xc.h);
		memcpy(old, p, sizeof old);
	}
	free(s);

done:
	XFlush(xc.dsp);
}

static void
xexpose(XEvent *ev)
{
	draw();
}

static void
xbutton(XEvent *ev)
{
	if (ev->type!=ButtonPress || pts.i>=MAXPTS)
		return;
	pts.a[pts.i][0]=(float)ev->xbutton.x/xc.w;
	pts.a[pts.i][1]=(float)ev->xbutton.y/xc.h;
#if 0
	fprintf(stderr, "%s: New point at (%g, %g).\n",
	        __func__, pts.a[pts.i][0], pts.a[pts.i][1]);
#endif
	pts.i++;
	draw();
}

static void
xkey(XEvent *ev)
{
	char str[8];
	int n;

	if (ev->type!=KeyPress)
		return;

	n=XLookupString(&ev->xkey, str, sizeof str, 0, 0);
	if (n) {
		switch (str[0]) {
		case 'q':
		case 'Q':
			XFreeGC(xc.dsp, xc.lgc);
			XFreeGC(xc.dsp, xc.pgc);
			XDestroyWindow(xc.dsp, xc.win);
			XCloseDisplay(xc.dsp);
			exit(0);
		}
	}
}

static void
xconfigure(XEvent *ev)
{
	xc.w=ev->xconfigure.width;
	xc.h=ev->xconfigure.height;
#if 0
	fprintf(stderr, "%s: New size (%d x %d).\n", __func__, xc.w, xc.h);
#endif
	return;
}

static unsigned long
getcolor(const char *c)
{
	XColor col;

	if (!XAllocNamedColor(xc.dsp, DefaultColormap(xc.dsp, xc.scr), c, &col, &col))
		die("Cannot allocate color");
	return col.pixel;
}

static void
xinit(void)
{
	XGCValues gcv;

	xc.dsp=XOpenDisplay("");
	if (xc.dsp==0)
		die("Cannot open display.");
	xc.scr=DefaultScreen(xc.dsp);
	xc.w=100;
	xc.h=100;
	xc.win=XCreateSimpleWindow(xc.dsp, RootWindow(xc.dsp, xc.scr), 0, 0, xc.w, xc.h,
	                           0, BlackPixel(xc.dsp, xc.scr), WhitePixel(xc.dsp, xc.scr));
	XSelectInput(xc.dsp, xc.win, StructureNotifyMask|ExposureMask|ButtonPressMask|KeyPressMask);

	gcv.foreground=getcolor(DOTCOLOR);
	gcv.background=WhitePixel(xc.dsp, xc.scr);
	xc.pgc=XCreateGC(xc.dsp, (Drawable)xc.win, GCForeground|GCBackground, &gcv);
	gcv.foreground=getcolor(LINECOLOR);
	gcv.font=XLoadFont(xc.dsp, "fixed");
	xc.lgc=XCreateGC(xc.dsp, (Drawable)xc.win, GCForeground|GCBackground|GCFont, &gcv);
	XMapWindow(xc.dsp, xc.win);
}

int
main(void)
{
	xinit();
	while (1) {
		XEvent ev;

		XNextEvent(xc.dsp, &ev);
		if (xhandler[ev.type])
			xhandler[ev.type](&ev);
	}
}
