#include <cstdio>
#include <cstdlib>

#include "tree.h"
#include "../utils/utils.h"

int main() {
    
    tree_t tree = {};
    call_cnt_t call_cnt = {};

    ERROR_HANDLE(tree_ctor, &tree, &call_cnt);

    ERROR_HANDLE(node_add, &tree, 20);
    ERROR_HANDLE(node_add, &tree, 15);
    ERROR_HANDLE(node_add, &tree, 10);
    ERROR_HANDLE(node_add, &tree, 5);
    ERROR_HANDLE(node_add, &tree, 27);
    ERROR_HANDLE(node_add, &tree, 14);
    ERROR_HANDLE(node_add, &tree, 30);

    ERROR_HANDLE(tree_dump, &tree, &call_cnt);

    ERROR_HANDLE(tree_dtor, &tree);

    return 0;
}