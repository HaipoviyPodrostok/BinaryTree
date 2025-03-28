#ifndef LIST_H
#define LIST_H

#include <cstdio>
#include <cstdlib>

#include "../utils/utils.h"

#define COUNTER_FILE "Text_dumps/counter.dot"
#define DOT_TITLE "digraph BinaryTree {\n    node [shape=\"Mrecord\", style=\"filled\", fontname=\"Courier New\"];\n"

#define ROOT_COLOR "#FFFF00"
#define NODE_COLOR "#00FFFF"
#define LEFT_ARROW_COLOR "#008000"
#define RIGHT_ARROW_COLOR "#B22222"


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

//CTOR
tree_err_t tree_ctor(tree_t* tree, call_cnt_t* call_cnt);

//ADD NOTE
tree_err_t node_add(tree_t* tree, int data);
tree_err_t dump_recursion(node_t* current, FILE* dot_file, tree_t* tree);

//DUMP
tree_err_t tree_dump(tree_t* tree, call_cnt_t* call_cnt);
tree_err_t add_recursion(node_t* current, int data);
tree_err_t print_node(node_t* current, FILE* dot_file, tree_t* tree);

//DTOR
void tree_dtor(tree_t* tree);
void dtor_node(node_t* current);

#endif //LIST_H