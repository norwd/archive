#include <math.h>
#define d(a, e) for(int a=0;a<e;a++)
char*w="	{k/;	y{ q ; }	c {	@;	={ 	S}	c}	W;;	{4}	k |; w{	+9;{;	8; 9{	S;	/}	y{ K}	{;}	l{	{ ~{ ;	V}k}g< t{	E	v;M{ B}y}	<{7;/;	Y} t}kp; Y} $Ha{e} w};} R} /{>}a	;} ;	`	$W-}	D}B; e;f;*;	~;A;s O{	o;>{1; m{ `} R}]{ T} v}={ I} ; }a?&; A}$;W;R{u} `; j}W;s{e}	A;[	R;	X  P; 4 ,F;({<8{#;%}@J{)}	}o^*{u/{'}]{	*}	}	;{ r}	f	/;}e} }w{ ${{;,; @ d	$}];>(}	I{ d}	&;	U}	{	y;Y}	{ P{	R} T}_{ }R } l	{ T}"
"';	|; ${=}	H} (}}8{cp{ s} #}+}	3}kF}<H	 .{ }G}x;	r	D c{; W; {	b;6; k{}B;*};	]} ~	{ ;;} !}}	x}v}n;^;	6V}Y{ h; ~	%*}! H; G{ r{ f;Y{ i}z} N  %}.{;	( 	v} _}	h; 7;<}	^;Z;0; ;	<;<; M; N{	}	_{O} !{f{]{M{;A{}	0;S}${	@;x}y}@	L;1	t{ 3{c{s{_{	`{	D{ ]}!;	${	_J;v+ }	3{B; ]{	}	E6	.x{?+; {x; }v{$};6}T; O; ; (}X7}	j; @} :}#	c{ !{ }x	KXt} >; ?{ c; ;	W;	; l;} h}p}	i{ %	}P}	/{	*}	%L; ;	!{ S{ n} "
"x;  { 1	J;v{	U}({	@ X{ k} H;4;e J	6;;v; G{{]	&{A d{ lM{;K;;	4-{}} p h{;	{	rW;	v{;	f}	}1{^&{9{{ ;~;n;q{	9 R	6{	{ u;a;	;	U;	;Y}	+}}2sk; 8	{	JK;'i;	;$;	W{	P!{{{P	} [;	(;Q; Un;+}g{C;{{	; <{	vS} b;6`} ?{+	%;	}n;q{ r}k; ;{c{ S} 2}~{	4;RW v} R;	kI}|; d; [ O}5; ;;}Z d	{ {&;h	o{ V	v ;	_{{/}  F{f{r{4{{?{ 4;S}	:;];E}	;	&} #e !{>{H; {O{ 0;} H;	p; w}>{1}{	-} 4;"
"S}}	u L{ y} %;2  |{(}	/;,{ )}Y;g}	G}v;T}	};}i {{};[{ E{q} g;T{ ={}R;	k{ j;_;h}gPc;({	F;6}	}} 3	,}<; 0	 P;{'t}u};		}U}s{8{ E} >{}E	{G{H :{  Yog}	}F  D{ R{	 -;M?;= q}_ U	{ ;	 I	{ |{{}	 	1{,}{ x{{ U{ s;J}}	6{>7;,{ D{	{{ ;]}	;M; &}{ V}	n{&	T~;({	}[;	r{#	u{X 9;L; Uf})}   {T}		p{	N;	>{	>	}}D} m{1{	{}X; o}	w}$}	^v} K  f	,}	^3; { @{_} _{	o;	4}	h}H;#.{	{}	;	<{ {G{ $;{ "
"z {a{{D;	?|}{{ ;	`} }	Q}j;4} 	3{Q}	{	* ;}r{a}	} R{p @;  N{ {f; A;8}L	$}{ }}J{ }	k{r} { [; -;p{	I{ {	&}J;	T}	?{Z{>;	5>; ];  wz ^}	u;);	H}	; L	&;	V	E{1{g;C} V} ~;U; ^{	J; { /}	{;(}y} aK /}	.};K;N{w{ `{	}T{l`; #;N{lX;	?; +}{ 	w{	;	q;	z;_;y} 8} 	&{X}	V{ WG}	,; [}U{	v{	Q;	w{	[	Y}N	Yu i{ {!A{}{ b0;	X~} ;-; 8{	E }	;F{	y{}{	";
int x[3][1<<20],j[2048],W[166],n,q=1,f,r,J,K,L[128];
s(C){
int b,*t=W+C*2,i=*t+1,M=i+t[1]+1;
if(q<r){
q*=r;
n*=r;
if(r>>9){
if(b=*w){
n+=b-1-(b>10)-(b>13)-(b>34)-(b>92)<<4;
b=*++w;
w++;
n+=b<33?(b^8)*2%5:(b^6)%3*4+(*w++^8)*2%5+4;
}
}
else{
b=getchar();
n+=b<0?0:b;
}
}
b=q*i/M;
if(i=n>=b){
n-=b;
q-=b;
}
else q=b;
t[i]++;
if(M>63){
*t/=2;
t[1]/=2;
}
return i;
}
l(C){
int a=0,b=1;
while(!s(C+a))a++;
while(a--)b+=b+s(4);
return b-1;
}
N(O,X,P,Y,Q,e,R)int*O,*P;
{
d(S,e)d(a,e){
int T=1<<R-1;
d(o,e)T+=P[o*Y+S*Q]*L[(2*a+1)*o*32/e%128];
O[a*X+S*Q]=T>>R;
}
}
U(y,k,h){
int u,i,*m,c=1<<h,e=c*c,z,p,A,g,v,D;
if(h>5||h>2&&s(h-3)){
c/=2;
d(a,4)U(y+a%2*c,k+a/2*c,h-1);
}
else{
p=l(73);
d(E,3){
m=x[E]+k*f+y;
z=E>0;
d(a,e)j[a]=0;
d(a,e){
if(s(61+h*2+z))break;
a+=l(5+z*10);
i=1-2*s(3);
j[a]=i*(l(25+(z+(a<e/8)*2)*10)+1)*(E?K:J);
}
if(!p){
u=0;
d(a,c){
u+=k?m[-f+a]:0;
u+=y?m[a*f-1]:0;
}
*j+=y&&k?u/2:u;
}
N(j+e,1,j,1,c,c,10);
N(m,f,j+e,c,1,c,10+h);
if(p){
A=p<17;
v=A?9-p:p-25;
d(a,c)d(o,c){
d(V,2){
g=a*v+v;
D=g&7;
g=(g>>3)+o+V;
if(i=g<0)g=(g*8+v/2)/v-2;
g=g<c?g:c-1;
j[V]=i^A?m[g*f-1]:m[-f+g];
}
m[A?o*f+a:a*f+o]+=*j*(8-D)+j[1]*D+4>>3;
}
}
}
}
}
F(b){
putchar(b<0?0:b>255?255:b);
}
main(B){
int k,G,H,h,I;
r=B>1?256:1968;
d(a,128)L[a]=lrint(cos(asin(1)/32*a)*sqrt(2-!a)*1024);
h=l(5);
f=1<<h;
I=f-l(5);
J=l(5);
K=l(5);
U(0,0,h);
printf("P6 %d %d 255 ",f,I);
d(a,I*f){
k=x[0][a];
G=x[1][a];
H=x[2][a];
B=k-G;
F(B+H);
F(k+G);
F(B-H);
}
return 0;
}

