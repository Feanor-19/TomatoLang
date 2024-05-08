#include "tr_AST_to_IR_funcs.h"
#include "backend.h"
#include "IR_interface.h"

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


#define TR_LEFT_CHILD_CURR() \
    WRP(translate_AST_node(AST, IR, tree_get_left_child(node), counters))

#define TR_RIGHT_CHILD_CURR() \
    WRP(translate_AST_node(AST, IR, tree_get_left_child(node), counters))

#define LEFT_CURR  (tree_get_left_child ( (node) ))
#define RIGHT_CURR (tree_get_right_child( (node) ))

#define LEFT( node__ )  (tree_get_left_child ( (node__) ))
#define RIGHT( node__ ) (tree_get_right_child( (node__) ))

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



Status tr_AST_to_IR_SEQ_EXEC (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{
    ASSERT_ALL();

    TR_LEFT_CHILD_CURR();
    TR_RIGHT_CHILD_CURR();


    return STATUS_OK;
}

Status tr_AST_to_IR_DUMMY (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{
    ASSERT_ALL();

    return STATUS_OK;
}

Status tr_AST_to_IR_FUNC_DEF (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{
    ASSERT_ALL();


}

Status tr_AST_to_IR_FUNC_DEF_HELPER (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{

}

Status tr_AST_to_IR_LIST_CONNECTOR (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{

}

Status tr_AST_to_IR_MAIN_PROG (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{

}



Status tr_AST_to_IR_ASSIGN (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{
    ASSERT_ALL();

    COMMENT("assign_start");
    
    COMMENT("assign_expr");
    TR_LEFT_CHILD_CURR();

    COMMENT("assign_var");
    CHECK_NODE_TYPE( RIGHT_CURR, TREE_NODE_TYPE_VAR_LOCAL || TREE_NODE_TYPE_FUNC_ARG );
    
    if ( GET_TYPE(node) == TREE_NODE_TYPE_VAR_LOCAL )
    {
        ident_t var_local_id = GET_ID(RIGHT_CURR);
        // comp_pop to [rbp - 8*(var_local_id+1)]

        
    }
    else if ( GET_TYPE(node) == TREE_NODE_TYPE_FUNC_ARG )
    {

    }

    ASSERT_UNREACHEABLE();
    return STATUS_OK;
}

Status tr_AST_to_IR_CMP_MORE (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{

}

Status tr_AST_to_IR_CMP_LESS (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{

}

Status tr_AST_to_IR_CMP_MORE_EQ (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{

}

Status tr_AST_to_IR_CMP_LESS_EQ (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{

}

Status tr_AST_to_IR_CMP_EQUAL (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{

}

Status tr_AST_to_IR_CMP_NOT_EQ (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{

}



Status tr_AST_to_IR_ADD (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{

}

Status tr_AST_to_IR_SUB (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{

}

Status tr_AST_to_IR_MUL (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{

}

Status tr_AST_to_IR_DIV (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{

}



Status tr_AST_to_IR_IF (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{

}

Status tr_AST_to_IR_WHILE (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{

}

Status tr_AST_to_IR_ELSE (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{

}



Status tr_AST_to_IR_SQRT (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{

}

Status tr_AST_to_IR_MINUS (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{

}



Status tr_AST_to_IR_CALL_FUNC (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{

}

Status tr_AST_to_IR_RETURN (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{

}

Status tr_AST_to_IR_INPUT (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{

}

Status tr_AST_to_IR_PRINT_NUM (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{

}

Status tr_AST_to_IR_PRINT_STR (const Tree *AST, IR *IR, TreeNode *node, Counters *counters)
{

}