#include "backend.h"

Status IR_push_head( IR *IR, IRBlock *block )
{
    assert(IR);
    assert(block);
}

Status IR_push_tail( IR *IR, IRBlock *block )
{
    assert(IR);
    assert(block);
}

Status IR_insert_after( IR *IR, IRBlock *ref, IRBlock *block_to_insert )
{
    assert(IR);
    assert(block_to_insert);
    assert(ref);
}

Status IR_insert_before( IR *IR, IRBlock *ref, IRBlock *block_to_insert )
{
    assert(IR);
    assert(block_to_insert);
    assert(ref);
}

Status IR_pop_head( IR *IR )
{
    assert(IR);
}

Status IR_pop_tail( IR *IR )
{
    assert(IR);
}

//! @attention after this func 'block' is not a valid ptr!
Status IR_pop( IR *IR, IRBlock *block );


Status translate_AST_to_IR( Tree *AST, IR* IR )
{
    assert(AST);
    assert(IR);


}

Status translate_AST_node( const Tree *AST, IR* IR, const TreeNode* node, Counters cnts )
{
    assert(AST);
    assert(IR);
    assert(node);
    assert(cnts);


}

void print_status_message( FILE *stream, Status status )
{
    fprintf(stream, "%s", status_messages[status]);
}

int init_log( Config cfg )
{
    if (cfg.log_file_name)
    {
        if (!logger_init_log( cfg.log_file_name ))
        {
            return 0;
        }
    }
    else
    {
        if (!logger_init_log( stdout ))
        {
            return 0;
        }
    }

    return 1;
}
