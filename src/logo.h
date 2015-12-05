//
// Created by pvienne on 05/12/15.
//

#ifndef TP_LOGO_LOGO_H
#define TP_LOGO_LOGO_H
#define _FORWARD 0
#define _LEFT 1
#define _RIGHT 2
#define _REPEAT 3

typedef struct NODE {
    int instruction; // May be 0 (Forward), 1 (Left), 2 (Right) or 3 (Repeat)
    int value;
    struct NODE *next;
    struct NODE *subset;
} NODE;

typedef NODE* PROG;

void print_logo(NODE *cur, int ind_level, int ind_size);

NODE *create_node(int type, int value, PROG subset);

NODE *create_forward(int value);

NODE *create_left(int value);

NODE *create_right(int value);

NODE *create_repeat(int times, PROG prog_to_repeat);

NODE *add_node(PROG programme, NODE *node);

NODE* add_repeat_node(NODE *repeat_node, NODE *node);

void free_prog(PROG program);

#endif //TP_LOGO_LOGO_H
