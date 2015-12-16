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

#include <stdio.h>
#include <stdbool.h>

typedef struct NODE {
    int instruction; // May be 0 (Forward), 1 (Left), 2 (Right) or 3 (Repeat)
    double value;
    struct NODE *next;
    struct NODE *subset;
} NODE;

typedef NODE* PROG;

typedef struct vect {
    double x;
    double y;
    double angle;
    bool pen_down;
} vect;

typedef struct vect* VECTOR;

void print_logo(NODE *cur, int ind_level, int ind_size);

void print_svg(NODE *cur);

void print_node(NODE* node, VECTOR v, FILE* out);

NODE *create_pen_change();

NODE *create_pen_down();

NODE *create_pen_up();

NODE *create_node(int type, double value, PROG subset);

NODE *create_forward(double value);

NODE *create_left(double value);

NODE *create_right(double value);

NODE *create_repeat(int times, PROG prog_to_repeat);

NODE *add_node(PROG programme, NODE *node);

NODE* add_repeat_node(NODE *repeat_node, NODE *node);

void free_prog(PROG program);

void compute_max_point(NODE* node, VECTOR v, VECTOR max);

#endif //TP_LOGO_LOGO_H

#pragma clang diagnostic pop