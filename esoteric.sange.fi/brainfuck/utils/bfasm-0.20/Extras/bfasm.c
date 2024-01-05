/*====================================================================
; BFASM -- ASM to BF assembler
; Filename : bfasm.c
; Language : ASM
; Version  : 0.20
; Copyright: (C) 2004 Jeffry Johnston
;
; Please do not make a change to this file without making the
; corresponding change to bfasm.asm (for consistency's sake).
;
; This program is free software; you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation. See the file LICENSE for more details.
;
; Version history:
; 0.20    04 Aug 2004 Fixed bug that occurred when both register
;                     operands were the same
; 0.10    24 Jun 2004 Initial release
;===================================================================*/

#include <stdio.h>
#include <stdlib.h>

/* function headers */
unsigned int inchar();
void outbf();
void outrep();

/* global variables */
unsigned int m[2000];

/*
m[0]    character, name 1
m[1]    mode: 0=comment, 1=nothing, 2=operands, 3=text find open quote, 4=find close quote
m[2]    name 2, instruction
m[3]    name 3, # operator (1 or 2 ops)
m[4]    temp, r_ operator 1 (1 op), r_ operator 2 (2 ops)
m[5]    temp, r_ operator 1 (2 ops)
m[6]    temp
m[7]    temp
m[8]    mp
m[9]    start of array memory
m[10]   org
m[11]   needpre
m[12]   needpost
m[20]   chars
*/

