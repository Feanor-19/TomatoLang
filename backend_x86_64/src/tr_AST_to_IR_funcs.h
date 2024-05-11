#ifndef TR_AST_TO_IR_FUNCS
#define TR_AST_TO_IR_FUNCS

#include "back_common.h"
#include "IR_interface.h"

#define FORMAL_TR_ASM_IR_ARGS const Tree *AST, IR *IR, TreeNode *node, Context *context

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"

#define DEF_AST_OP(name) Status tr_AST_to_IR_##name (FORMAL_TR_ASM_IR_ARGS);
#include "ast_ops_defs.h"
#undef DEF_AST_OP

#pragma GCC diagnostic pop

inline arg_t form_arg_t_mem_loc_var( ident_t var_local_id, Context *context )
{
    size_t args_num_in_curr_frame = min( context->args_num, NUM_OF_XMM_REGS_TO_PASS_ARGS );
    return form_arg_t_mem( REG_rbp, (-1)*QWORD*( (disp_t) args_num_in_curr_frame + 1 + (disp_t) var_local_id ) );
}

inline arg_t form_arg_t_mem_func_arg( ident_t func_arg_id )
{
    if ( (size_t) func_arg_id < NUM_OF_XMM_REGS_TO_PASS_ARGS )
        return form_arg_t_mem( REG_rbp, (-1)*QWORD*((disp_t) func_arg_id + 1) );
    else
        return form_arg_t_mem( REG_rbp, QWORD*(2 + (disp_t) func_arg_id - (disp_t) NUM_OF_XMM_REGS_TO_PASS_ARGS) );
}

#endif /* TR_AST_TO_IR_FUNCS */