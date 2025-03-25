#ifndef LIST_H
#define LIST_H

#define COUNTER_FILE "Text_dumps/counter.dot"

#define DOT_TITLE "digraph BinaryTree {\n    node [shape=\"Mrecord\", style=\"filled\", fillcolor=\"#F0F8FF\", fontname=\"Courier New\"];\n"

#include <cstdio>
#include <cstdlib>

#include "../utils/utils.h"

typedef struct Node {
    int data;   
    struct Node* left;
    struct Node* right;
} node_t;

typedef struct Tree {
    node_t* root;
    size_t size;
} tree_t;

typedef struct CallCounter {
    size_t call_num;
    size_t launch_num;
} call_cnt_t;

tree_err_t tree_ctor(tree_t* tree, call_cnt_t* call_cnt);
tree_err_t node_add(tree_t* tree, int data);
tree_err_t recurs_func(node_t* current, FILE* dot_file);
tree_err_t tree_dump(tree_t* tree, call_cnt_t* call_cnt);
void add_recursion(node_t* tmp, int data);
tree_err_t print2dot(node_t* current, FILE* dot_file, const char* call_func);

#endif //LIST_H