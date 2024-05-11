#include "tr_AST_to_IR_funcs.h"
#include "backend.h"
#include "IR_interface.h"

#include <stdlib.h>

// DSL

#define FACT_TR_ASM_IR_ARGS AST, IR, node, counters, context

#define LAST_IR_BLOCK IR->tail

#define WRP(func__) do                      \
{                                           \
    Status stat__ = func__;                 \
    if (stat__ != STATUS_OK) return stat__; \
} while(0)

#define UNUSED(var) do{var = var;}while(0)

#define ASSERT_ALL()    \
do{                     \
    assert(AST);        \
    assert(IR);         \
    assert(node);       \
    assert(counters);   \
}while(0)

#define LEFT_CURR  (tree_get_left_child ( (node) ))
#define RIGHT_CURR (tree_get_right_child( (node) ))

#define LEFT( node__ )  (tree_get_left_child ( (node__) ))
#define RIGHT( node__ ) (tree_get_right_child( (node__) ))

#define TR_LEFT_CHILD_CURR() \
    WRP(translate_AST_node(AST, IR, LEFT_CURR, counters, context))

#define TR_RIGHT_CHILD_CURR() \
    WRP(translate_AST_node(AST, IR, RIGHT_CURR, counters, context))

#define TR_LEFT_CHILD_OF( node__ ) \
    WRP(translate_AST_node( AST, IR, LEFT( node__ ), counters, context))

#define TR_RIGHT_CHILD_OF( node__ ) \
    WRP(translate_AST_node( AST, IR, RIGHT( node__ ), counters, context))

#define TR_NODE( node__ ) \
    WRP(translate_AST_node( AST, IR, node__, counters, context))


#define GET_TYPE( node__ )  (get_node_data( (node__) ).type)
#define GET_ID( node__ )    (get_node_data( (node__) ).id)
#define GET_NUM( node__ )   (get_node_data( (node__) ).num)
#define GET_OP( node__ )    (get_node_data( (node__) ).op)
#define GET_STR( node__ )   (get_node_data( (node__) ).str)

#define COMMENT(comment__) \
do{                                     \
    IRBlockData data = {};              \
    data.type = IR_BLOCK_TYPE_DUMMY;    \
    data.comment = comment__;           \
    IR_push_tail(IR, data);             \
}while(0)

//! @brief Returns error if the type isn't consistent.
#define CHECK_NODE_TYPE(node__, needed_type__)      \
do{                                                 \
    if(GET_TYPE(node__) != (needed_type__)) \
        return STATUS_ERROR_WRONG_NODE_IN_AST;      \
}while(0)

#define IR_PUSH_TAIL(data__) WRP(IR_push_tail( IR, data__ ))
#define IR_PUSH_HEAD(data__) WRP(IR_push_head( IR, data__ ))

