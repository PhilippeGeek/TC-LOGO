%{
#include <stdlib.h>
#include <stdio.h>
#include "logo.tab.h"
#include "logo.h"

%}
%option noyywrap
%%
[ \t\n]          ;
FORWARD|Forward|forward	return FORWARD;
LEFT|Left|left	  	return LEFT;
RIGHT|Right|right	return RIGHT;
REPEAT|Repeat|repeat	return REPEAT;
PU|pu|PEN_UP|Pen_Up|pen_up	return PEN_UP;
PD|pd|PEN_DOWN|Pen_Down|pen_down	return PEN_DOWN;
PS|ps|PEN_SWITCH|Pen_Switch|pen_switch	return PEN_CHANGE;
\[|\]			return BRACKETS;
[0-9]+  		{ yylval.dVal=strtod(yytext, NULL); return integer; }
[0-9]+\.[0-9]+ 		{ yylval.dVal=strtod(yytext, NULL); return integer; }
.          			;
%%
