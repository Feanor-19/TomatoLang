#ifndef COMMON_H
#define COMMON_H

#include "/usr/include/feanor/tree/tree.h"
#include "logger.h"
#include "ast_ops.h"
#include <assert.h>


typedef int32_t ident_t;
#define ABSENT_ID -1
typedef double num_t;


enum TreeNodeType
{
    TREE_NODE_TYPE_OP,        //!< AST Operator
    TREE_NODE_TYPE_CONST_NUM, //!< Constant number of type 'num_t'
    TREE_NODE_TYPE_VAR_LOCAL, //!< Local variable in some func, defined by numerical
                              // id (of type 'ident_t')
    TREE_NODE_TYPE_FUNC_ARG,  //!< One of func args, defined by its sequence number
                              // (of type 'ident_t')
    TREE_NODE_TYPE_STR_IDENT, //!< Contains string identificator (used for functions' names).
    TREE_NODE_TYPE_CONST_STR, //!< Constant string.
};

struct TreeNodeData
{
    TreeNodeType type;
    union
    {
        ASTOpNameEnum op;
        num_t num;
        ident_t id;
        char *str;
    };

};

enum FuncType
{
    FUNC_TYPE_RECIPE,
    FUNC_TYPE_ACTION,
};



const size_t REALLOC_DEFAULT_MULTIPLIER = 2;
const double DBL_PRECISION              = 1E-10;
const mode_t DEFAULT_FILE_MODE          = 0777;


#define FREE(ptr) do{ if (ptr) free(ptr); ptr = NULL; }while(0)

#define ASSERT_UNREACHEABLE() assert( 0 && "Unreacheable line!" )

#define SIZEARR(arr) (sizeof(arr)/sizeof(arr[0]))

#define FCLOSE(file) do{if (file) fclose(file); }while(0)


//! @brief Reads file with 'file_name' to dynamically allocated string
//! and returns it. If some error happens, returns NULL.
char *read_file_to_str( const char *file_name );

//! @brief Writes given tree to the given file. Returns 1 if
//! all's ok, 0 if some error happens.
int write_tree_to_file( const char *file_name, const Tree *tree_ptr );

//! @brief Reads tree from the given file. Returns 1 if
//! all's ok, 0 if some error happens.
//! @note Given tree IS ctored() by this func. 
int read_tree_from_file( const char *file_name, Tree *tree_ptr );

//! @brief Returns new node of type operator and writes value 'op' into it.
TreeNode *new_node_op( Tree *tree_ptr, ASTOpNameEnum op );

//! @brief Returns new node of type const number and writes value 'num' into it.
TreeNode *new_node_const_num( Tree *tree_ptr, num_t num );

//! @brief Returns new node of type 'var local' and writes value 'id' into it.
TreeNode *new_node_var_local( Tree *tree_ptr, ident_t id );

//! @brief Returns new node of type 'func arg' and writes value 'id' into it.
TreeNode *new_node_func_arg( Tree *tree_ptr, ident_t id );

//! @brief Returns new node of type 'string ident' and writes value 'ident' into it.
TreeNode *new_node_str_ident( Tree *tree_ptr, char *ident );

//! @brief Returns new node of type 'const string' and writes value 'str' into it.
TreeNode *new_node_const_str( Tree *tree_ptr, char *str );

//! @brief Should be passed to tree_ctor().
void TreeNodeData_dtor( void *data );

TreeNodeData get_node_data( TreeNode *node_ptr );

//! @brief Checks given node's type and value.
int is_node_op( TreeNode *node_ptr, ASTOpNameEnum op );

//! @brief Checks given node's type and value.
int is_node_num( TreeNode *node_ptr, num_t num );

//! @brief Checks given node's type and value.
int is_node_var_local( TreeNode *node_ptr, ident_t id );

//! @brief Checks given node's type and value.
int is_node_func_arg( TreeNode *node_ptr, ident_t id );

void realloc_arr_if_needed( void **arr, size_t *arr_cap_ptr, size_t arr_ind, size_t elem_size );

#define REALLOC_ARR_WRP(arr, elem_t) do {                                                       \
    realloc_arr_if_needed( (void**) &(arr), &(arr##_cap), (arr##_curr_len), sizeof(elem_t) );   \
    if (!(arr))                                                                                 \
        ERROR("REALLOC ERROR: array named \"%s\", "                                             \
              "attempt to request %d elems of size %d.",                                        \
              #arr, 2 * (arr##_cap), sizeof(elem_t));                                           \
} while (0)

void print_tree_node_data( FILE *stream, void *data_ptr );

int is_dbl_zero( double a );

int are_dbls_equal( double a, double b );

void put_n_chars( FILE *stream, char c, size_t n );

inline size_t min( size_t a, size_t b )
{
    return (a < b) ? a : b;
}

inline size_t max( size_t a, size_t b )
{
    return (a > b) ? a : b;
}

//! @brief Counts number of nodes connected as a list using TREE_OP_LIST_CONNECTOR.
//! Receives the root of the list.
inline size_t count_list_len( TreeNode *list_root )
{
    assert(list_root);

    size_t num = 1;
    TreeNode *curr = list_root;
    while ( tree_get_right_child( curr ) )
    {
        num++;
        curr = tree_get_right_child( curr );
    }

    return num;
}

#endif /* COMMON_H */
