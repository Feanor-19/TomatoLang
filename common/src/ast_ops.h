#ifndef AST_OP_ENUM_H
#define AST_OP_ENUM_H

#define DEF_AST_OP(id, name) TREE_OP_##name = id,
enum ASTOpNameEnum
{
    #include "ast_ops_defs.h"
};
#undef DEF_AST_OP

struct ASTOpName
{
    ASTOpNameEnum name;
    const char *str;
};

#define DEF_AST_OP(id, name) { TREE_OP_##name, #name },
const ASTOpName AST_OPS_NAMES[] =
{
    #include "ast_ops_defs.h"
    { TREE_OP_DUMMY, "FICTIONAL!" }
};
#undef DEF_AST_OP

#endif /* AST_OP_ENUM_H */
