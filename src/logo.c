//
// Created by pvienne on 05/12/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "logo.h"

void print_logo(NODE *cur, int ind_level, int ind_size) {
    while (cur != NULL) {
        int i = 0;
        for (i = 0; i < ind_level * ind_size; ++i) {
            printf(" ");
        }
        switch (cur->instruction) {
            case 0:
                printf("FORWARD %lf\n", cur->value);
                break;
            case 1:
                printf("LEFT %lf\n", cur->value);
                break;
            case 2:
                printf("RIGHT %lf\n", cur->value);
                break;
            case 3:
                printf("REPEAT %lf [\n", cur->value);
                print_logo(cur->subset, ind_level + 1, ind_size);
                printf("]\n");
                break;
            default:break;
        }
        cur = cur->next;
    }
}

NODE *create_node(int type, double value, PROG subset) {
    NODE *node = malloc(sizeof(NODE));
    node->value = value;
    node->instruction = type;
    node->subset = subset;
    node->next = NULL;
    return node;
}

NODE *create_forward(double value) {
    return create_node(_FORWARD, value, NULL);
}

NODE *create_left(double value) {
    return create_node(_LEFT, value, NULL);
}

NODE *create_right(double value) {
    return create_node(_RIGHT, value, NULL);
}

NODE *create_repeat(int times, PROG prog_to_repeat) {
    return create_node(_REPEAT, times, prog_to_repeat);
}

// Assuming the program already contains at least one node
NODE *add_node(PROG programme, NODE *node) {
    if (programme == NULL) {
        return programme;
    }

    PROG main_node = programme;
    while (programme->next != NULL)
        programme = programme->next;

    programme->next = node;
    return main_node;
}

NODE* add_repeat_node(NODE *repeat_node, NODE *node) {
    if (repeat_node == NULL)
        return node;
    PROG new_subset = add_node(repeat_node->subset, node);
    repeat_node->subset = new_subset;
    return new_subset;
}

void free_prog(PROG program) {
    if (program == NULL)
        return;
    PROG parent = NULL;
    while (program->next != NULL) {
        parent = program;
        program = program->next;
    }
    if (program->instruction == _REPEAT) {
        free_prog(program->subset);
    }
    if(parent!=NULL)
        parent->next = NULL;
    free(program);
    free_prog(parent);
}

void print_svg(NODE *program){
    fprintf(stdout,"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                   "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"300\" height=\"200\">\n"
                   "  <title>Sortie d'un programme Logo</title>\n");
    VECTOR v = malloc(sizeof(struct vect));
    v->angle = 0;
    v->x=0;
    v->y=0;
    while(program!=NULL){
        print_node(program, v, stdout);
        program = program->next;
    }
    fprintf(stdout,"\n</svg>\n");
}

void print_node(NODE* node, VECTOR v, FILE* out){
    if(node == NULL) return;
    struct vect next;
    PROG subprog;
    int i;
    switch (node->instruction) {
        case _FORWARD:
            next = (*v);
            next.y += node->value * sin(M_PI * v->angle/180.0);
            next.x += node->value * cos(M_PI * v->angle/180.0);
            fprintf(out, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"black\"/>\n", v->x, v->y, next.x, next.y);
            *v = next;
            break;
        case _LEFT:
            v->angle+=node->value;
            break;
        case _RIGHT:
            v->angle+=node->value;
            break;
        case _REPEAT:
            subprog = node->subset;
            for (i = 0; i < node->value; ++i) {
                NODE* current = subprog;
                while(current!=NULL){
                    print_node(current, v, stdout);
                    current = current->next;
                }
            }
            break;
        default:break;
    }
}