#include "backend.h"
#include "IR_interface.h"

Status translate_AST_to_IR( const Tree *AST, IR* IR )
{
    assert(AST);
    assert(IR);

    Context context = {};
    return translate_AST_node_to_IR( AST, IR, tree_get_root(AST), &context );
}

Status translate_AST_node_to_IR( FORMAL_TR_ASM_IR_ARGS )
{
    assert(AST);
    assert(IR);
    assert(node);

    TreeNodeData data = get_node_data(node);
    switch (data.type)
    {
    case TREE_NODE_TYPE_OP:
        return AST_OPS_BACKEND[data.op](AST, IR, node, context);
        break;
    case TREE_NODE_TYPE_STR_IDENT:
        ASSERT_UNREACHEABLE();
        break;
    case TREE_NODE_TYPE_VAR_LOCAL:
    {
        IRBlockData push_loc_var_data = form_IRBlockData_type( IR_BLOCK_TYPE_PUSH );
        push_loc_var_data.arg_src = form_arg_t_mem_loc_var( get_node_data(node).id, context );
        IR_push_tail( IR, push_loc_var_data );
        break;
    }
    case TREE_NODE_TYPE_FUNC_ARG:
    {
        IRBlockData push_func_arg_data = form_IRBlockData_type( IR_BLOCK_TYPE_PUSH );
        push_func_arg_data.arg_src = form_arg_t_mem_func_arg( get_node_data(node).id );
        IR_push_tail( IR, push_func_arg_data );
        break;
    }
    case TREE_NODE_TYPE_CONST_NUM:
    {
        IRBlockData const_data = form_IRBlockData_type( IR_BLOCK_TYPE_NUM_CONST );
        const_data.num_const = get_node_data(node).num;
        IR_push_tail( IR, const_data );
        IRBlock *const_block = IR->tail;

        IRBlockData push_const_data = form_IRBlockData_type( IR_BLOCK_TYPE_PUSH );
        push_const_data.arg_src = form_arg_t_mem_var( const_block );
        IR_push_tail( IR, push_const_data );
        break;
    }
    case TREE_NODE_TYPE_CONST_STR:
        ASSERT_UNREACHEABLE();
        break;
    default:
        ASSERT_UNREACHEABLE();
        break;
    }

    return STATUS_OK;
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
