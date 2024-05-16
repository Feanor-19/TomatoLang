#include "middleend.h"

Status opt_fold_consts(Tree *AST, TreeNode *node, bool *changes)
{
    assert(node);
    assert(changes);

    TreeNodeData node_data = get_node_data(node);
    if (node_data.type == TREE_NODE_TYPE_OP && node_data.op == TREE_OP_MUL)
    {
        TreeNode *node_left = tree_get_left_child(node);
        TreeNode *node_right = tree_get_right_child(node);
    }
}

Status optimize_AST(Tree *AST)
{
    assert(AST);
    Status status = STATUS_OK;

    bool changes = false;
    do
    {
        changes = false;
        status = opt_fold_consts(AST, tree_get_root(AST), &changes);
        if (status != STATUS_OK)
            break;
    } while (changes);
    
    return status;
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
