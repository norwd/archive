/*
**
** index.c
**
** Christopher Osburn 2008
**
** Determine the calculation index for a specified number base
**
** Supplemental to
** Some Notes on the History and Desirability of the Use of Alternate
** Number Bases in Arithmetic
**
** The Duodecimal Bulletin
** Volume Four Dozen Ten, Number One
** Whole Number Nine Dozen Eight (2009)
**
** usage:  index [base]
**
** compile:  cc -o index index.c -lm
**
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int regnum(int);
int * sieve(int);
int expmult(int *, int *);
int numcmp(const void *, const void *);
int primecount(int);
int squarecount(int);

int main(int ac, char * av[])
{
  int base;
  float R, P, S;
  int r, p, s;
  float I;

  if (ac == 2) {
    base = atoi(av[1]);

    printf("\nNUMBER BASE CALCULATION INDEX\nFOR BASE: %d\n\n", base);

    printf("REGULAR NUMBERS:\n");
    r = regnum(base);
    R = (float) r / (base - 2);
    printf("\n   COUNT: %d OF %d POSSIBLE\n", r, base - 2);
    printf("   REGULARITY INDEX..............................R = %5.3f\n\n", R);

    printf("LEAST SIGNIFICANT PLACE - PRIME NUMBERS:\n");
    p = primecount(base);
    P = (float) p / floor (base / 2);
    printf("\n   COUNT: %d OF %d POSSIBLE (ODD NUMBERS)\n", p, base / 2);
    printf("   PRIME NUMBER INDEX............................P = %5.3f\n\n", P);

    printf("LEAST SIGNIFICANT PLACE - SQUARE NUMBERS:\n");
    s = squarecount(base);
    S = (float) s / base;
    printf("\n   COUNT: %d OF %d POSSIBLE\n", s, base);
    printf("   SQUARE NUMBER INDEX...........................S = %5.3f\n\n", S);

    I = (R * log((double) base)) / (P * S * base);
    printf("\nCALCULATION INDEX................................I = %5.3f\n\n", I);

  } else {
    fprintf(stderr, "usage: %s integer\n", av[0]);
  }
}


int regnum(int base)
{
  int *primes, *primeptr;
  int primelist[10]; // we really won't need more than this;
  int exponents[10]; // an exponent for each prime
  int primecount;

  int *reglist, regptr;
  int regcount = 0;

  int i, j, place, num;

  reglist = malloc(base * sizeof(int));
  regptr = 0;

    // first we need a list of primes < base
  primes = sieve(base);

    // then we need to see which of these primes
    // divide the base
  i = 0;
  for (primeptr = primes; *primeptr != 0; primeptr++) {
    if (base % *primeptr == 0) {
      primelist[i] = *primeptr;
      exponents[i] = 0;  // probably already is...
      i++;
    }
  }
  primelist[i] = 0;
  primecount = i;

  exponents[0]++;
  for (;;) {
    if ((num = expmult(primelist, exponents)) < base) {
      regcount++;
      exponents[0]++;
      reglist[regptr++] = num;
    } else {
      place = 0;
      while (expmult(primelist, exponents) >= base) {
        exponents[place] = 0;
        exponents[place + 1]++;
	place++;
	if (place >= primecount) {
	  qsort(reglist, regptr, sizeof(int), numcmp);
	  printf ("   ");
	  for (i = 0; i < regptr; i++) {
	    printf("%4d ", reglist[i]);
	    if (i % 10 == 9) printf("\n   ");
	  }
	  return regcount;
	}
      }
    }
  }
  return 0; // error!
}


int* sieve(int limit)
{
  static int *primelist;
  int primecount = 0;
  int *primetable;
  int sqrlimit;
  int i, j;

  sqrlimit = (int) sqrt(limit);
  primetable = malloc((limit + 1) * sizeof(int));

  for (j = 2; j <= sqrlimit; j++) {
    if (primetable[j] == 1)  // if j is composite
      continue;              //   skip it.
    for (i = j + j; i <= limit; i += j) {
      primetable[i] = 1;
    }
  }

  for (j = 2; j <= limit; j++) 
    if (primetable[j] == 0)
      primecount++;

  primelist = malloc((primecount + 1) * sizeof(int));

  j = 0;
  for (i = 2; i <= limit; i++) {
    if (primetable[i] == 0) {
      primelist[j] = i;
      j++;
      if (j > primecount) {
        fprintf(stderr, "check allocs in sieve!\n");
        exit(17);
      }
    }
  }

  primelist[primecount] = 0; // sentinel
  free((void *) primetable);

  return primelist;
}


int expmult(int *primes, int *exponents)
{
  int i, j;
  int product = 1;

  for (i = 0; primes[i] != 0; i++)
    for (j = 0; j < exponents[i]; j++)
      product *= primes[i];

  return product;
}


int numcmp(const void *a, const void *b)
{
  int *aa, *bb;

  aa = (int *) a;
  bb = (int *) b;

  if (*aa < *bb) return -1;
  if (*aa > *bb) return 1;
  return 0;
}


int primecount(int base)
{
  int *primes, *p;
  int *test;
  int i, total = 0;

  test = (int *) malloc(base * sizeof(int));
  primes = sieve(2 * base * base);

  for (i = 0; i < base; i++)
    test[i] = 0;

  for (p = primes; *p; p++)
    test[*p % base]++;

  printf("   ");
  for (i = 0; i < base; i++) {
    if (test[i] > 1) {
      printf("%4d ", i);
      total++;
      if (total % 10 == 0)
        printf("\n   ");
    }
  }

  free(test);
  free(primes);

  return total;
}


int squarecount(int base)
{
  int i, total = 0;
  int *test;

  test = (int *) malloc(base * sizeof(int));

  for (i = 0; i < base; i++)
    test[i] = 0;

  for (i = 0; i < base; i++)
    test[(i * i) % base]++;

  printf("   ");
  for (i = 0; i < base; i++) {
    if (test[i] > 0) {
      printf("%4d ", i);
      total++;
      if (total % 10 == 0)
        printf("\n   ");
    }
  }
  free (test);
 
  return total;
}
