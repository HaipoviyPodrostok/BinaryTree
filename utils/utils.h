#ifndef UTILS_H
#define UTILS_H

#include <cstdio>
#include <cstdlib>

enum tree_err_t{ 
    TREE_ERR_SUCCESS = 0,
    TREE_ERR_DUMP_ERROR = 1,
};




// #define ERROR_HANDLE(call_func, ...);


// __func__
// __VA_ARGS___
// return error

// enum Error error = call_func(...)
// if (error)
// {
//  perror("Can_t" __func__);
//  destructors
//  return error
//};

#endif //UTILS_H