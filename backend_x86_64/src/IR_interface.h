#ifndef IR_INTERFACE
#define IR_INTERFACE

#include "back_common.h"

#include <assert.h>
#include <stdlib.h>

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

inline void IR_dtor(IR *IR)
{
    assert(IR);

    IRBlock *curr_block = IR->head;
    while (curr_block)
    {
        IRBlock *next_block = curr_block->next;
        free(curr_block);
        curr_block = next_block;
    }
}

inline Status IR_push_head( IR *IR, IRBlockData data )
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

inline Status IR_push_tail( IR *IR, IRBlockData data )
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

inline Status IR_insert_after( IR *IR, IRBlock *ref, IRBlockData data_to_insert )
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

inline Status IR_insert_before( IR *IR, IRBlock *ref, IRBlockData data_to_insert )
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

inline Status IR_pop_head( IR *IR )
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

inline Status IR_pop_tail( IR *IR )
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

//! @attention after this func 'block' is not a valid ptr!
inline Status IR_pop( IR *IR, IRBlock *block )
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

inline IRBlockData form_IRBlockData_type( IRBlockType type )
{
    IRBlockData data = {};

    data.type      = type;
    
    return data;
}

inline arg_t form_arg_t_reg( reg_t reg )
{
    arg_t arg = {};
    arg.type = IRB_ARG_TYPE_REG;
    arg.reg = reg;
    return arg;
}

inline arg_t form_arg_t_reg_xmm( reg_xmm_t reg_xmm )
{
    arg_t arg = {};
    arg.type = IRB_ARG_TYPE_REG_XMM;
    arg.reg_xmm = reg_xmm;
    return arg;
}

inline arg_t form_arg_t_mem( reg_t base_reg, disp_t disp, 
                             reg_t index_reg = REG_DUMMY, MemScaleFactor scale = SCALE_FACTOR_0 )
{
    mem_t mem = {};

    mem.base_reg    = base_reg;
    mem.index_reg   = index_reg;
    mem.scale       = scale;
    mem.disp        = disp;

    arg_t arg = {};
    arg.type = IRB_ARG_TYPE_MEM;
    arg.mem = mem;

    return arg;
}

inline arg_t form_arg_t_imm_const( int64_t imm_const )
{
    arg_t arg = {};
    arg.type = IRB_ARG_TYPE_IMM_CONST;
    arg.imm_const = imm_const;
    return arg;
}

inline arg_t form_arg_t_mem_var( IRBlock *mem_var )
{
    arg_t arg = {};
    arg.type = IRB_ARG_TYPE_MEM_VAR;
    arg.mem_var = mem_var;
    return arg;
}

inline arg_t form_arg_t_const_str_addr( IRBlock *const_str_addr )
{
    arg_t arg = {};
    arg.type = IRB_ARG_TYPE_CONST_STR_ADDR;
    arg.addr = const_str_addr;
    return arg;
}

#endif /* IR_INTERFACE */