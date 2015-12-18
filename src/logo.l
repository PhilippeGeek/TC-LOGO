%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "logo.tab.h"
#include "logo.h"

%}
%option noyywrap
%%
[ \t\n]          ;
FORWARD|fw	return FORWARD;
LEFT|lt		return LEFT;
RIGHT|rt	return RIGHT;
REPEAT|rp	return REPEAT;
CIRCLE		return CIRCLE;
BUBBLE		return BUBBLE;
PU|pu		return PEN_UP;
PD|pd		return PEN_DOWN;
PS|ps		return PEN_CHANGE;
TO|to		return TO;
END|end		return END;
\[|\]		return BRACKETS;
[0-9]+  		{ yylval.dVal=strtod(yytext, NULL); return integer; }
[0-9]+\.[0-9]+ 		{ yylval.dVal=strtod(yytext, NULL); return integer; }
[a-z]+    { yylval.sVal=strdup(yytext); return string; }
%%