/* main */
int main(void) {
  unsigned int n;
/*
0 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19
a b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t
g ip t0 t1 t2 r1 r2 r3 r4 im t3 t4 t5 t6 t7 0  a  ...
*/
/*
    first
    //  (@G[-]@IP[-])           (G=0:IP=0)
    //  @G+                     G=1
    //  @IP+                    IP=1
    //  [                       DO WHILE IP<>0
    a+b+[

    last
    //    @G[-]@IP[-]             END (G=0:IP=0)
    //  @IP]                    LOOP
    a[-]b[-]]

    pre
    //  @G[@T0+@T1+@G-]         T0=G:T1=G:G=0 (T1=G)
    //  @T0[@G+@T0-]            G=T0:T0=0
    //  @T1[[-]                 IF T1<>0 THEN:T1=0 (IF G<>0 THEN)
    a[c+d+a-]c[a+c-]d[[-]       (i.e. only run this code when not jumping)

    post
    //  @T1]                    END IF
    d]

    //L#: label
    //  (...)                   T2=##
    //  @T0+                    T0=1
    //  @G[@T0-@T1+@G-]         IF G<>0 THEN T0=0:T1=G:G=0
    //  @T1[@G+@T1-]            G=T0:T1=0
    //  @T0[-                   IF T0<>0 THEN:T0=0 (IF G=0 THEN)
    //    @T1+                    T1=1
    //    @IP[@T2-@T0+@IP-]       T2=T2-IP:T0=IP:IP=0
    //    @T0[@IP+@T0-]           IP=T0:T0=0
    //    @T2[                    IF T2<>0 THEN
    //      @T1-                    T1=0
    //    @T2[-]]                 END IF:T2=0
    //    @T1[                    IF T1<>0 THEN (IF T2=IP THEN)
    //      @G+                     G=1
    //    @T1-]                   END IF:T1=0
    //  @T0]@T2[-]              END IF:T0=0:T2=0
    e(+++'s)   c+a[c-d+a-]d[a+d-]c[-d+b[e-c+b-]c[b+c-]e[d-e[-]]d[a+d-]c]e[-]

    //GOTO label
    //  (...)                   IP=#:G=0

    //IF expr THEN GOTO label
    //  @TEMP0[[-]              IF TEMP0<>0 THEN:TEMP0=0
    //  (...)                     IP=##:G=0
    //  @TEMP0]                 END IF

      //V1=V1/V2
      //  @V1[@T3+@V1-]         T3=V1:V1=0
      //  @T3[                  DO WHILE T3<>0

      //    @V2[@T2+@T0+@V2-]     T2=V2:T0=V2:V2=0
      //    @T0[@V2+@T0-]         V2=T0:T0=0

      //    @T2[                  DO WHILE T2<>0

      //      @T0+@T3-              T0=1:T3=T3-1
      //      [@T0[-]@T1+@T3-]      IF T3<>0 THEN T0=0:T1=T3:T3=0
      //      @T1[@T3+@T1-]         T3=T1:T1=0

      //      @T0[                  IF T0<>0 THEN (IF T3=0 THEN)
      //        @T2-[                 T2=T2-1:IF T2<>0 THEN
      //          @V1-                  V1=V1-1
      //        @T2[-]]+              END IF:T2=1
      //      @T0-]                 END IF:T0=0

      //    @T2-]                 T2=T2-1:LOOP
      //    @V1+                  V1=V1+1
      //  @T3]                  LOOP:(T3=0)
      t0=e
      t1=k
      t2=d
      t3=c
      1[c+1-]c[2[d+e+2-]e[2+e-]d[e+c-[e[-]k+c-]k[c+k-]e[d-[1-d[-]]+e-]d-]1+c]

*/

            /*0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36*/
  char * s = "addanddecdiveq_ge_gt_in_incjmpjnzjz_lblle_lt_modmovmulne_negnotor_outpoppshrclstosubswpclrretendstkorgdb_txtraw"
             "a+b+[\0" /* 0 first */
             "b]\0" /* 1 last (end, post, last) */
             "a[c+d+a-]c[a+c-]d[[-]\0" /* 2 pre */
             "d]\0" /* 3 post */
             "2\0" /* 4 immed */
             "2[-]\0" /* 5 immed clear */
             "2[1+e+2-]e[2+e-]\0" /* 6 add */
             "1[e+1-]e[e[-]2[e+d+2-]d[2+d-]e[1-e[-]]]\0" /* and */
             "2-\0" /* dec */
             /* "1[k+1-]2[l+e+2-]e[2+e-]k[->>+<-[>]>[[<+>-]>>>+<]<<<<]p[1+p-]m[-]l[-]\0"*/
             "1[c+1-]c[2[d+e+2-]e[2+e-]d[e+c-[e[-]k+c-]k[c+k-]e[d-[1-d[-]]+e-]d-]1+c]\0"
             /* div */
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
             "1[k+1-]2[l+e+2-]e[2+e-]k[->>+<-[>]>[[<+>-]>>>+<]<<<<]p[-]m[1+m-]l[-]\0" /* mod */
             "1[-]2[1+e+2-]e[2+e-]\0" /* 22 mov */
             "1[d+1-]d[2[1+e+2-]e[2+e-]d-]\0" /* mul */
             "1[d+1-]2[d-e+2-]e[2+e-]d[1+d[-]]\0" /* ne_ */
             "2[e-2-]e[2+e-]\0" /* neg */
             "2-[e-2-]e[2+e-]\0" /* not */
             "1[e+1-]e[1-e[-]]2[e+d+2-]d[2+d-]e[1[-]-e[-]]\0" /* or_ */
             "2.\0" /* out */
             "2[-]q[-]>[>>]<<->[<<<[<<]>+>[>>]>-]<<<[<<]>[2+q-]\0" /* pop */
             "2[e+q+2-]e[2+e-]q>[>>]+<<[<<]>[>[>>]<+<[<<]>-]\0" /*  psh */
             "1[-]2[e+o+*>+<2-]e[2+e-]*>[[>>]+[<<]>>-]+[>>]<[<[<<]>+1+*>[>>]<-]<[<<]>[>[>>]<+<[<<]>-]>[>>]<<[-<<]>\0"  /* rcl */
             /*
             "1[-]2[e+o+*>>+<2-]e[2+e-]*>>[[>>]+[<<]>>-]+[>>]<[<[<<]>+1+*>>[>>]<-]<[<<]>[>[>>]<+<[<<]>-]>[>>]<<[-<<]\0"
             */
             "1[e+*>+<1-]e[1+e-]2[e+*+2-]e[2+e-]*>[[>>]+[<<]>>-]+[>>]<[-]<[<<]>[>[>>]<+<[<<]>-]>[>>]<<[-<<]>\0" /* sto */
             /*
             "1[e+*>>+<1-]e[1+e-]2[e+*>+2-]e[2+e-]*>>[[>>]+[<<]>>-]+[>>]<[-]<[<<]>[>[>>]<+<[<<]>-]>[>>]<<[-<<]\0"
             */
             "2[1-e+2-]e[2+e-]\0" /* sub */
             "1[e+1-]2[1+2-]e[2+e-]\0" /* swp */
             "2[-]\0" /* clr */
             "a[-]b[-]q[-]>[>>]<<->[<<<[<<]>+>[>>]>-]<<<[<<]>[b+q-]\0" /* ret */
             "a[-]b[-]\0"; /* end */
  for (n = 0; n < 1900; n++) { m[n + 20] = s[n]; }

  m[6] = 0;
  m[8] = 0;
  /* m[9] = 17; */ m[9] = 18;
  /* m[10] = m[9] + 3; */ m[10] = m[9] + 2;
  outbf(); /* first */
  m[11] = 1;
  m[12] = 0;

  m[1] = 1;
  Laa:;
    m[0] = inchar();

    Laj:;
    /* putchar(m[0]); */
    /* printf("%i ", m[1]); */
    if (m[0] != '\0') goto Lam;
      if (m[1] == 2) goto Lai;
      goto Lab;
    Lam:;
    if (m[0] != '\n' && m[0] != '\v' && m[0] != '\f' && m[0] != '\r') goto Lad;
      if(m[1] == 2) goto Lai;
      m[1] = 1;
      goto Laa;
    Lad:;
    if (m[1] == 4) {
      if (m[0] == '\"') {
        m[1] = 1;
        goto Laa;
      }
      m[2] = 34;
      m[3] = m[0];
      goto Lai;
    }
    if (m[0] == ' ' || m[0] == '\t' || m[1] == 0) goto Laa;
    if (m[1] != 3) goto Lay; /* txt */
      if (m[0] != '\"') goto Laz; /* syntax error, open quote expected */
      m[1] = 4;
      goto Laa;
    Lay:;
    if (m[0] != ';') goto Lac; /* comment */
      /* putchar(';'); */
      if(m[1] == 2) goto Lai;
      m[1] = 0;
      goto Laa;
    Lac:;
    if (m[1] != 1) goto Lae; /* get 3 letter instruction */
      m[2] = inchar();
      /* putchar(m[2]); */
      m[3] = inchar();
      /* putchar(m[3]); */
      m[4] = 0;
      Laf:;
        m[5] = m[4] + 20;
        m[6] = m[m[5]];
        if (m[0] != m[6]) goto Lag;
        m[5]++;
        m[6] = m[m[5]];
        if (m[2] != m[6]) goto Lag;
        m[5]++;
        m[6] = m[m[5]];
        if (m[3] == m[6]) goto Lah;
        Lag:;
        m[4]++;
        m[4]++;
        m[4]++;
        if (m[4] == 111) goto Laz; /* not found, quit */
      goto Laf;
      Lah:; /* found */
      m[1] = 2;
      m[2] = m[4] / 3;
      m[3] = 0;
      m[4] = 0;
      m[5] = 0;
      /* printf("%i ", m[2]); */
      goto Laa;
    Lae:; /* find operands */
    if (m[2] != 35) goto Lax; /* txt command */
      m[1] = 3;
      goto Laj;
    Lax:;
    if (m[0] != 'r') goto Lak; /* r_ operand */
      m[0] = inchar();
      m[0] = m[0] - '1';
      if (m[0] > 3) goto Laz; /* not a number, quit */
      m[4] = m[0] + 'f';
      goto Laa;
    Lak:;
    if (m[0] != ',') goto Lan; /* , */
      m[5] = m[4];
      m[4] = 0;
      goto Laa;
    Lan:;
    if (m[0] != '.') goto Lal; /* .char */
      m[3] = inchar();
      goto Laa;
    Lal:; /* number */
    m[0] = m[0] - '0';
    if (m[0] > 9) goto Laz; /* not a number, quit */
    m[3] = m[3] * 10;
    m[3] = m[3] + m[0];
  goto Laa;

  /* operands complete, process instruction */
  Lai:;
    /*
    printf("\ninst: %i (%c%c%c) op3: %u op4: %i op5: %i\n", m[2], m[3*m[2]+20], m[3*m[2]+21], m[3*m[2]+22], m[3], m[4], m[5]);
    */
    if (m[4] && m[4] == m[5]) { /* 0.20 example: r1,r1 */
      m[6] = 22;                /* 0.20 mov j,f:r1 */
      m[5] = 'j';
      outbf();
      m[5] = m[4];              /* 0.20 regs: (5) f:r1, (4) j */
      m[4] = 'j';
      /*
      printf("\ninst: %i (%c%c%c) op3: %u op4: %i op5: %i\n", m[2], m[3*m[2]+20], m[3*m[2]+21], m[3*m[2]+22], m[3], m[4], m[5]);
      */
    }
    if (m[11] == 1 && m[2] != 12) {
      m[6] = 2;
      outbf(); /* pre */
      m[11] = 0;
    }
    switch (m[2]) {
    case 0: /* add */
      if (m[4] == 0) {
        m[6] = 4;
        m[4] = m[5];
        outbf();
        m[6] = '+';
        outrep();
        goto Lap;
      }
      goto Lao;
    case 9: /* jmp */
      m[11] = 1;
      m[12] = 1;
      goto Lao;
    case 10: /* jnz */
      m[11] = 1;
      m[12] = 1;
      goto Lao;
    case 11: /* jz_ */
      m[11] = 1;
      m[12] = 1;
      goto Lao;
    case 12: /* lbl */
      if (m[11] == 0) {
        m[6] = 3;
        outbf(); /* post */
      }
      m[11] = 1;
      m[6] = 4;
      m[4] = 'e';
      outbf();
      m[6] = '+';
      outrep();
      m[6] = 18;
      outbf();
      goto Lap;
    case 16: /* mov */
      if (m[4] == 0) {
        m[6] = 5;
        m[4] = m[5];
        outbf();
        m[6] = '+';
        outrep();
        goto Lap;
      }
      goto Lao;
    case 27: /* sub */
      if (m[4] == 0) {
        m[6] = 4;
        m[4] = m[5];
        outbf();
        m[6] = '-';
        outrep();
        goto Lap;
      }
      goto Lao;
    case 30: /* ret */
      m[11] = 1;
      m[12] = 1;
      goto Lao;
    case 31: /* end */
      m[11] = 1;
      m[12] = 1;
      goto Lao;
    case 32: /* stk */
      /* m[9] = m[3] * 2 + 17; */ m[9] = m[3] * 2 + 18;
      goto Lap;
    case 33: /* org */
      /* m[10] = m[3] * 2 + m[9] + 3; */ m[10] = m[3] * 2 + m[9] + 2;
      goto Lap;
    case 34: /* db_ */
      m[6] = 4;
      m[4] = '^';
      outbf();
      m[6] = '+';
      outrep();
      m[10] = m[10] + 2;
      if (m[1] == 4) goto Laa;
      goto Lap;
    case 36: /* raw */
      putchar(m[3]);
      goto Lap;
    }
    Lao:;
    if (m[4] == 0) {
      m[6] = 4; /* immed */
      m[4] = 'j';
      outbf();
      m[6] = '+';
      outrep();
      m[3]++;
    }
    m[6] = m[2] + 6;
    outbf();
    if (m[3] == 0) goto Lap;
      m[6] = 5; /* immed clear */
      outbf();
    Lap:;
    m[1] = 1;
    /* putchar('\n'); */
    if (m[12] == 1) {
      m[6] = 3;
      outbf(); /* post */
      m[12] = 0;
    }
  goto Laj;

  /* done */
  Laz:;
  putchar('#');
  return 0;

  Lab:;
  if (m[11] == 0 || m[12] == 1) {
    m[6] = 3;
    outbf(); /* post */
  }
  m[6] = 2;
  outbf(); /* pre */
  m[6] = 37;
  outbf(); /* end */
  m[6] = 3;
  outbf(); /* post */
  m[6] = 1;
  outbf(); /* last */
  return 0;
}

