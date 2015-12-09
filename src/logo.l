%{
#include <stdlib.h>
#include <stdio.h>
#include "tokens.h"
%}
%option noyywrap
%%
[ \t\n]          ;
FORWARD|Forward|forward	  	{ return FORWARD; }
LEFT|Left|left	  			{ return LEFT; }
RIGHT|Right|right	  		{ return RIGHT; }
REPEAT|Repeat|repeat	  	{ return REPEAT; }
[0-9]+           			{ return integer; }
.          					;
%%
