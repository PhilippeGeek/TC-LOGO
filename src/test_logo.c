//
// Created by pvienne on 05/12/15.
//

#include "logo.h"

int main(){
    PROG test_prog = create_forward(160);
    add_node(test_prog, create_left(90));
    add_node(test_prog, create_forward(160));
    PROG rep_prog = create_forward(0.5);
    add_node(rep_prog, create_left(1));
    NODE* rep_node = create_repeat(360, rep_prog);
    add_node(test_prog, rep_node);
    //print_logo(test_prog, 0, 2);
    print_svg(test_prog);
    free_prog(test_prog);
    return 0;
}