#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <sys/stat.h>
#include <string.h>

#include "list.h"
#include "../utils/utils.h"

tree_err_t tree_ctor(tree_t* tree, call_cnt_t* call_cnt) {
    //TREE INITIALIZATION
    tree->root = NULL;
    tree->size = 0;

    //PROGRAMM LAUNCH COUNTER    
    printf("%lu\n", call_cnt->launch_num);

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
    
    if (tree->root == NULL) {
        tree->root = (node_t*) calloc(1, sizeof(node_t));
        tree->root->data = data;
    }
    
    else
        add_recursion(tree->root, data);
    
    return TREE_ERR_SUCCESS;
}

void add_recursion(node_t* current, int data) {
    
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
    
    recurs_func(tree->root, dot_file);

    fprintf(dot_file, "}");
    fclose(dot_file);
    fclose(counter_file);

    char system_command[100] = "";
    sprintf(system_command, "dot Text_dumps/tree_dump_%lu_%lu.dot -T png -o Graphviz_dumps/tree_dump_%lu_%lu.png", call_cnt->launch_num, call_cnt->call_num, call_cnt->launch_num, call_cnt->call_num);
    system(system_command);

    return TREE_ERR_SUCCESS;
}

tree_err_t recurs_func(node_t* current, FILE* dot_file) {
    
    fprintf(dot_file, "    node%p [label=\"value: %d \n left: %p \n right: %p\"]\n", current, current->data, current->left, current->right);
    
    if (current->left) {
        recurs_func(current->left, dot_file);
        fprintf(dot_file, "    node%p -> node%p\n", current, current->left);
    }

    if (current->right) {
        recurs_func(current->right, dot_file);
        fprintf(dot_file, "    node%p -> node%p\n", current, current->right);
    }
      
    return TREE_ERR_SUCCESS;
}
