#ifndef TR_AST_TO_IR_FUNCS
#define TR_AST_TO_IR_FUNCS

#include "back_common.h"

#define FORMAL_TR_ASM_IR_ARGS const Tree *AST, IR *IR, TreeNode *node, \
                                Counters *counters, Context *context


#define DEF_AST_OP(name) Status tr_AST_to_IR_##name (FORMAL_TR_ASM_IR_ARGS);
#include "ast_ops_defs.h"
#undef DEF_AST_OP

#endif /* TR_AST_TO_IR_FUNCS */