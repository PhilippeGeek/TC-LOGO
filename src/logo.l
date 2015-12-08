%{
#include <stdlib.h>
#include <stdio.h>
#include "logo.h"
%}
%option noyywrap
%%
[ \t\n]          ;
FORWARD|Forward|forward	  { return _FORWARD; }
LEFT|Left|left	  { return _LEFT; }
RIGHT|Right|right	  { return _RIGHT; }
REPEAT|Repeat|repeat	  { return _REPEAT; }
[0-9]+           { return _INTEGER; }
.          { return _UNKNOWN; }
%%
int main() {
	yylex();
}
