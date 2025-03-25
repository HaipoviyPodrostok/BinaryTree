#include <cstdio>
#include <cstdlib>

#include "list.h"
#include "../utils/utils.h"

int main() {
    
    tree_t tree = {};
    call_cnt_t call_cnt = {};

    tree_ctor(&tree, &call_cnt);

    node_add(&tree, 20);
    node_add(&tree, 15);
    node_add(&tree, 10);
    node_add(&tree, 5);

    tree_dump(&tree, &call_cnt);

    return 0;
}