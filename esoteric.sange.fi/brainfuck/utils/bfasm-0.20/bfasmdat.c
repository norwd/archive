/*====================================================================
' BFASMDAT -- Creates data lists for bfasm.asm
' Filename : bfasmdat.c
' Language : ANSI C 1989
' Version  : 0.10
' Copyright: (C) 2004 Jeffry Johnston
'
' This program is free software; you can redistribute it and/or modify
' it under the terms of the GNU General Public License as published by
' the Free Software Foundation. See the file LICENSE for more details.
'
' Usage: bfasmdat > bfasm.dat
'
' Version history:
' 0.10    24 Jun 2004 Initial release
====================================================================*/

#include <stdio.h>
#include <stdlib.h>

#define START 171

int main(void) {
  unsigned int p;
  char * s =
  "a+b+[\0" /* 0 first */
  "b]\0" /* 1 last (end, post, last) */
  "a[c+d+a-]c[a+c-]d[[-]\0" /* 2 pre */
  "d]\0" /* 3 post */
  "2\0" /* 4 immed */
  "2[-]\0" /* 5 immed clear */
  "2[1+e+2-]e[2+e-]\0" /* 6 add */
  "1[e+1-]e[e[-]2[e+d+2-]d[2+d-]e[1-e[-]]]\0" /* and */
  "2-\0" /* dec */
  "1[c+1-]c[2[d+e+2-]e[2+e-]d[e+c-[e[-]k+c-]k[c+k-]e[d-[1-d[-]]+e-]d-]1+c]\0" /* div */
  "1[d+1-]+2[d-c+2-]c[2+c-]d[1-d[-]]\0" /* eq_ */
  "1[d+1-]+2[c+k+e+2-]e[2+e-]k[d[l+e+d-]e[d+e-]+l[c-d-e-l[-]]e[k[-]+e-]k-]c[1-c[-]]d[-]\0" /* ge_ */
  "1[d+1-]2[c+k+e+2-]e[2+e-]k[d[l+e+d-]e[d+e-]+l[c-d-e-l[-]]e[k[-]+e-]k-]d[1+d[-]]c[-]\0" /* gt_ */
  "2,\0" /* in_ */
  "2+\0" /* inc */
  "a[-]b[-]2[b+c+2-]c[2+c-]\0" /* jmp addr */
  "1[c+d+1-]c[1+c-]d[a[-]b[-]2[b+c+2-]c[2+c-]d[-]]\0" /* jnz val, addr */
  "d+1[d[-]c+1-]c[1+c-]d[a[-]b[-]2[b+c+2-]c[2+c-]d[-]]\0" /* jz_ val, addr */
  "c+a[c-d+a-]d[a+d-]c[-d+b[e-c+b-]c[b+c-]e[d-e[-]]d[a+d-]c]e[-]\0" /* lbl */
  "1[d+1-]+2[c+k+e+2-]e[2+e-]k[d[l+e+d-]e[d+e-]+l[c-d-e-l[-]]e[k[-]+e-]k-]d[1-d[-]]c[-]\0" /* le_ */
  "1[d+1-]2[c+k+e+2-]e[2+e-]k[d[l+e+d-]e[d+e-]+l[c-d-e-l[-]]e[k[-]+e-]k-]c[1+c[-]]d[-]\0" /* lt_ */
  "1[k+1-]2[l+e+2-]e[2+e-]k[->>+<-[>]>[[<+>-]>>>+<]<<<<]p[-]m[1+m-]l[-]\0" /* mod (BUG!) */
  "1[-]2[1+e+2-]e[2+e-]\0" /* mov */
  "1[d+1-]d[2[1+e+2-]e[2+e-]d-]\0" /* mul */
  "1[d+1-]2[d-e+2-]e[2+e-]d[1+d[-]]\0" /* ne_ */
  "2[e-2-]e[2+e-]\0" /* neg */
  "2-[e-2-]e[2+e-]\0" /* not */
  "1[e+1-]e[1-e[-]]2[e+d+2-]d[2+d-]e[1[-]-e[-]]\0" /* or_ */
  "2.\0" /* out */
  "2[-]q[-]>[>>]<<->[<<<[<<]>+>[>>]>-]<<<[<<]>[2+q-]\0" /* pop */
  "2[e+q+2-]e[2+e-]q>[>>]+<<[<<]>[>[>>]<+<[<<]>-]\0" /*  psh */
  "1[-]2[e+o+*>+<2-]e[2+e-]*>[[>>]+[<<]>>-]+[>>]<[<[<<]>+1+*>[>>]<-]<[<<]>[>[>>]<+<[<<]>-]>[>>]<<[-<<]>\0"  /* rcl */
  "1[e+*>+<1-]e[1+e-]2[e+*+2-]e[2+e-]*>[[>>]+[<<]>>-]+[>>]<[-]<[<<]>[>[>>]<+<[<<]>-]>[>>]<<[-<<]>\0" /* sto */
  "2[1-e+2-]e[2+e-]\0" /* sub */
  "1[e+1-]2[1+2-]e[2+e-]\0" /* swp */
  "2[-]\0" /* clr */
  "a[-]b[-]q[-]>[>>]<<->[<<<[<<]>+>[>>]>-]<<<[<<]>[b+q-]\0" /* ret */
  "a[-]b[-]\0" /* end */
  "@";

  for (p = 0; s[p] != '@'; p++)  {
    printf("db_     %i\n", p + START);
    for (; s[p] != '\0'; p++);
  }
  printf("\n;**********************\n\n");
  for (p = 0; s[p] != '@'; p++)  {
    printf("txt     \"%s\"\ndb_     0\n", s + p);
    for (; s[p] != '\0'; p++);
  }
  return EXIT_SUCCESS;
}
