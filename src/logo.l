%{
#include <stdlib.h>
#include <stdio.h>
#include "logo.tab.h"
#include "logo.h"
#define YYSTYPE double
%}
%option noyywrap
%%
[ \t\n]          ;
FORWARD|Forward|forward	return FORWARD;
LEFT|Left|left	  	return LEFT;
RIGHT|Right|right	return RIGHT;
REPEAT|Repeat|repeat	return REPEAT;
\[|\]			return BRACKETS;
[0-9]+  		{ yylval.dVal=strtod(yytext, NULL); return integer; }
[0-9]+\.[0-9]+ 		{ yylval.dVal=strtod(yytext, NULL); return integer; }
.          			;
%%