#define MAKE_LABEL( label__ ) \
    COMMENT("label " #label__ ":");                                                 \
    IRBlockData lbl_data_##label__ = form_IRBlockData_type( IR_BLOCK_TYPE_DUMMY );  \
    IR_PUSH_TAIL( lbl_data_##label__ );                                             \
    IRBlock *lbl_block_##label__ = LAST_IR_BLOCK;

inline size_t min( size_t a, size_t b )
{
    return (a < b) ? a : b;
}


Status tr_AST_to_IR_SEQ_EXEC (FORMAL_TR_ASM_IR_ARGS)
{
    ASSERT_ALL();

    TR_LEFT_CHILD_CURR();
    TR_RIGHT_CHILD_CURR();


    return STATUS_OK;
}

Status tr_AST_to_IR_DUMMY (FORMAL_TR_ASM_IR_ARGS)
{
    ASSERT_ALL();

    return STATUS_OK;
}

Status tr_AST_to_IR_FUNC_DEF (FORMAL_TR_ASM_IR_ARGS)
{
    ASSERT_ALL();


}

Status tr_AST_to_IR_FUNC_DEF_HELPER (FORMAL_TR_ASM_IR_ARGS)
{

}

Status tr_AST_to_IR_LIST_CONNECTOR (FORMAL_TR_ASM_IR_ARGS)
{

}

Status tr_AST_to_IR_MAIN_PROG (FORMAL_TR_ASM_IR_ARGS)
{

}

Status tr_AST_to_IR_ASSIGN (FORMAL_TR_ASM_IR_ARGS)
{
    ASSERT_ALL();

    COMMENT("assign_start");
    
    COMMENT("assign_expr");
    TR_LEFT_CHILD_CURR();

    CHECK_NODE_TYPE( RIGHT_CURR, TREE_NODE_TYPE_VAR_LOCAL || TREE_NODE_TYPE_FUNC_ARG );
    
    if ( GET_TYPE(node) == TREE_NODE_TYPE_VAR_LOCAL )
    {
        COMMENT("assign_pop_to_local_var");

        ident_t var_local_id = GET_ID(RIGHT_CURR);

        IRBlockData pop_data = form_IRBlockData_type( IR_BLOCK_TYPE_POP );
        size_t args_num_in_curr_frame = min( context->args_num, NUM_OF_XMM_REGS_TO_PASS_ARGS );
        pop_data.arg_dst = form_arg_t_mem( REG_rbp, (-1)*QWORD*( args_num_in_curr_frame + 1 + var_local_id ) );
        IR_PUSH_TAIL( pop_data );
    }
    else if ( GET_TYPE(node) == TREE_NODE_TYPE_FUNC_ARG )
    {
        COMMENT("assign_pop_to_func_arg");

        ident_t func_arg_id = GET_ID(RIGHT_CURR);
        
        IRBlockData pop_data = form_IRBlockData_type( IR_BLOCK_TYPE_POP );
        if ( func_arg_id < NUM_OF_XMM_REGS_TO_PASS_ARGS )
            pop_data.arg_dst = form_arg_t_mem( REG_rbp, (-1)*QWORD*(func_arg_id + 1) );
        else
            pop_data.arg_dst = form_arg_t_mem( REG_rbp, QWORD*(2 + func_arg_id - NUM_OF_XMM_REGS_TO_PASS_ARGS) );
        IR_PUSH_TAIL(pop_data);
    }

    COMMENT("assign_end");

    return STATUS_OK;
}

Status tr_AST_to_IR_CMP_MORE (FORMAL_TR_ASM_IR_ARGS)
{
    ASSERT_UNREACHEABLE(); // THIS NODE TYPE MUST BE HELD IN OTHER PLACE (IN)
    return STATUS_OK;
}

Status tr_AST_to_IR_CMP_LESS (FORMAL_TR_ASM_IR_ARGS)
{
    ASSERT_UNREACHEABLE(); // THIS NODE TYPE MUST BE HELD IN OTHER PLACE (IN)
    return STATUS_OK;
}

Status tr_AST_to_IR_CMP_MORE_EQ (FORMAL_TR_ASM_IR_ARGS)
{
    ASSERT_UNREACHEABLE(); // THIS NODE TYPE MUST BE HELD IN OTHER PLACE (IN)
    return STATUS_OK;
}

Status tr_AST_to_IR_CMP_LESS_EQ (FORMAL_TR_ASM_IR_ARGS)
{
    ASSERT_UNREACHEABLE(); // THIS NODE TYPE MUST BE HELD IN OTHER PLACE (IN)
    return STATUS_OK;
}

Status tr_AST_to_IR_CMP_EQUAL (FORMAL_TR_ASM_IR_ARGS)
{
    ASSERT_UNREACHEABLE(); // THIS NODE TYPE MUST BE HELD IN OTHER PLACE (IN)
    return STATUS_OK;
}

Status tr_AST_to_IR_CMP_NOT_EQ (FORMAL_TR_ASM_IR_ARGS)
{
    ASSERT_UNREACHEABLE(); // THIS NODE TYPE MUST BE HELD IN OTHER PLACE (IN)
    return STATUS_OK;
}

//! @brief Computes left child of curr_node, assuming it's an expression, then pops
//! its result in REG_XMM_TMP_1. Then does the same with right child and REG_XMM_TMP_2.
inline Status bi_arg_instr_helper(FORMAL_TR_ASM_IR_ARGS)
{
    COMMENT("computing left expr");
    TR_LEFT_CHILD_OF( LEFT_CURR );
    COMMENT("pop result to xmm_tmp_1");
    IRBlockData pop_data = form_IRBlockData_type( IR_BLOCK_TYPE_POP );
    pop_data.arg_dst = form_arg_t_reg_xmm( REG_XMM_TMP_1 );
    IR_PUSH_TAIL(pop_data);

    COMMENT("computing right expr");
    TR_RIGHT_CHILD_OF( LEFT_CURR );
    COMMENT("pop result to xmm_tmp_2");
    pop_data.arg_dst = form_arg_t_reg_xmm( REG_XMM_TMP_2 );
    IR_PUSH_TAIL(pop_data);
}

Status tr_AST_to_IR_ADD (FORMAL_TR_ASM_IR_ARGS)
{
    ASSERT_ALL();

    COMMENT("add start");

    WRP(bi_arg_instr_helper(FACT_TR_ASM_IR_ARGS));

    IRBlockData add_data = form_IRBlockData_type( IR_BLOCK_TYPE_ADDSD );
    add_data.arg1 = form_arg_t_reg_xmm( REG_XMM_TMP_1 );
    add_data.arg2 = form_arg_t_reg_xmm( REG_XMM_TMP_2 );

    COMMENT("push back onto comp. sub-stack");
    IRBlockData push_data = form_IRBlockData_type( IR_BLOCK_TYPE_PUSH );
    push_data.arg_src = form_arg_t_reg_xmm( REG_XMM_TMP_1 );
    IR_PUSH_TAIL(push_data);

    COMMENT("add end");

    return STATUS_OK;
}

Status tr_AST_to_IR_SUB (FORMAL_TR_ASM_IR_ARGS)
{
    ASSERT_ALL();
    COMMENT("sub start");

    WRP(bi_arg_instr_helper(FACT_TR_ASM_IR_ARGS));

    IRBlockData sub_data = form_IRBlockData_type( IR_BLOCK_TYPE_SUBSD );
    sub_data.arg1 = form_arg_t_reg_xmm( REG_XMM_TMP_1 );
    sub_data.arg2 = form_arg_t_reg_xmm( REG_XMM_TMP_2 );

    COMMENT("push back onto comp. sub-stack");
    IRBlockData push_data = form_IRBlockData_type( IR_BLOCK_TYPE_PUSH );
    push_data.arg_src = form_arg_t_reg_xmm( REG_XMM_TMP_1 );
    IR_PUSH_TAIL(push_data);

    COMMENT("sub end");
    return STATUS_OK;
}

Status tr_AST_to_IR_MUL (FORMAL_TR_ASM_IR_ARGS)
{
    ASSERT_ALL();
    COMMENT("mul start");

    WRP(bi_arg_instr_helper(FACT_TR_ASM_IR_ARGS));

    IRBlockData mul_data = form_IRBlockData_type( IR_BLOCK_TYPE_MULSD );
    mul_data.arg1 = form_arg_t_reg_xmm( REG_XMM_TMP_1 );
    mul_data.arg2 = form_arg_t_reg_xmm( REG_XMM_TMP_2 );

    COMMENT("push back onto comp. sub-stack");
    IRBlockData push_data = form_IRBlockData_type( IR_BLOCK_TYPE_PUSH );
    push_data.arg_src = form_arg_t_reg_xmm( REG_XMM_TMP_1 );
    IR_PUSH_TAIL(push_data);

    COMMENT("mul end");
    return STATUS_OK;
}

Status tr_AST_to_IR_DIV (FORMAL_TR_ASM_IR_ARGS)
{
    ASSERT_ALL();
    COMMENT("div start");

    WRP(bi_arg_instr_helper(FACT_TR_ASM_IR_ARGS));

    IRBlockData div_data = form_IRBlockData_type( IR_BLOCK_TYPE_DIVSD );
    div_data.arg1 = form_arg_t_reg_xmm( REG_XMM_TMP_1 );
    div_data.arg2 = form_arg_t_reg_xmm( REG_XMM_TMP_2 );

    COMMENT("push back onto comp. sub-stack");
    IRBlockData push_data = form_IRBlockData_type( IR_BLOCK_TYPE_PUSH );
    push_data.arg_src = form_arg_t_reg_xmm( REG_XMM_TMP_1 );
    IR_PUSH_TAIL(push_data);

    COMMENT("div end");
    return STATUS_OK;
}

//! @brief Translates given cmp type into corresponding 
//! jmp type (inside IRBlockData)
inline IRBlockData get_corr_jmp_data( ASTOpNameEnum cmp_type )
{
    IRBlockData data = {};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch-enum"
    switch (cmp_type)
    {
    case TREE_OP_CMP_EQUAL:
        data.type = IR_BLOCK_TYPE_JE;
        break;
    case TREE_OP_CMP_LESS:
        data.type = IR_BLOCK_TYPE_JB;
        break;
    case TREE_OP_CMP_LESS_EQ:
        data.type = IR_BLOCK_TYPE_JBE;
        break;
    case TREE_OP_CMP_MORE:
        data.type = IR_BLOCK_TYPE_JA;
        break;
    case TREE_OP_CMP_MORE_EQ:
        data.type = IR_BLOCK_TYPE_JAE;
        break;
    case TREE_OP_CMP_NOT_EQ:
        data.type = IR_BLOCK_TYPE_JNE;
        break;
    default:
        ASSERT_UNREACHEABLE();
        break;
    }
#pragma GCC diagnostic pop

    return data;
}

inline Status cmp_helper( FORMAL_TR_ASM_IR_ARGS )
{
    COMMENT("cmp helper start");
    WRP(bi_arg_instr_helper(FACT_TR_ASM_IR_ARGS));

    IRBlockData comisd_data = form_IRBlockData_type( IR_BLOCK_TYPE_COMISD );
    comisd_data.arg1 = form_arg_t_reg_xmm( REG_XMM_TMP_1 );
    comisd_data.arg2 = form_arg_t_reg_xmm( REG_XMM_TMP_2 );
    IR_PUSH_TAIL(comisd_data);

    COMMENT("cmp helper end");

    return STATUS_OK;
}

Status tr_AST_to_IR_IF (FORMAL_TR_ASM_IR_ARGS)
{
    ASSERT_ALL();

    COMMENT("if_start");

    WRP(cmp_helper( FACT_TR_ASM_IR_ARGS ));

    COMMENT("jump if_yes");
    CHECK_NODE_TYPE( LEFT_CURR, TREE_NODE_TYPE_OP );
    IRBlockData jmp_if_yes_data = get_corr_jmp_data( GET_OP( LEFT_CURR ) );
    IR_PUSH_TAIL( jmp_if_yes_data ); // filling it later
    IRBlock *jmp_if_yes_block = LAST_IR_BLOCK;

    TreeNode *subtree_if_main_body = NULL;
    if ( GET_TYPE( RIGHT_CURR ) == TREE_NODE_TYPE_OP && GET_OP( RIGHT_CURR ) == TREE_OP_ELSE )
    {
        subtree_if_main_body = LEFT( RIGHT_CURR );
        
        COMMENT("else branch:");
        TR_RIGHT_CHILD_OF( RIGHT_CURR );
    }
    else
    {
        subtree_if_main_body = RIGHT_CURR;
    }

    COMMENT("jump if_end:");
    IRBlockData jmp_if_end_data = form_IRBlockData_type( IR_BLOCK_TYPE_JMP );
    IR_PUSH_TAIL( jmp_if_end_data );
    IRBlock *jmp_if_end_block = LAST_IR_BLOCK; // filling it later

    MAKE_LABEL(if_yes);
    jmp_if_yes_block->data.instr_ptr = lbl_block_if_yes; // filling 'if_yes' label

    TR_NODE( subtree_if_main_body );

    MAKE_LABEL(if_end)
    jmp_if_end_block->data.instr_ptr = lbl_block_if_end; // filling 'if_end' label

    return STATUS_OK;
}

Status tr_AST_to_IR_WHILE (FORMAL_TR_ASM_IR_ARGS)
{
    ASSERT_ALL();

    MAKE_LABEL(while_start);

    WRP(cmp_helper( FACT_TR_ASM_IR_ARGS ));

    COMMENT("jmp while_body");
    CHECK_NODE_TYPE( LEFT_CURR, TREE_NODE_TYPE_OP );
    IRBlockData jmp_while_body_data = get_corr_jmp_data( GET_OP( LEFT_CURR ) );
    IR_PUSH_TAIL( jmp_while_body_data ); // filling it later
    IRBlock *jmp_while_body_block = LAST_IR_BLOCK;

    COMMENT("jmp while_end");
    IRBlockData jmp_while_end_data = form_IRBlockData_type( IR_BLOCK_TYPE_JMP );
    IR_PUSH_TAIL( jmp_while_end_data ); // filling it later
    IRBlock *jmp_while_end_block = LAST_IR_BLOCK; 

    MAKE_LABEL(while_body)
    jmp_while_body_block->data.instr_ptr = lbl_block_while_body;

    COMMENT("while body:");
    TR_RIGHT_CHILD_CURR();

    COMMENT("jmp while_start");
    IRBlockData jmp_while_start_data = form_IRBlockData_type( IR_BLOCK_TYPE_JMP );
    jmp_while_start_data.instr_ptr = lbl_block_while_start;
    IR_PUSH_TAIL( jmp_while_start_data );

    MAKE_LABEL(while_end)
    jmp_while_end_block->data.instr_ptr = lbl_block_while_end;

    return STATUS_OK;
}

Status tr_AST_to_IR_ELSE (FORMAL_TR_ASM_IR_ARGS)
{
    ASSERT_UNREACHEABLE();
    return STATUS_OK;
}



Status tr_AST_to_IR_SQRT (FORMAL_TR_ASM_IR_ARGS)
{
    ASSERT_ALL();

    COMMENT("sqrt start, computing sub-expr:");
    TR_RIGHT_CHILD_CURR();

    COMMENT("pop result to reg_xmm_tmp_1");
    IRBlockData pop_data = form_IRBlockData_type( IR_BLOCK_TYPE_POP );
    pop_data.arg_dst = form_arg_t_reg_xmm( REG_XMM_TMP_1 );
    IR_PUSH_TAIL(pop_data);

    IRBlockData sqrt_data = form_IRBlockData_type( IR_BLOCK_TYPE_SQRTSD );
    sqrt_data.arg_dst = form_arg_t_reg_xmm( REG_XMM_TMP_1 );
    sqrt_data.arg_src = form_arg_t_reg_xmm( REG_XMM_TMP_1 );
    IR_PUSH_TAIL(sqrt_data);

    COMMENT("push back onto comp. sub-stack");
    IRBlockData push_data = form_IRBlockData_type( IR_BLOCK_TYPE_PUSH );
    push_data.arg_src = form_arg_t_reg_xmm( REG_XMM_TMP_1 );
    IR_PUSH_TAIL(push_data);

    COMMENT("sqrt end");    

    return STATUS_OK;
}

Status tr_AST_to_IR_MINUS (FORMAL_TR_ASM_IR_ARGS)
{
    ASSERT_ALL();

    COMMENT("minus start, computing sub-expr:");
    TR_RIGHT_CHILD_CURR();

    COMMENT("pop result to reg_xmm_tmp_1");
    IRBlockData pop_data = form_IRBlockData_type( IR_BLOCK_TYPE_POP );
    pop_data.arg_dst = form_arg_t_reg_xmm( REG_XMM_TMP_1 );
    IR_PUSH_TAIL(pop_data);

    COMMENT("mulsd reg_xmm_tmp_1, [num_const_which_is_minus_one]");
    COMMENT("the mentioned const:");
    IRBlockData minus_one_data = form_IRBlockData_type( IR_BLOCK_TYPE_NUM_CONST );
    minus_one_data.num_const = -1;
    IR_PUSH_TAIL( minus_one_data );
    IRBlock *minus_one_block = LAST_IR_BLOCK;

    COMMENT("the mentioned mulsd:");
    IRBlockData mulsd_data = form_IRBlockData_type( IR_BLOCK_TYPE_MULSD );
    mulsd_data.arg1 = form_arg_t_reg_xmm( REG_XMM_TMP_1 );
    mulsd_data.arg2 = form_arg_t_mem_var( minus_one_block );
    IR_PUSH_TAIL(mulsd_data);

    COMMENT("push back onto comp. sub-stack");
    IRBlockData push_data = form_IRBlockData_type( IR_BLOCK_TYPE_PUSH );
    push_data.arg_src = form_arg_t_reg_xmm( REG_XMM_TMP_1 );
    IR_PUSH_TAIL(push_data);

    COMMENT("sqrt end"); 

    return STATUS_OK;
}



Status tr_AST_to_IR_CALL_FUNC (FORMAL_TR_ASM_IR_ARGS)
{

}

Status tr_AST_to_IR_RETURN (FORMAL_TR_ASM_IR_ARGS)
{

}

Status tr_AST_to_IR_INPUT (FORMAL_TR_ASM_IR_ARGS)
{
    ASSERT_ALL();

    COMMENT( "input start" );
    
    IRBlockData extern_keyword_data = form_IRBlockData_type( IR_BLOCK_TYPE_EXTERN_KW );
    extern_keyword_data.extern_func_name = STDLIB_FUNC_INPUT;
    IR_PUSH_TAIL(extern_keyword_data);

    IRBlockData call_data = form_IRBlockData_type( IR_BLOCK_TYPE_CALL );
    call_data.func_name = STDLIB_FUNC_INPUT;
    IR_PUSH_TAIL(call_data);

    COMMENT( "push from xmm0, in which func result is located" );
    IRBlockData push_data = form_IRBlockData_type( IR_BLOCK_TYPE_PUSH );
    push_data.arg_src = form_arg_t_reg_xmm( REG_xmm0 );
    IR_PUSH_TAIL(push_data);

    COMMENT( "input end" );

    return STATUS_OK;
}

Status tr_AST_to_IR_PRINT_NUM (FORMAL_TR_ASM_IR_ARGS)
{
    ASSERT_ALL();

    COMMENT("print num start");

    COMMENT("compute the argument:");
    TR_RIGHT_CHILD_CURR();

    COMMENT("pop to xmm0");
    IRBlockData pop_data = form_IRBlockData_type( IR_BLOCK_TYPE_POP );
    pop_data.arg_dst = form_arg_t_reg_xmm( REG_xmm0 );
    IR_PUSH_TAIL( pop_data );

    IRBlockData call_data = form_IRBlockData_type( IR_BLOCK_TYPE_CALL );
    call_data.func_name = STDLIB_FUNC_PRINT_NUM;
    IR_PUSH_TAIL(call_data);

    return STATUS_OK;
}

Status tr_AST_to_IR_PRINT_STR (FORMAL_TR_ASM_IR_ARGS)
{
    ASSERT_ALL();

    COMMENT("print_str start");

    CHECK_NODE_TYPE( RIGHT_CURR, TREE_NODE_TYPE_CONST_STR );

    IRBlockData str_const_data = form_IRBlockData_type( IR_BLOCK_TYPE_STR_CONST );
    str_const_data.str_const = GET_STR( RIGHT_CURR );
    IR_PUSH_TAIL( str_const_data );
    IRBlock *str_const_block = LAST_IR_BLOCK;

    COMMENT("mov *first common reg used to pass params*, str_ptr");
    IRBlockData mov_data = form_IRBlockData_type( IR_BLOCK_TYPE_MOV );
    mov_data.arg_dst = form_arg_t_reg( REGS_TO_PASS_PARAMS_TO_FUNCS[0] );
    mov_data.arg_src = form_arg_t_const_str_addr( str_const_block );
    IR_PUSH_TAIL( mov_data );

    IRBlockData call_data = form_IRBlockData_type( IR_BLOCK_TYPE_CALL );
    call_data.func_name = STDLIB_FUNC_PRINT_STR;
    IR_PUSH_TAIL(call_data);

    return STATUS_OK;
}