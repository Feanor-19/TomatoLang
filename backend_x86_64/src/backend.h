#ifndef BACKEND_H
#define BACKEND_H

#include "back_common.h"
#include "config_back.h"
#include "tr_AST_to_IR_funcs.h"
#include "tr_IR_to_NASM_funcs.h"

#define DEF_STATUS(name, message) message,
const char * const status_messages[] =
{
    #include "back_statuses.h"
    "FICTIONAL MESSAGE!"
};
#undef DEF_STATUS


typedef Status(*tr_AST_to_IR_t)(FORMAL_TR_ASM_IR_ARGS);

#define DEF_AST_OP(name) tr_AST_to_IR_##name,
const tr_AST_to_IR_t AST_OPS_BACKEND[] = 
{
    #include "ast_ops_defs.h"
    NULL
};
#undef DEF_AST_OP


typedef Status(*tr_IR_to_NASM_t)(FORMAL_TR_IR_NASM_ARGS);

#define DEF_IRBLOCK_TYPE(name) tr_IR_to_NASM_##name,
const tr_IR_to_NASM_t TR_IR_NASM_FUNCS[] = 
{
    #include "IRBlockType_defs.h"
    NULL
};
#undef DEF_IRBLOCK_TYPE


const size_t DEFAULT_NUM_CONSTS_ARR_SIZE = 10;


Status translate_AST_to_IR( const Tree *AST, IR *IR );

//! @brief Translates given node and subtree, which starts with this node, into IR.
Status translate_AST_node_to_IR( FORMAL_TR_ASM_IR_ARGS );

//! @brief Sets common label for each IRBlock, which is pointed at by some other block.
//! @note Pointer to another block (needing common label) is stored in the field 'instr_ptr'.
// Other types of labels aren't set this way.
void set_cmn_labels( const IR* IR );

//! @brief Changes IR, making some small optimizations (e.g. folding
//! sequantial (paired) 'push' and 'pop' into one 'mov' (if possible)).
Status optimize_IR( IR *IR );

//! @brief Unfolds 'unrealistic' functions into combinations of realistic ones.
//! @example push xmm_reg -> { sub rsp, QWORD; mov [rsp], xmm_reg }
Status make_IR_realistic( IR *IR );

Status translate_IR_to_NASM( const IR *IR, const char *output_filename );

void print_status_message( FILE *stream, Status status );

int init_log( Config cfg );

#endif /* BACKEND_H */