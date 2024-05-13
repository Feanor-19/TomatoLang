#ifndef MAKE_REAL_IR_FUNCS_H
#define MAKE_REAL_IR_FUNCS_H

#include "IR_interface.h"
#include "back_common.h"

inline IRBlock *hlp_push_xmm(IR *IR, IRBlock *block)
{
    assert(IR);
    assert(block);

    // sub rsp, QWORD_SIZE
    IRBlockData sub_rsp_data = form_IRBlockData_type( IR_BLOCK_TYPE_SUB );
    sub_rsp_data.arg1 = form_arg_t_reg( REG_rsp );
    sub_rsp_data.arg2 = form_arg_t_imm_const( QWORD );
    IR_insert_after( IR, block, sub_rsp_data );

    if ( block->lbl_cmn_set )
    {
        IR->tail->lbl_cmn_set = true;
        IR->tail->lbl_cmn = block->lbl_cmn;
    }

    // mov [rsp], reg_xmm
    IRBlockData mov_data = form_IRBlockData_type( IR_BLOCK_TYPE_MOV );
    mov_data.arg_dst = form_arg_t_mem( REG_rsp, 0 );
    mov_data.arg_src = block->data.arg_src;
    IR_insert_after( IR, block->next, mov_data );

    IRBlock *last_added_block = block->next->next;

    IR_pop( IR, block );

    return last_added_block->next;
}

inline IRBlock *hlp_pop_xmm(IR *IR, IRBlock *block)
{
    assert(IR);
    assert(block);

    // mov reg_xmm, [rsp]
    IRBlockData mov_data = form_IRBlockData_type( IR_BLOCK_TYPE_MOV );
    mov_data.arg_dst = block->data.arg_dst;
    mov_data.arg_src = form_arg_t_mem( REG_rsp, 0 );
    IR_insert_after( IR, block, mov_data );

    if ( block->lbl_cmn_set )
    {
        IR->tail->lbl_cmn_set = true;
        IR->tail->lbl_cmn = block->lbl_cmn;
    }

    // add rsp, QWORD_SIZE
    IRBlockData add_data = form_IRBlockData_type( IR_BLOCK_TYPE_ADD );
    add_data.arg1 = form_arg_t_reg( REG_rsp );
    add_data.arg2 = form_arg_t_imm_const( QWORD );
    IR_insert_after( IR, block->next, add_data );

    IRBlock *last_added_block = block->next->next;

    IR_pop(IR, block);

    return last_added_block->next;
}

#endif /* MAKE_REAL_IR_FUNCS_H */