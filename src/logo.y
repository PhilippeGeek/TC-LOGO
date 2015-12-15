%{
#include <stdio.h>
#include "logo.h"
int yyparse();
int yylex();
int yyerror(char *s);
PROG instruction;
int currentNodeType;
%}

%code requires {
    #include "logo.h"
}

%union {
  NODE* tVal;
  int iVal;
  double dVal;
  }

%token LEFT RIGHT FORWARD REPEAT BRACKETS PEN_UP PEN_DOWN PEN_CHANGE
%type <tVal> INST PROG
%type <dVal> VALUE
%token <dVal> integer

%%

PROG :
    INST { $$ = $1; if(instruction == NULL) instruction = $$; }
    | PROG INST { add_node($1, $2); $$ = $1; }
INST: FORWARD VALUE { $$ = create_forward($2); }
    | LEFT VALUE { $$ = create_left($2); }
    | RIGHT VALUE { $$ = create_right($2); }
    | REPEAT VALUE BRACKETS PROG BRACKETS  { $$ = create_repeat($2, $4); }
    | PEN_UP { $$ = create_pen_up(); }
    | PEN_DOWN { $$ = create_pen_down(); }
    | PEN_CHANGE { $$ = create_pen_change(); }
VALUE: integer { $$=$1; }

%%

int yyerror(char *s) {
	printf("yyerror : %s\n",s);
	return 0;
}

int main(void) {
	yyparse();
	print_svg(instruction);
	return 0;
}
