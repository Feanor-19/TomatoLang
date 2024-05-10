#include "tr_AST_to_IR_funcs.h"
#include "backend.h"
#include "IR_interface.h"

#include <stdlib.h>

// DSL

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

#define IR_PUSH_TAIL(data__)                        \
do{                                                 \
    Status status = IR_push_tail( IR, data__ );     \
    if (status != STATUS_OK)                        \
        return status;                              \
} while(0)

#define IR_PUSH_HEAD(data__)                        \
do{                                                 \
    Status status = IR_push_head( IR, data__ );     \
    if (status != STATUS_OK)                        \
        return status;                              \
} while(0)


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

        IRBlockData pop_data = form_IRBlockData_type( IR_BLOCK_TYPE_POP, IR_BLOCK_DATA_ARGS_DIR );
        size_t args_num_in_curr_frame = min( context->args_num, NUM_OF_XMM_REGS_TO_PASS_ARGS );
        pop_data.arg_dst.mem = form_mem_t( REG_rbp, (-1)*QWORD*( args_num_in_curr_frame + 1 + var_local_id ) );
        IR_PUSH_TAIL( pop_data );
    }
    else if ( GET_TYPE(node) == TREE_NODE_TYPE_FUNC_ARG )
    {
        COMMENT("assign_pop_to_func_arg");

        ident_t func_arg_id = GET_ID(RIGHT_CURR);
        
        IRBlockData pop_data = form_IRBlockData_type( IR_BLOCK_TYPE_POP, IR_BLOCK_DATA_ARGS_DIR );
        if ( func_arg_id < NUM_OF_XMM_REGS_TO_PASS_ARGS )
            pop_data.arg_dst.mem = form_mem_t( REG_rbp, (-1)*QWORD*(func_arg_id + 1) );
        else
            pop_data.arg_dst.mem = form_mem_t( REG_rbp, QWORD*(2 + func_arg_id - NUM_OF_XMM_REGS_TO_PASS_ARGS) );
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



Status tr_AST_to_IR_ADD (FORMAL_TR_ASM_IR_ARGS)
{

}

Status tr_AST_to_IR_SUB (FORMAL_TR_ASM_IR_ARGS)
{

}

Status tr_AST_to_IR_MUL (FORMAL_TR_ASM_IR_ARGS)
{

}

Status tr_AST_to_IR_DIV (FORMAL_TR_ASM_IR_ARGS)
{

}

//! @brief Translates given cmp type into corresponding 
//! jmp type (inside IRBlockData)
inline IRBlockData get_corr_jmp_data( ASTOpNameEnum cmp_type )
{
    IRBlockData data = {};
    data.data_type = IR_BLOCK_DATA_INSTR_PTR;
    switch (cmp_type)
    {
    case TREE_OP_CMP_EQUAL:
        data.type = IR_BLOCK_TYPE_JE;
        break;
    
    default:
        ASSERT_UNREACHEABLE();
        break;
    }

    return data;
}

Status tr_AST_to_IR_IF (FORMAL_TR_ASM_IR_ARGS)
{
    ASSERT_ALL();

    COMMENT("if_start");

    COMMENT("computing left cmp expr");
    TR_LEFT_CHILD_OF( LEFT_CURR );
    IRBlockData pop_data = form_IRBlockData_type( IR_BLOCK_TYPE_POP, IR_BLOCK_DATA_ARGS_DIR );
    pop_data.arg_dst.reg_xmm = REG_XMM_TMP_1;
    IR_PUSH_TAIL(pop_data);

    COMMENT("computing right cmp expr");
    TR_RIGHT_CHILD_OF( LEFT_CURR );
    pop_data.arg_dst.reg_xmm = REG_XMM_TMP_2;
    IR_PUSH_TAIL(pop_data);

    IRBlockData comisd_data = form_IRBlockData_type( IR_BLOCK_TYPE_COMISD, IR_BLOCK_DATA_ARGS_NUM );
    comisd_data.arg1.reg_xmm = REG_XMM_TMP_1;
    comisd_data.arg2.reg_xmm = REG_XMM_TMP_2;
    IR_PUSH_TAIL(comisd_data);

    IRBlockData jmp_data =;


    COMMENT("if_end");
    return STATUS_OK;
}

Status tr_AST_to_IR_WHILE (FORMAL_TR_ASM_IR_ARGS)
{

}

Status tr_AST_to_IR_ELSE (FORMAL_TR_ASM_IR_ARGS)
{

}



Status tr_AST_to_IR_SQRT (FORMAL_TR_ASM_IR_ARGS)
{

}

Status tr_AST_to_IR_MINUS (FORMAL_TR_ASM_IR_ARGS)
{

}



Status tr_AST_to_IR_CALL_FUNC (FORMAL_TR_ASM_IR_ARGS)
{

}

Status tr_AST_to_IR_RETURN (FORMAL_TR_ASM_IR_ARGS)
{

}

Status tr_AST_to_IR_INPUT (FORMAL_TR_ASM_IR_ARGS)
{

}

Status tr_AST_to_IR_PRINT_NUM (FORMAL_TR_ASM_IR_ARGS)
{

}

Status tr_AST_to_IR_PRINT_STR (FORMAL_TR_ASM_IR_ARGS)
{

}