//
// Created by pvienne on 05/12/15.
//

#include <stdio.h>
#include <stdlib.h>
#include "logo.h"

void print_logo(NODE *cur, int ind_level, int ind_size) {
    while (cur != NULL) {
        int i = 0;
        for (i = 0; i < ind_level * ind_size; ++i) {
            printf(" ");
        }
        switch (cur->instruction) {
            case 0:
                printf("FORWARD %d\n", cur->value);
                break;
            case 1:
                printf("LEFT %d\n", cur->value);
                break;
            case 2:
                printf("RIGHT %d\n", cur->value);
                break;
            case 3:
                printf("REPEAT %d [\n", cur->value);
                print_logo(cur->subset, ind_level + 1, ind_size);
                printf("]\n");
                break;
            default:break;
        }
        cur = cur->next;
    }
}

NODE *create_node(int type, int value, PROG subset) {
    NODE *node = malloc(sizeof(NODE));
    node->value = value;
    node->instruction = type;
    node->subset = subset;
    node->next = NULL;
    return node;
}

NODE *create_forward(int value) {
    return create_node(_FORWARD, value, NULL);
}

NODE *create_left(int value) {
    return create_node(_LEFT, value, NULL);
}

NODE *create_right(int value) {
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