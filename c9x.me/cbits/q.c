#include <stdio.h>
#define o(x) fputs(x,stdout);
#define O(x) putchar((c=x)==122?92:c);
char c,*p,*q,s[]=
"#include <stdio.h>\n"
"#define o(x) fputs(x,stdout);\n"
"#define O(x) putchar((c=x)==122?92:c);\n"
"char c,*p,*q,s[]=\n"
"@main(){ q=p=s; while(*p!='@') O(*p++)\n"
"	o(\"z\"\") do\n"
"		if(*q==10&&q[1])\n"
"			o(\"zznz\"znz\"\")\n"
"		else if(*q==34)\n"
"			o(\"zzz\"\")\n"
"		else if(*q!=10)\n"
"			putchar(*q);\n"
"	while(*++q); o(\"zznz\";zn\")\n"
"	while(*++p) O(*p) }\n";
main(){ q=p=s; while(*p!='@') O(*p++)
	o("\"") do
		if(*q==10&&q[1])
			o("\\n\"\n\"")
		else if(*q==34)
			o("\\\"")
		else if(*q!=10)
			putchar(*q);
	while(*++q); o("\\n\";\n")
	while(*++p) O(*p) }
