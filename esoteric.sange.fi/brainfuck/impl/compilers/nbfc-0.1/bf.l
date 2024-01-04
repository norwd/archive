%{
/* This is the lexer for brainfuck */
#include "y.tab.h"
#include <string.h>
#include <stdio.h>
%}
%%
\+ 	{return INCR;}
- 	{return DECR;}
\> {return FORE;}
\< 	{return BACK;}
\[		{return LOOP;}
\]		{return POOL;}
\.	{return PUTC;}
,	{return GETC;}
[ \t\n] {/*IGNORE*/}
.  {/*IGNORE*/}
%%
  
