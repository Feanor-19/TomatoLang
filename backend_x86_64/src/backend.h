#ifndef BACKEND_H
#define BACKEND_H

#include "back_common.h"
#include "config_back.h"
#include "tr_AST_to_IR_funcs.h"

#define DEF_STATUS(name, message) message,
const char * const status_messages[] =
{
    #include "back_statuses.h"
    "FICTIONAL MESSAGE!"
};
#undef DEF_STATUS


typedef Status(*tr_AST_to_IR_t)(const Tree*,IR*,TreeNode*,Counters*);

#define DEF_AST_OP(name) tr_AST_to_IR_##name,
const tr_AST_to_IR_t AST_OPS_BACKEND[] = 
{
    #include "ast_ops_defs.h"
    NULL
};


Status translate_AST_to_IR( const Tree *AST, IR* IR );

//! @brief Translates given node and subtree, which starts with this node, into IR.
Status translate_AST_node( const Tree *AST, IR *IR, TreeNode *node, Counters *cnts );


void print_status_message( FILE *stream, Status status );

int init_log( Config cfg );

#endif /* BACKEND_H */