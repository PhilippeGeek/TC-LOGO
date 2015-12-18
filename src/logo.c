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
                for (i = 0; i < ind_level * ind_size; ++i) {
                    printf(" ");
                }
                printf("]\n");
                break;
            case _PEN_UP:
                printf("PU\n");
                break;
            case _PEN_DOWN:
                printf("PD\n");
                break;
            case _PEN_CHANGE:
                printf("PS\n");
                break;
            default:
                if(cur->subset!=NULL){
                    printf("EXEC\n");
                    print_logo(cur->subset, ind_level + 1, ind_size);
                    for (i = 0; i < ind_level * ind_size; ++i) {
                        printf(" ");
                    }
                    printf("END EXEC\n");
                }
                break;
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

NODE *create_pen_change() {
    return create_node(_PEN_CHANGE, 0, NULL);
}

NODE *create_pen_up() {
    return create_node(_PEN_UP, 0, NULL);
}

NODE *create_pen_down() {
    return create_node(_PEN_DOWN, 0, NULL);
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
        return node;
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
    VECTOR v = malloc(sizeof(struct vect));
    v->angle = 0;
    v->x=0;
    v->y=0;
    v->computing=true;
    v->pen_down=true;

    v->max = malloc(sizeof(struct vect));
    v->max->angle = 0;
    v->max->x=0;
    v->max->y=0;
    v->max->pen_down=false;

    v->min = malloc(sizeof(struct vect));
    v->min->angle = 0;
    v->min->x=0;
    v->min->y=0;
    v->min->pen_down=false;

    NODE* p = program;

    while(p!=NULL){
        print_node(p, v, NULL);
        p = p->next;
    }

    fprintf(stdout,"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                   "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%d\" height=\"%d\">\n"
                   "  <title>Sortie d'un programme Logo</title>\n", ((int)v->max->x-(int)v->min->x) + 11, ((int)v->max->y-(int)v->min->y) + 11);
    v->angle = 0;
    v->x=5.0;
    v->y=5.0;
    v->computing = false;
    v->pen_down=true;
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
            if(v->pen_down&&!v->computing)
                fprintf(out, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"black\"/>\n",
                        v->x-v->min->x, v->y-v->min->y, next.x - v->min->x, next.y - v->min->y);
            else if(v->computing){
                v->max->x = v->max->x < next.x ? next.x : v->max->x;
                v->max->y = v->max->y < next.y ? next.y : v->max->y;
                v->min->x = v->min->x > next.x ? next.x : v->min->x;
                v->min->y = v->min->y > next.y ? next.y : v->min->y;
            }
            *v = next;
            break;
        case _LEFT:
            v->angle-=node->value;
            break;
        case _RIGHT:
            v->angle+=node->value;
            break;
        case _PEN_UP:
            v->pen_down = false;
            break;
        case _PEN_DOWN:
            v->pen_down = true;
            break;
        case _PEN_CHANGE:
            v->pen_down = !(v->pen_down);
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
        default:
            subprog = node->subset;
            NODE* current = subprog;
            while(current!=NULL){
                print_node(current, v, stdout);
                current = current->next;
            }
            break;
    }
}
