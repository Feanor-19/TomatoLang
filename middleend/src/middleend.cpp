#include "middleend.h"

Status opt_fold_consts(Tree *AST, TreeNode *node, bool *changes)
{
    assert(node);
    assert(changes);

    TreeNode *node_left = tree_get_left_child(node);
    TreeNode *node_right = tree_get_right_child(node);

    TreeNodeData node_data = get_node_data(node);
    if (node_data.type == TREE_NODE_TYPE_OP && node_data.op == TREE_OP_MUL)
    {

        if ( is_node_num(node_left, 0) || is_node_num(node_right, 0) )
        {
            TreeNodeData new_data = {};
            new_data.type = TREE_NODE_TYPE_CONST_NUM;
            new_data.num = 0;

            tree_delete_left_child(AST, node);
            tree_delete_right_child(AST, node);

            tree_change_data( AST, node, &new_data );

            *changes = true;

            return STATUS_OK;
        }
    }
    Status status = STATUS_OK;

    if (node_left)
        status = opt_fold_consts( AST, node_left, changes );
    
    if (node_right)
        status = opt_fold_consts( AST, node_right, changes );

    return status;
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
