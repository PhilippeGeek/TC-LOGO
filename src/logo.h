//
// Created by pvienne on 05/12/15.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#ifndef TP_LOGO_LOGO_H
#define TP_LOGO_LOGO_H
#define _FORWARD 0
#define _LEFT 1
#define _RIGHT 2
#define _REPEAT 3
#define _INTEGER 4
#define _UNKNOWN 5
#define _PEN_UP 6
#define _PEN_DOWN 7
#define _PEN_CHANGE 8
#define _SET_COLOR 9

#include <stdio.h>
#include <stdbool.h>

#define OP_NONE 0
#define OP_PLUS 1
#define OP_MINUS 2
#define OP_TIMES 3
#define OP_DIVIDE 4
#define OP_BIN_SHIFT 6
#define OP_MOD 5

struct VAR {
    double value;
    struct VAR *left;
    int op;
    struct VAR *right;
};

typedef struct VAR VAR;

struct NODE {
    int instruction; // May be 0 (Forward), 1 (Left), 2 (Right) or 3 (Repeat)
    VAR *value;
    struct NODE *next;
    struct NODE *subset;
    void* func_call;
};
typedef struct NODE NODE;
typedef NODE* PROG;

//typedef struct FUNCTION {
//    char* name;
//    PROG function;
//    int arg_count;
//    char** arg_names;
//} FUNCTION;
//
//typedef struct FUNC_CALL{
//    struct FUNCTION function;
//    void** args;
//};

struct vect {
    double x;
    double y;
    double angle;
    unsigned int color;
    bool pen_down;
    bool computing;
    struct vect* min;
    struct vect* max;
};

typedef struct vect* VECTOR;

void print_logo(NODE *cur, int ind_level, int ind_size);

void print_svg(NODE *cur);

void print_node(NODE* node, VECTOR v, FILE* out);

NODE *create_set_color(VAR *r, VAR *g, VAR *b);

NODE *create_pen_change();

NODE *create_pen_down();

NODE *create_pen_up();

NODE *create_node(int type, VAR *value, PROG subset);

NODE *create_forward(VAR *value);

NODE *create_left(VAR *value);

NODE *create_right(VAR *value);

NODE *create_repeat(VAR *times, PROG prog_to_repeat);

NODE *add_node(PROG programme, NODE *node);

NODE* add_repeat_node(NODE *repeat_node, NODE *node);

void free_prog(PROG program);

#endif //TP_LOGO_LOGO_H

#pragma clang diagnostic pop