/*% cc -Wall -O3 -o # %
 * algsum
 * Compute a polynomial zeroing
 * on the sum of roots of two
 * given monic polynomials.
 * It accepts two lines of
 * input which are the two
 * input polynomials. They
 * must be given in the
 * following form:
 *
 * Polynomial :=
 *     Monomial + ... + Monomial
 * Monomial :=
 *     [-] [{0..9}+] x[{0..9}+]
 *
 * The coefficient of the
 * highest degree monomial must
 * be 1 (not checked).
 *
 * The sample input:
 *     x2 + 1
 *     1x2 + -2 x0
 * can be used to get a
 * polynomial zeroing on
 * 'i + sqrt(2)'.
 */

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct poly Poly;
struct poly {
	int deg;
	int *a;
};

void print(Poly p) {
	int i, j;

	for (j = 1, i = 0; i <= p.deg; i++) {
		if (!p.a[i])
			continue;
		if (i == 0)
			printf("%d", p.a[i]);
		else
			printf(j ? "%d x%d" : " + %d x%d", p.a[i], i);
		j = 0;
	}
	puts("");
}

Poly parse(char *line) {
	Poly res;
	int sign, c, px, a[64] = { 0 };
	char *p, *q;

	res.deg = 0;
	p = strtok(line, "+");

	while (p) {
		sign = 1;
		px = 0;
		c = 1;
		while (*p) {
			p += strspn(p, " \t\n");
			switch (*p) {
			case '-':
				sign = -1;
				p++;
				break;
			case '0'...'9':
				c = strtod(p, &q);
				if (p == q) {
					if (*p == '-')
						c = -1;
					else
						c = 1;
					p++;
				} else
					p = q;
				break;
			case 'x':
				if (!isdigit(p[1]))
					px = 1, p++;
				else
					px = strtod(p+1, &p);
				break;
			case 0:
				break;
			default:
				fputs("syntax error\n", stderr);
				exit(1);
			}
		}
		a[px] += sign*c;
		if (res.deg < px)
			res.deg = px;
		p = strtok(0, "+");
	}

	res.a = calloc(sizeof (int), res.deg+1);
	memcpy(res.a, a, (res.deg+1) * sizeof (int));
	return res;
}

#define Mat(i,j,l) M[((j)*p1.deg + (i)) + deg*(l)]
Poly p1, p2;
int deg, *M, *rows;

void det(int *out, int c) {
	int row, i, m;
	int *buf;

	if (deg == c) {
		out[0] = 1;
		return;
	}

	buf = calloc(sizeof (int), deg-c);

	m = 1;
	for (row = 0; row < deg; row++) {
		if (!rows[row])
			continue;

		if (M[c*deg + row] == 0 && row != c)
			goto next;

		rows[row] = 0;
		det(buf, c+1);
		rows[row] = 1;

		if (row == c)
			for (i = 1; i <= deg-c; i++)
				out[i] -= m*buf[i-1];

		for (i = 0; i < deg-c; i++)
			out[i] += m*M[c*deg + row]*buf[i];

		memset(buf, 0, (deg-c) * sizeof (int));
	next:
		m = -m;
	}

	free(buf);
}

int main() {
	char line[512];
	int *pol, i, j, k, l;

	p1 = parse(fgets(line, 512, stdin));
	p2 = parse(fgets(line, 512, stdin));

	puts("\n--- POLYNOMS");
	print(p1);
	print(p2);

	if (!p1.deg || !p2.deg) {
		fputs("invalid input\n", stderr);
		exit(1);
	}

	deg = p1.deg * p2.deg;
	M = calloc(sizeof (int), deg * deg);
	pol = calloc(sizeof (int), deg+1);

	l = 0;
	for (j = 0; j < p2.deg; j++)
	for (i = 0; i < p1.deg; i++) {
		if (i < p1.deg-1)
			Mat(i+1, j, l) += 1;
		else
			for (k = 0; k < p1.deg; k++)
				Mat(k, j, l) -= p1.a[k];

		if (j < p2.deg-1)
			Mat(i, j+1, l) += 1;
		else
			for (k = 0; k < p2.deg; k++)
				Mat(i, k, l) -= p2.a[k];

		l++;
	}
	
	puts("\n--- MATRIX");
	for (l = 0; l < deg; l++)
	for (i = 0; i < deg; i++) {
		if (i == 0 && l != 0)
			puts("");
		printf("%02d ", M[i + deg*l]);
	}
	puts("");

	puts("\n--- POLYNOM");
	rows = calloc(sizeof (int), deg);
	for (i = 0; i < deg; i++)
		rows[i] = 1;
	det(pol, 0);
	print((Poly){ .deg = deg, .a = pol });

	return 0;
}
