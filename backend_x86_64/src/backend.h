#ifndef BACKEND_H
#define BACKEND_H

#include "common.h"
#include "config_back.h"


#define DEF_STATUS(name, msg) STATUS_##name,
enum Status
{
    #include "back_statuses.h"
};
#undef DEF_STATUS

#define DEF_STATUS(name, message) message,
const char * const status_messages[] =
{
    #include "back_statuses.h"
    "FICTIONAL MESSAGE!"
};
#undef DEF_STATUS


enum IRBlockType
{
    IR_BLOCK_TYPE_DUMMY,
    
};

//! @brief Block of IR (see below).
struct IRBlock
{
    IRBlockType type = IR_BLOCK_TYPE_DUMMY;

    IRBlock *next = NULL;
    IRBlock *prev = NULL;
};

//! @brief Intermediate representation.
//! @details Double-linked list of blocks, each of them represents
//! an instruction from 'abstract assembler'.
struct IR
{
    IRBlock *head = NULL;
    IRBlock *tail = NULL;

    size_t blocks_count = 0;
};

struct Counters
{
    // cnt_t cmp_c   = 0;
    // cnt_t if_c    = 0;
    // cnt_t while_c = 0;
    // cnt_t and_c   = 0;
    // cnt_t or_c    = 0;
    // cnt_t not_c   = 0;
};


Status IR_push_head( IR *IR, IRBlock *block );

Status IR_push_tail( IR *IR, IRBlock *block );

Status IR_insert_after( IR *IR, IRBlock *ref, IRBlock *block_to_insert );

Status IR_insert_before( IR *IR, IRBlock *ref, IRBlock *block_to_insert );

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