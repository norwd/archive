%token INCR 
%token DECR
%token LOOP
%token POOL
%token FORE
%token BACK
%token GETC
%token PUTC
%start s
%%
s: /* empty */ 
	| s op
op: INCR {process("array[p]++;");}
	| DECR {process("array[p]--;");}
	| LOOP {process("while(array[p] != 0) {");}
	| POOL {process("}");}
	| FORE {process("p++;");}
	| BACK {process("p--;");}
	| GETC {process("array[p]=getchar();");}
	| PUTC {process("putchar(array[p]);");}
%%
#include "bf.h"

int process(char * string) {
	emmit(string);
	return (0);
}

int yyerror(char * string) {
	printf("Error: %s", string);
	return(1);
}
