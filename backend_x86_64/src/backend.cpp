#include "backend.h"

inline IRBlock *alloc_new_IRBlock(IR *IR)
{
    IRBlock *new_IRBlock = (IRBlock *) calloc(1, sizeof( IRBlock ));
    if (new_IRBlock)
        IR->blocks_count++;
    
    return new_IRBlock;
}

inline void free_IRBlock(IR *IR, IRBlock *block)
{
    free(block);
    IR->blocks_count--;
}

Status IR_push_head( IR *IR, IRBlockData data )
{
    assert(IR);

    IRBlock *new_block = alloc_new_IRBlock(IR);
    if( !new_block )
        return STATUS_ERROR_MEMORY_ALLOC_ERROR;

    new_block->data = data;
    new_block->next = IR->head;
    new_block->prev = NULL;

    IR->head = new_block;

    if (IR->blocks_count == 1)
        IR->tail = new_block;

    return STATUS_OK;
}

Status IR_push_tail( IR *IR, IRBlockData data )
{
    assert(IR);
    
    IRBlock *new_block = alloc_new_IRBlock(IR);
    if( !new_block )
        return STATUS_ERROR_MEMORY_ALLOC_ERROR;

    new_block->data = data;
    new_block->next = NULL;
    new_block->prev = IR->tail;

    IR->tail = new_block;

    if (IR->blocks_count == 1)
        IR->head = new_block;

    return STATUS_OK;
}

Status IR_insert_after( IR *IR, IRBlock *ref, IRBlockData data_to_insert )
{
    assert(IR);
    assert(ref);

    IRBlock *new_block = alloc_new_IRBlock(IR);
    if( !new_block )
        return STATUS_ERROR_MEMORY_ALLOC_ERROR;

    new_block->data = data_to_insert;

    IRBlock *tmp = ref->next;
    ref->next = new_block;
    tmp->prev = new_block;

    new_block->prev = ref;
    new_block->next = tmp;

    return STATUS_OK;
}

Status IR_insert_before( IR *IR, IRBlock *ref, IRBlockData data_to_insert )
{
    assert(IR);
    assert(ref);

    IRBlock *new_block = alloc_new_IRBlock(IR);
    if( !new_block )
        return STATUS_ERROR_MEMORY_ALLOC_ERROR;

    new_block->data = data_to_insert;

    IRBlock *tmp = ref->prev;
    ref->prev = new_block;
    tmp->next = new_block;

    new_block->next = ref;
    new_block->prev = tmp;

    return STATUS_OK;
}

Status IR_pop_head( IR *IR )
{
    assert(IR);

    IRBlock *old_head = IR->head;
    if (!old_head)
        return STATUS_ERROR_POP_NON_EXISTING_IR_ELEM;

    IR->head = old_head->next;
    free_IRBlock(IR, old_head);

    if (IR->blocks_count == 0)
        IR->tail = NULL;

    return STATUS_OK;
}

Status IR_pop_tail( IR *IR )
{
    assert(IR);

    IRBlock *old_tail = IR->tail;
    if (!old_tail)
        return STATUS_ERROR_POP_NON_EXISTING_IR_ELEM;

    IR->tail = old_tail->prev;
    free_IRBlock(IR, old_tail);

    if (IR->blocks_count == 0)
        IR->head = NULL;

    return STATUS_OK;
}

Status IR_pop( IR *IR, IRBlock *block )
{
    assert(IR);
    assert(block);

    if      ( IR->head == block )
        return IR_pop_head(IR);
    else if ( IR->tail == block )
        return IR_pop_tail(IR);

    block->prev->next = block->next;
    block->next->prev = block->prev;

    free_IRBlock(IR, block);

    return STATUS_OK;
}


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
