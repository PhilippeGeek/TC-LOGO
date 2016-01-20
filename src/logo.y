%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logo.h"
int yyparse();
int yylex();
int yyerror(char *s);
char** prog_names;
PROG* programmes;
PROG instruction;
int currentProg=-1;
int progCount = 0;
int mallocatedProgs = 7;
%}

%code requires {
    #include "logo.h"
}

%destructor { free($$); } NAME

%union {
  NODE* tVal;
  int iVal;
  double dVal;
  char* sVal;
  }

%token LEFT RIGHT FORWARD REPEAT BRACKETS PEN_UP PEN_DOWN PEN_CHANGE CIRCLE BUBBLE TO END SET_COLOR
%type <tVal> INST PROG SUBPROG
%type <dVal> VALUE
%type <sVal> NAME
%token <dVal> integer
%token <sVal> string

%%

PROG :
    INST {
        $$ = $1;
        if(instruction == NULL && currentProg == -1 && $1->instruction>=0){
            instruction = $$;
        }
    }
    | PROG INST {
        if(currentProg == -1){
            if($2->instruction == -2){
                $1 = instruction;
                add_node($1, $2);
                $$ = $1;
            } else if(instruction == NULL){
                $$ = $2;
                instruction = $$;
            } else {
                add_node($1, $2);
                $$ = $1;
            }
        } else {
            if($2->instruction == -1){
                $$ = $2;
            } else {
                add_node($1, $2);
                $$ = $1;
            }
        }
    }

SUBPROG:
    INST { $$ = $1; }
    | SUBPROG INST { add_node($1, $2); }

INST: FORWARD VALUE { $$ = create_forward($2); }
    | LEFT VALUE { $$ = create_left($2); }
    | CIRCLE VALUE { PROG p = create_left(1); add_node(p, create_forward($2)); $$ = create_repeat(360, p); }
    | BUBBLE VALUE {
        PROG p = create_left(1);
        add_node(p, create_forward($2));
        $$ = create_repeat(360, p);
        }
    | RIGHT VALUE { $$ = create_right($2); }
    | REPEAT VALUE BRACKETS SUBPROG BRACKETS  { $$ = create_repeat($2, $4); }
    | PEN_UP { $$ = create_pen_up(); }
    | PEN_DOWN { $$ = create_pen_down(); }
    | PEN_CHANGE { $$ = create_pen_change(); }
    | SET_COLOR VALUE VALUE VALUE { $$ = create_set_color($2, $3, $4); }
    | TO NAME {
        // Check if we are not already storing a program
        if(currentProg!=-1){
            yyerror("Can not declare programme inside another !");
        }

        // First find if it's a redefinition of the function
        int i=0;
        for(i=0;i<progCount;i++){
            if(strcmp($2,*(prog_names+i)) == 0)
                break;
        }

        if(i>=progCount){ // It's a new function !
            // Set next number code to programme
            currentProg = progCount;

            // If we not have sufficiant memory
            if(mallocatedProgs - 1>=currentProg){
                // Rallocate 10 more space storage
                programmes = realloc(programmes, (mallocatedProgs + 10) * sizeof(PROG));
                prog_names = realloc(prog_names, (mallocatedProgs + 10) * sizeof(char*));
                mallocatedProgs += 10;
            }
        } else { // Just rewrite the old one
            currentProg = i;
        }

        // To be sure to clear old data
	if(*(programmes+currentProg)!=NULL)free(*(programmes+currentProg));
        *(programmes+currentProg) = create_node(-1,0.0,NULL);

	if(*(prog_names+currentProg)!=NULL)free(*(prog_names+currentProg));
        // Store name for program
        *(prog_names+currentProg) = strdup($2);

	free($2);

        $$ = *(programmes+currentProg);
    }
    | END {
        if(currentProg!=-1){ // If we are able to close a program
            progCount++;
            currentProg = -1;
        } else { // If not, cry on the developer
            yyerror("No program declaration to end");
        }

        // Create an empty node (if not, bison will not be happy)
        $$ = create_node(-2,0.0,NULL);
    }
    | NAME {
        int i=0;
        for(i=0;i<progCount;i++){
            if(strcmp($1,*(prog_names+i)) == 0)
                break;
        }
        if(i >= progCount)
            yyerror("Command is not defined");
        $$ = create_node(-3,0.0,*(programmes+i));
    }
VALUE: integer { $$=$1; }
NAME:  string  { $$=$1; }
%%

int yyerror(char *s) {
	fprintf(stderr, "yyerror : %s\n",s);
	exit(1);
}

int main(void) {
	int i=0;
    prog_names = malloc(mallocatedProgs*sizeof(char*));
    programmes = malloc(mallocatedProgs*sizeof(PROG));
	for(i=0; i<mallocatedProgs;i++){
			(*(prog_names+i)) = NULL;
			(*(programmes+i)) = NULL;
	}
	yyparse();
	if(currentProg!=-1)
	    yyerror("Command declaration is not ended!");
	print_svg(instruction);
	for(i=0; i<mallocatedProgs;i++){
		if(*(prog_names+i)!=NULL)
			free(*(prog_names+i));
		if(*(programmes+i)!=NULL){
			free_prog(*(programmes+i));
			free(*(programmes+i));
		}
	}
	free(prog_names);
	free(programmes);
	if(instruction!=NULL)
	    free_prog(instruction);
	return 0;
}
