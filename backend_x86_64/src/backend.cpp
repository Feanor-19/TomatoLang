#include "backend.h"
#include "IR_interface.h"

Status translate_AST_to_IR( Tree *AST, IR* IR )
{
    assert(AST);
    assert(IR);


}

Status translate_AST_node( FORMAL_TR_ASM_IR_ARGS )
{
    assert(AST);
    assert(IR);
    assert(node);

    TreeNodeData data = get_node_data(node);
    switch (data.type)
    {
    case TREE_NODE_TYPE_OP:
        return AST_OPS_BACKEND[data.op](AST, IR, node, counters, context);
        break;
    case TREE_NODE_TYPE_STR_IDENT:
        ASSERT_UNREACHEABLE();
        break;
    case TREE_NODE_TYPE_VAR_LOCAL:
        
        break;
    case TREE_NODE_TYPE_FUNC_ARG:
        
        break;
    case TREE_NODE_TYPE_CONST_NUM:

        break;
    case TREE_NODE_TYPE_CONST_STR:

        break;
    default:
        ASSERT_UNREACHEABLE();
        break;
    }

    ASSERT_UNREACHEABLE();
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
