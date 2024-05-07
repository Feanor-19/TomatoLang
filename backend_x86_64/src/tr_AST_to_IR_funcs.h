#ifndef TR_AST_TO_IR_FUNCS
#define TR_AST_TO_IR_FUNCS

#include "back_common.h"

#define FORMAL_TR_ASM_TEXT_ARGS FILE *stream, const Tree *AST, TreeNode *node, \
                                Counters *counters


#define DEF_AST_OP(name) Status tr_AST_to_IR_##name (FORMAL_TR_ASM_TEXT_ARGS);
#include "ast_ops_defs.h"
#undef DEF_AST_OP

#endif /* TR_AST_TO_IR_FUNCS */