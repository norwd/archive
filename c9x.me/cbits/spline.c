/* spline.c
 * An implementation of
 * cubic Hermite splines.
 *
 * Use spnew to create a new
 * curve interpolating the given
 * set of points, then smooth it
 * using spinterp and retrieve
 * points of the curve using
 * spget.
 */
#define _XOPEN_SOURCE 600
#include <math.h>
#include <stdlib.h>

#define MAXPOINTS 128

struct Spline {
	float    ps[MAXPOINTS][D];
	float    ms[MAXPOINTS][D];
	float    ts[MAXPOINTS];
	unsigned n;
};

#if 0
static const float O[D]; /* The origin. */
#endif

static inline float
dst2(float *a, float *b)
{
	float    d2;
	unsigned d;

	d2=0;
	for (d=0; d<D; d++)
		d2+=(a[d]-b[d])*(a[d]-b[d]);
	return d2;
}

static inline float
dst(float *a, float *b)
{
	return sqrtf(dst2(a, b));
}

struct Spline *
spnew(float (*a)[D], unsigned n)
{
	struct Spline *s;
	unsigned      d;
	float         t;

	s=malloc(sizeof *s);
	if (!s)
		return 0;
	s->n=n;
	/* Retreive points' coordinates.
	 */
	while (n--)
		for (d=0; d<D; d++)
			s->ps[n][d]=a[n][d];
	/* Set timing information based
	 * on the square of the distance
	 * separing two consecutive points.
	 */
	t=0;
	for (n=0; n<s->n-1; n++) {
		float dt;

		dt=dst(s->ps[n], s->ps[n+1]);
		if (!dt) {
			free(s);
			return 0;
		}
		s->ts[n]=t;
		t+=dt;
	}
	s->ts[n]=t;
	return s;
}

void
sptbounds(struct Spline *s, float *min, float *max)
{
	if (s->n==0) {
		*min=*max=0;
		return;
	}
	*min=s->ts[0];
	*max=s->ts[s->n-1];
}

enum SplineType {
	CatmullRom, /* Catmull-Rom spline, no parameter needed.            */
	Cardinal,   /* Cardinal spline, tension must be given (in [0, 1]). */
	FiniteDiff, /* Finite differences method, no parameter.            */
};

void
spinterp(struct Spline *s, enum SplineType ty, float p)
{
	unsigned i, d;
	float    dt;

	for (d=0; d<D; d++)
		s->ms[0][d]=s->ms[s->n-1][d]=0;
	switch (ty) {
	case CatmullRom:
		p=0;
	case Cardinal:
		if (!s->n)
			return;
		p=1-p;
		for (i=1; i<s->n-1; i++) {
			dt=s->ts[i+1]-s->ts[i-1];
			for (d=0; d<D; d++) {
				s->ms[i][d]=s->ps[i+1][d]-s->ps[i-1][d];
				s->ms[i][d]*=p/dt;
			}
		}
		break;
	case FiniteDiff:
		for (i=1; i<s->n-1; i++) {
			dt=2*(s->ts[i]-s->ts[i-1]);
			for (d=0; d<D; d++)
				s->ms[i][d]=(s->ps[i][d]-s->ps[i-1][d])/dt;
			dt=2*(s->ts[i+1]-s->ts[i]);
			for (d=0; d<D; d++)
				s->ms[i][d]+=(s->ps[i+1][d]-s->ps[i][d])/dt;
		}
		break;
	}
}

float *
spget(struct Spline *s, float t)
{
	static float p[D];
	unsigned     beg, end;
	unsigned     d;
	float        x, dt;

	if (s->n==0 || t>s->ts[s->n-1] || t<s->ts[0])
		return 0;
	beg=0;
	end=s->n-1;

	/* Find the correct interval using
	 * a binary search.
	 */
	while (end-beg>1) {
		unsigned mid=(beg+end)/2;
		if (t<s->ts[mid]) {
			end=mid;
		} else {
			beg=mid;
		}
	}
	dt=s->ts[beg+1]-s->ts[beg];
	x=(t-s->ts[beg])/dt;

	/* Compute the cspline point.
	 */
	for (d=0; d<D; d++) {
		p[d] =s->ps[beg][d]*(1 + x*x*(2*x - 3));
		p[d]+=s->ms[beg][d]*dt*x*(1 + x*(x - 2));
		p[d]+=s->ps[beg+1][d]*x*x*(-2*x + 3);
		p[d]+=s->ms[beg+1][d]*dt*x*x*(x - 1);
	}

	return p;
}
