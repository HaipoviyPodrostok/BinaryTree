#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <sys/stat.h>
#include <string.h>

#include "tree.h"
#include "../utils/utils.h"

tree_err_t tree_ctor(tree_t* tree, call_cnt_t* call_cnt) {
    
    assert(tree != NULL);
    assert(call_cnt != NULL);
    
    //TREE INITIALIZATION
    tree->root = NULL;
    tree->size = 0;

    //CALL_COUNTER INITIALIZATION
    call_cnt->call_num = 0;
    call_cnt->launch_num = 0;

    //PROGRAMM LAUNCH COUNTER    
    FILE* counter_file = fopen(COUNTER_FILE, "r+t");

    if (!counter_file) {
        counter_file = fopen(COUNTER_FILE, "w+");
        call_cnt->launch_num = 1;
    }
    
    else {
        if (fscanf(counter_file, "Last launch_num = %lu", &(call_cnt->launch_num)) != 1) {
            return TREE_ERR_DUMP_ERROR;
        }
        call_cnt->launch_num++;
    }

    fseek(counter_file, 0, SEEK_SET);
    fprintf(counter_file, "Last launch_num = %lu", call_cnt->launch_num);

    fclose(counter_file);

    return TREE_ERR_SUCCESS;
}

tree_err_t node_add(tree_t* tree, int data) {
    
    assert(tree != NULL);

    if (tree->root == NULL) {
        tree->root = (node_t*) calloc(1, sizeof(node_t));
        if (!tree->root)    return TREE_ERR_SELECTION_ERROR;
        tree->root->data = data;
    }
    
    else {
        add_recursion(tree->root, data);
    }
    
    return TREE_ERR_SUCCESS;
}

tree_err_t add_recursion(node_t* current, int data) {
    
    if (data < current->data) {
        if (current->left == NULL) {
            current->left = (node_t*) calloc(1, sizeof(node_t));
            current->left->data = data;
        } 
        
        else {
            add_recursion(current->left, data);
        }
    }
    
    else {
        if (current->right == NULL) {
            current->right = (node_t*) calloc(1, sizeof(node_t));
            current->right->data = data;
        }
        
        else {
            add_recursion(current->right, data);
        }
    }
}

tree_err_t tree_dump(tree_t* tree, call_cnt_t* call_cnt) {
    
    assert(tree != NULL);
    assert(call_cnt != NULL);

    if (tree->root == NULL) {
        printf ("tree is empty\n");
        return TREE_ERR_SUCCESS;
    }
    
    call_cnt->call_num++;
    
    FILE* counter_file = fopen(COUNTER_FILE, "r");
    fscanf(counter_file, "Last launch_num = %lu", &call_cnt->launch_num);

    char dot_file_name[100] = "";
    sprintf(dot_file_name, "Text_dumps/tree_dump_%lu_%lu.dot", call_cnt->launch_num, call_cnt->call_num);

    FILE* dot_file = fopen(dot_file_name, "w");
    fprintf(dot_file, DOT_TITLE);

    recurs_func(tree->root, dot_file, tree);

    fprintf(dot_file, "}");
    fclose(dot_file);
    fclose(counter_file);

    char system_command[100] = "";
    sprintf(system_command, "dot Text_dumps/tree_dump_%lu_%lu.dot -T png -o Graphviz_dumps/tree_dump_%lu_%lu.png", call_cnt->launch_num, call_cnt->call_num, call_cnt->launch_num, call_cnt->call_num);
    system(system_command);

    return TREE_ERR_SUCCESS;
}

tree_err_t recurs_func(node_t* current, FILE* dot_file, tree_t* tree) {
    
    assert(current != NULL);
    assert(dot_file != NULL);
    assert(tree != NULL);

    if (current->left)    recurs_func(current->left, dot_file, tree);
    if (current->right)   recurs_func(current->right, dot_file, tree);
      
    print_node(current, dot_file, tree);

    return TREE_ERR_SUCCESS;
}

tree_err_t print_node(node_t* current, FILE* dot_file, tree_t* tree) {
    
    assert(current != NULL);
    assert(dot_file != NULL);
    assert(tree != NULL);

    char fillcolor [20] = "";
    
    if (current == tree->root)    sprintf(fillcolor, ROOT_COLOR);
    else                          sprintf(fillcolor, NODE_COLOR);

    fprintf(dot_file, "\n    node%p [fillcolor= \"%s\", label=\"{<f0> value: %d | { <f1> left: %p |<f2> right: %p }}\"]\n", current, fillcolor, current->data, current->left, current->right);

    if (current->left)    fprintf(dot_file, "    node%p:f1 -> node%p:f0 [label=\"Да\", fontcolor= \""LEFT_ARROW_COLOR"\", color= \""LEFT_ARROW_COLOR"\", penwidth=2]\n", current, current->left);
    if (current->right)   fprintf(dot_file, "    node%p:f2 -> node%p:f0 [label=\"Нет\", fontcolor= \""RIGHT_ARROW_COLOR"\", color= \""RIGHT_ARROW_COLOR"\", penwidth=2]\n", current, current->right);

    return TREE_ERR_SUCCESS;
}

tree_err_t tree_dtor(tree_t* tree) {

    if (tree == NULL)    return TREE_ERR_NOT_EXIST;    
    if (tree->root == NULL)    return TREE_ERR_TREE_IS_EMPTY;

    dtor_node(tree->root);

    return TREE_ERR_SUCCESS;
}

tree_err_t dtor_node(node_t* current) {
    
    assert(current != NULL);

    if (current->left != NULL)    dtor_node(current->left);
    if (current->right != NULL)   dtor_node(current->right);  
    
    free(current); 

    return TREE_ERR_SUCCESS;
}