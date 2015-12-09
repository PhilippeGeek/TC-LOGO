%{
#include <stdio.h>
int yyparse();
int yylex();
int yyerror(char *s);
%}

%union {
           int instruction; // May be 0 (Forward), 1 (Left), 2 (Right) or 3 (Repeat)
           int value;
       }
%token LEFT RIGHT FORWARD REPEAT integer

%%

PROG : INST | PROG INST { printf("Un programme!\n"); }
INST: FORWARD VALUE |
      LEFT VALUE |
      RIGHT VALUE |
      REPEAT VALUE '[' PROG ']'  { printf("Un programme!\n"); }
VALUE: integer

%%

int yyerror(char *s) {
	printf("yyerror : %s\n",s);
	return 0;
}

int main(void) {
	yyparse();
	return 0;
}