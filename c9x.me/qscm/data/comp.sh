#!/bin/sh
[ -z "$1" ] && {
	echo 'usage: comp.sh file.qscm'
	exit 1
}

cat << EOF > /tmp/qscm.c
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

typedef intptr_t V;

#define L(n) L_(n, E)
#define A a_(E)
#define B(x,y) (E=C(x,E), B_(y, &E))
#define F(n) C((V)f##n, E)
#define Z1(f) Zn(f, 0)
#define Z(f,a) Zn(f, C(a,0))
#define Z3(f,a,b) Zn(f, C(a,C(b,0)))
#define Z4(f,a,b,c) Zn(f, C(a,C(b,C(c,0))))
#define J return
#define D(x,y) V f##x(V E){J y;}

V C(V a,V d){V*p=malloc(2*sizeof*p);*p=a;p[1]=d;J(V)p;}
V a_(V x){J*(V*)x;}
V d_(V x){J*((V*)x+1);}
V B_(V x,V *e){*e=d_(*e);J x;}
V L_(V n,V e){while(--n)e=d_(e);J a_(e);}
V Zn(V x,V a){V(*f)(V)=(V(*)())a_(x),e=d_(x);for(;a;e=a,a=x)x=d_(a),((V*)a)[1]=e;J f(e);}

D(g,*(char *)A)
D(s,*(char *)L(2)=A)
D(n,(V)malloc(A))
D(c,C(L(2),A))
D(a,a_(A))
D(d,d_(A))
D(i,getchar())
D(o,putchar(A))
#define X(x) (V)&(V[2]){(V)f##x}
V qget=X(g),qset=X(s),qnew=X(n),q=X(c),qcar=X(a),qcdr=X(d),qgetc=X(i),qputc=X(o),
EOF
./comp < $1 |
	tee /tmp/qscm.out \
	>> /tmp/qscm.c
cc -O2 -Wall /tmp/qscm.c