/* outrep */
void outrep() {
  while (m[3]) {
    putchar(m[6]);
    m[3]--;
  }
}

/* outbf */
void outbf() {
  unsigned int r1, r4;
  m[7] = 131;
  r4 = 0;

  o1:;
    if (r4 >= m[6]) goto o2;
    o3:;
      r1 = m[m[7]];
      m[7]++;
    if (r1 != '\0') goto o3;
    r4++;
  goto o1;

  /*
  o1:;
  if (r4 >= m[6]) goto o2;
    r1 = m[m[7]];
    if (r1 != '\0') goto o3;
      r4++;
    o3:;
    m[7]++;
  goto o1;
  */

  o2:;
    r1 = m[m[7]];
    if (r1 == '\0') goto o4;
    if (r1 != '1') goto o5;
      r1 = m[5];
    o5:;
    if (r1 != '2') goto o6;
      r1 = m[4];
    o6:;
    if (r1 != '*') goto o7;
      r1 = m[9];
      goto o11;
    o7:;
    if (r1 != '^') goto o8;
      r1 = m[10];
      goto o11;
    o8:;
    if (r1 < 'a') goto o9;
    if (r1 > 'z') goto o9;
      r1 = r1 - 'a';
      o11:;
      if (r1 < m[8]) goto o12;
        r4 = 0;
        m[15] = r1 - m[8];
        o14:;
          if (m[15] <= r4) goto o13;
          putchar('>');
          r4++;
        goto o14;
      o12:;
        r4 = 0;
        m[15] = m[8] - r1;
        o16:;
          if (m[15] <= r4) goto o13;
          putchar('<');
          r4++;
        goto o16;
      o13:;
      m[8] = r1;
    goto o10;
    o9:;
      putchar(r1);
    o10:;
    m[7]++;
  goto o2;
  o4:;
}

/* inchar */
unsigned int inchar() {
  int c = getchar();
  if (c <= 0)
    c = 0;
  return c;
}
