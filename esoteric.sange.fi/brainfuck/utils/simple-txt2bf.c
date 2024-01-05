From hogsett@csl.sri.com Thu Sep 12 11:49:43 2002
Date: Fri, 23 Aug 2002 21:40:08 -0700
From: Mike Hogsett <hogsett@csl.sri.com>
To: pkalliok@helsinki.fi
Subject: BF Encoder C program


Attached is a BF encoder program.  From ascii input it outputs a bf
program which when run in a bf interpreter will output the original file.

 - Michael Hogsett

P.S.  Some BF interpreters do not handle files over a fixed size.  I
recommend using the perl bf interpreter at :

	  http://www.hut.fi/~mnippula/useless/

#include <stdio.h>
#include <math.h>

/* compile with gcc -lm -o bencode bencode.c */

/*
  FACTOR_TYPE struct and get_closest_factors function
  used from txt2bf.c by Sean Geoghegan

  From txt2bf.c

  *   txt2bf - an ascii text to bf code convertor
  *
  *   (c) 2001 Sean Geoghegan 
  *
  *   This software is available free of charge for distribution,
  *   modification and use (by executing the program) as long as the
  *   following conditions are met: 
  *
  *   1. Every work copied or derived from this software distributed in any
  *      form must come with this license; 
  *   2. The only permitted change to this license is adding one's name
  *      in the authors section when having modified the software. 
  *
  *   THE AUTHORS CANNOT BE HELD RESPONSIBLE FOR ANY
  *   DIRECT OR INDIRECT HARM THIS SOFTWARE MIGHT CAUSE.
  *
  *    
  *   The input file is given as a commandline arg,
  *   the output file is written to file with the 
  *   same name as the inut file but a .bf extenstion.
  *
  *   Author: Sean Geoghegan
  *   Date: 21/12/2001
  
  */

/* Author: Michael Hogsett <hogsett@csl.sri.com> Date: 23/8/2001 */

/* #define DEBUG 1 */

void outbf(char);
void iloop(char);
void dloop(char);

char last;

typedef struct FACTOR_TYPE {
        int x;
        int y;
        int rem;
}FACTOR, *FACTOR_PTR;

FACTOR get_closest_factors(int n){
  FACTOR factor;
  
  factor.x = (int)sqrt(n);
  factor.y = factor.x;
  
  while ( (factor.x * (factor.y + 1)) <= n ) {
    factor.y++;
  }
  
  factor.rem = n - (factor.x * factor.y);
  
#ifdef DEBUG
  printf("Factors for %d are x=%d y=%d rem=%d\n",n,factor.x,factor.y,factor.rem);
#endif
  
  return factor;
}


int main(int argc, char** argv) { 
  char c;
  last = 0;
  while ( (c = getc(stdin)) != EOF ) { 
    outbf(c);
    last = c;
  }
}

void outbf(char c) { 
  char diff = c - last;
  if ( diff > 0 ) { 
    // need to increment value to output byte
    iloop(abs(diff));
  } else if ( diff < 0 ) {
    // need to decrement value to output byte
    dloop(abs(diff));
  }
  fprintf(stdout,".\n");
}

void iloop(char diff) { 
  FACTOR factors = get_closest_factors(diff);
  putc('>',stdout);
  while(factors.x--) {
    putc('+',stdout);
  }
  fprintf(stdout,"[<");
  while(factors.y--) {
    putc('+',stdout);
  }
  fprintf(stdout,">-]<");
  while(factors.rem--) {
    putc('+',stdout);
  }
}

void dloop(char diff) { 
  FACTOR factors = get_closest_factors(diff);
  putc('>',stdout);
  while(factors.x--) {
    putc('+',stdout);
  }
  fprintf(stdout,"[<");
  while(factors.y--) { 
    putc('-',stdout);
  }
  fprintf(stdout,">-]<");
  while(factors.rem--) {
    putc('-',stdout);
  }
}
