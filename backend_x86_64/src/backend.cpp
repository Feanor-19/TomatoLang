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

inline bool is_IRB_ARG_mem_type( IRBlockArgType arg_type )
{
    return arg_type == IRB_ARG_TYPE_CONST_STR_ADDR
        || arg_type == IRB_ARG_TYPE_MEM
        || arg_type == IRB_ARG_TYPE_MEM_NUM_CNST;
}

inline IRBlock* opt_seq_push_pop_hlp( IR *IR, IRBlock *push_block )
{
    assert(IR);
    assert(push_block);

    IRBlock *pop_block = push_block->next;

    IRBlockData push_data = push_block->data;
    IRBlockData pop_data = pop_block->data;

    if ( pop_block->lbl_cmn_set )
        return pop_block->next; // optimization can't be done

    IRBlock *first_inserted_block = NULL;
    IRBlock *last_inserted_block = NULL;
    if ( is_IRB_ARG_mem_type(push_data.arg_src.type) && is_IRB_ARG_mem_type(pop_data.arg_dst.type) )
    {
        // mov some_reg, arg_src
        // mov arg_dst, some_reg

        IRBlockData mov_to_reg = form_IRBlockData_type( IR_BLOCK_TYPE_MOV );
        mov_to_reg.arg_dst = form_arg_t_reg( REG_TMP_1 );
        mov_to_reg.arg_src = push_data.arg_src;
        IR_insert_after( IR, pop_block, mov_to_reg );
        
        first_inserted_block = pop_block->next;

        IRBlockData mov_from_reg = form_IRBlockData_type(IR_BLOCK_TYPE_MOV);
        mov_from_reg.arg_dst = pop_data.arg_dst;
        mov_from_reg.arg_src = form_arg_t_reg( REG_TMP_1 );
        IR_insert_after( IR, first_inserted_block, mov_from_reg );

        last_inserted_block = first_inserted_block->next;
    }
    else
    {
        // mov arg_dst, arg_src

        IRBlockData mov_data = form_IRBlockData_type( IR_BLOCK_TYPE_MOV );
        mov_data.arg_dst = pop_data.arg_dst;
        mov_data.arg_src = push_data.arg_src;
        IR_insert_after(IR, pop_block, mov_data);

        first_inserted_block = pop_block->next;

        last_inserted_block = first_inserted_block;
    }

    if ( push_block->lbl_cmn_set )
    {
        first_inserted_block->lbl_cmn_set = true;
        first_inserted_block->lbl_cmn = push_block->lbl_cmn;
    }

        IR_pop(IR, push_block);
        IR_pop(IR, pop_block);

    return last_inserted_block;
}

//! @brief Optimizes each pair of sequential ('push', 'pop') with
//! identical 'arg_src' and 'arg_dst' into one 'mov'. 
//! @note Exception: if both 'arg_src' and 'arg_dst' are of type 'mem',
//! the arg is moved through some srcatch reg.  
inline void optimize_seq_push_pop( IR *IR )
{
    assert(IR);
    
    IRBlock *curr_block = IR->head;
    while (curr_block->next)
    {
        IRBlockData curr_data = curr_block->data;
        IRBlockData next_data = curr_block->next->data;

        if (curr_data.type == IR_BLOCK_TYPE_PUSH && next_data.type == IR_BLOCK_TYPE_POP)
        {
            curr_block = opt_seq_push_pop_hlp( IR, curr_block );
        }
        else
        {
            curr_block = curr_block->next;
        }
    }
}

Status optimize_IR( IR *IR )
{
    assert(IR);

    optimize_seq_push_pop(IR);

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
void set_cmn_labels( const IR* IR )
{
    assert(IR);

    size_t lbl_cmn = 0;

    IRBlock *curr_block = IR->head;
    while (curr_block)
    {
        IRBlock *target = (IRBlock*) curr_block->data.instr_ptr; 
        if (target)
        {
            target->lbl_cmn_set = true;
            target->lbl_cmn = lbl_cmn++;
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
