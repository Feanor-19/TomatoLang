#ifndef BACKEND_H
#define BACKEND_H

#include "back_common.h"
#include "config_back.h"


#define DEF_STATUS(name, message) message,
const char * const status_messages[] =
{
    #include "back_statuses.h"
    "FICTIONAL MESSAGE!"
};
#undef DEF_STATUS


typedef Status (*tr_AST_to_IR_t)(FILE*,const Tree*,TreeNode*,Counters*);

const tr_AST_to_IR_t AST_OPS_BACKEND[] = 
{

};

Status IR_push_head( IR *IR, IRBlockData data );

Status IR_push_tail( IR *IR, IRBlockData data );

Status IR_insert_after( IR *IR, IRBlock *ref, IRBlockData data_to_insert );

Status IR_insert_before( IR *IR, IRBlock *ref, IRBlockData data_to_insert );

Status IR_pop_head( IR *IR );

Status IR_pop_tail( IR *IR );

//! @attention after this func 'block' is not a valid ptr!
Status IR_pop( IR *IR, IRBlock *block );


Status translate_AST_to_IR( const Tree *AST, IR* IR );

//! @brief Translates given node and subtree, which starts with this node, into IR.
Status translate_AST_node( const Tree *AST, IR *IR, const TreeNode *node, Counters cnts );


void print_status_message( FILE *stream, Status status );

int init_log( Config cfg );

#endif /* BACKEND_H */