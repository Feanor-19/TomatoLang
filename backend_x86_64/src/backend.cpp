#include "backend.h"
#include "IR_interface.h"
#include "make_real_IR_funcs.h"

Status translate_AST_to_IR( const Tree *AST, IR* IR )
{
    assert(AST);
    assert(IR);

    Context context = {};
    return translate_AST_node_to_IR( AST, IR, tree_get_root(AST), &context );
}

//! @brief Finds IRBlock of type 'NUM_CONST' with specified 'num'.
//! If no block is found, returns NULL. 
inline IRBlock *find_in_IR_num_const_block( const IR *IR, num_t num )
{
    assert(IR);

    IRBlock *curr_block = IR->head;
    while (curr_block)
    {
        IRBlockData curr_data = curr_block->data;
        if (curr_data.type == IR_BLOCK_TYPE_NUM_CONST && are_num_t_identical(curr_data.num_const, num))
            return curr_block;

        curr_block = curr_block->next;
    }
    return NULL;
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
        num_t num = get_node_data(node).num;

        // check whether needed const num block has already been created
        IRBlock *const_block = find_in_IR_num_const_block( IR, num );
        if ( !const_block )
        {
            // nope, creating a new one 
            IRBlockData const_data = form_IRBlockData_type( IR_BLOCK_TYPE_NUM_CONST );
            const_data.num_const = num;
            IR_push_tail( IR, const_data );
            const_block = IR->tail;
        }

        IRBlockData push_const_data = form_IRBlockData_type( IR_BLOCK_TYPE_PUSH );
        push_const_data.arg_src = form_arg_t_mem_num_cnst( const_block );
        IR_push_tail( IR, push_const_data );
        break;
    }
    case TREE_NODE_TYPE_CONST_STR:
    case TREE_NODE_TYPE_FUNC_INFO:
        ASSERT_UNREACHEABLE();
        break;
    default:
        ASSERT_UNREACHEABLE();
        break;
    }

    return STATUS_OK;
}

// //! @brief Helper func for 'optimize_num_consts'. Finds index of an elem in
// //! 'num_const_arr' with the given 'num' and returns it. If not found, returns -1.
// inline int64_t opt_num_consts_find(IRBlock *num_const_arr[], size_t num_const_arr_curr_len, num_t num)
// {
//     for (size_t ind = 0; ind < num_const_arr_curr_len; ind++)
//     {
//         if (num_const_arr[ind]->data.num_const == num)
//             return ind;
//     }
//     return -1;
// } 

// //! @brief Merges identical num consts into one.
// inline Status optimize_num_consts(IR *IR)
// {
//     assert(IR);

//     //! @brief We will store here ptrs to all unique IRBlocks which has arg 'NUM_CONST'
//     IRBlock **num_const_arr = (IRBlock**) calloc( DEFAULT_NUM_CONSTS_ARR_SIZE, sizeof(IRBlock*) );
//     size_t num_const_arr_cap = DEFAULT_NUM_CONSTS_ARR_SIZE;
//     size_t num_const_arr_curr_len = 0;

//     IRBlock *curr_block = IR->head;
//     while (curr_block)
//     {
//         IRBlockData curr_data = curr_block->data;
//         if (curr_data.type == IRB_ARG_TYPE_MEM_NUM_CNST)
//         {
//             int64_t ind = opt_num_consts_find( num_const_arr, num_const_arr_curr_len, curr_data.num_const );
//             if ( ind == -1 )
//             {
//                 // this is a new const, adding to the arr

//                 num_const_arr[num_const_arr_curr_len++] = curr_block;
//             }
//         }
//     }
// }

Status optimize_IR( IR *IR )
{
    assert(IR);


    return STATUS_OK;
}

//! @brief Helper func for 'make_IR_realistic'. Returns ptr to next
//! block, which may need to be converted.
inline IRBlock *make_IRBlock_realistic(IR *IR, IRBlock *block)
{
    assert(IR);
    assert(block);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch-enum"
    switch (block->data.type)
    {
    case IR_BLOCK_TYPE_PUSH:
    {
        if      (block->data.arg_src.type == IRB_ARG_TYPE_REG_XMM)
            return hlp_push_xmm(IR, block);
        break;
    }
    case IR_BLOCK_TYPE_POP:
    {
        if (block->data.arg_dst.type == IRB_ARG_TYPE_REG_XMM)
            return hlp_pop_xmm(IR, block);
        break;
    }
    default:
        break;
    }
#pragma GCC diagnostic pop

    return block->next;
}

Status make_IR_realistic( IR *IR )
{
    assert(IR);

    IRBlock *curr_block = IR->head;
    while (curr_block)
    {
        curr_block = make_IRBlock_realistic(IR, curr_block);
    }

    return STATUS_OK;
}


//! @brief Prints some header lines, 
inline Status print_nasm_header( FILE *stream )
{
    assert(stream);

    PRINT("default rel");
    PRINT("section .text"); 

    return STATUS_OK;
}

//! @brief Sets common label for each IRBlock, which is pointed at by some other block.
//! @note Pointer to another block (needing common label) is stored in the field 'instr_ptr'.
// Other types of labels aren't set this way.
inline void set_cmn_labels( const IR* IR, Counters *counters )
{
    assert(IR);
    assert(counters);

    IRBlock *curr_block = IR->head;
    while (curr_block)
    {
        IRBlock *target = (IRBlock*) curr_block->data.instr_ptr; 
        if (target)
        {
            target->lbl_cmn_set = true;
            target->lbl_cmn = counters->lbl_cmn++;
        }   

        curr_block = curr_block->next;
    }
}

Status translate_IR_to_NASM( const IR* IR, const char *output_filename )
{
    assert(IR);
    assert(output_filename);

    FILE *stream = fopen( output_filename, "w" );
    if (!stream)
        return STATUS_ERROR_CANT_OPEN_OUTPUT_FILE;

    print_nasm_header(stream);

    Counters counters = {};
    set_cmn_labels(IR, &counters);

    IRBlock *curr_block = IR->head;
    while( curr_block )
    {
        if(curr_block->lbl_cmn_set)
            PRINT("LCC_%lu:", curr_block->lbl_cmn);

        IRBlockType type = curr_block->data.type;
        TR_IR_NASM_FUNCS[ type ]( curr_block, stream, &counters );
        curr_block = curr_block->next;
    }

    fclose(stream);
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
