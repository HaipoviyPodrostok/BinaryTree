#ifndef UTILS_H
#define UTILS_H

#include <cstdio>
#include <cstdlib>

#define ERROR_HANDLE(call_func, ...) ({                                 \
    tree_err_t error = call_func;                                       \
    if (error) {                                                        \
        fprintf(stderr, "[" #call_func "] Error code: %d\n", error);    \
        __VA_ARGS__;                                                    \
        return error;                                                   \
    }                                                                   \
});

typedef enum { 
    TREE_ERR_SUCCESS = 0,
    TREE_ERR_DUMP_ERROR = 1,
    TREE_ERR_NOT_EXIST = 2,
    TREE_ERR_TREE_IS_EMPTY = 3,
    TREE_ERR_SELECTION_ERROR = 4,
    TREE_ERR_FILE_READING_ERROR = 5,
} tree_err_t;

#endif //UTILS_H