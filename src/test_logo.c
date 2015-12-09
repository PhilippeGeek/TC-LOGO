//
// Created by pvienne on 05/12/15.
//

#include "logo.h"

int main(){
    PROG test_prog = create_forward(100);
    add_node(test_prog, create_left(45));
    add_node(test_prog, create_forward(45));
    add_node(test_prog, create_right(45));
    PROG rep_prog = create_forward(1);
    NODE* rep_node = create_repeat(360, rep_prog);
    add_node(test_prog, rep_node);
    add_repeat_node(rep_node, create_right(1));
    print_logo(test_prog, 0, 2);
    free_prog(test_prog);
    return 0;
}