#ifndef MIDDLEEND_H
#define MIDDLEEND_H


#include "common.h"
#include "config_middle.h"


#define DEF_STATUS(name, msg) STATUS_##name,
enum Status
{
    #include "middle_statuses.h"
};
#undef DEF_STATUS


#define DEF_STATUS(name, message) message,
const char * const status_messages[] =
{
    #include "middle_statuses.h"
    "FICTIONAL MESSAGE!"
};
#undef DEF_STATUS


//! @brief Helper function for 'optimize_AST'. Applies optimization
//! 'fold constants' to specified subtree. Sets correspondingly *changes
Status opt_fold_consts(Tree *AST, TreeNode *node, bool *changes);

//! @brief Applies optimizations to AST, changing it.
Status optimize_AST(Tree *AST);

void print_status_message( FILE *stream, Status status );

int init_log( Config cfg );

#endif /* MIDDLEEND_H */
