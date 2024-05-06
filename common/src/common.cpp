#include "common.h"

#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

inline off_t get_file_size(const char *file_name)
{
    assert(file_name);

    struct stat st_buf = {};

    if ( stat(file_name, &st_buf) == -1) return -1;

    return st_buf.st_size;
}

char *read_file_to_str( const char *file_name )
{
    assert(file_name);

    off_t file_size = get_file_size(file_name);
    if (file_size == -1)
        return NULL;

    FILE *file_p = fopen(file_name, "r");
    if (file_p == NULL)
        return NULL;

    char *str = (char *) calloc( (size_t) file_size + 1, sizeof(char) );

    fread(str, sizeof(char), (size_t) file_size, file_p);
    if ( ferror(file_p) != 0 )
    {
        free(str);
        return NULL;
    }

    fclose(file_p);

    return str;
}

inline void write_tree_node( FILE *stream, TreeNode *node )
{
    assert(stream);
    assert(node);

    putc('(', stream);

    putc(' ', stream);
    TreeNodeType node_type = get_node_data(node).type;
    putc('0' + (char) node_type, stream);
    switch (node_type)
    {
    case TREE_NODE_TYPE_OP:
        fprintf(stream, " %d ", get_node_data(node).op);
        break;
    case TREE_NODE_TYPE_CONST_NUM:
        fprintf(stream, " %g ", get_node_data(node).num);
        break;
    case TREE_NODE_TYPE_VAR_LOCAL:
    case TREE_NODE_TYPE_FUNC_ARG:
        fprintf(stream, " %d ", get_node_data(node).id);
        break;
    case TREE_NODE_TYPE_STR_IDENT: 
    case TREE_NODE_TYPE_CONST_STR:
        fprintf(stream, " %lu %s ", strlen(get_node_data(node).str), get_node_data(node).str );
        break;
    default:
        ASSERT_UNREACHEABLE();
        break;
    }

    if ( tree_get_left_child( node ) )
        write_tree_node( stream, tree_get_left_child( node ) );
    else
        putc('_', stream);

    putc(' ', stream);

    if ( tree_get_right_child( node ) )
        write_tree_node( stream, tree_get_right_child( node ) );
    else
        putc('_', stream);

    putc(' ', stream);
    putc(')', stream);
}

int write_tree_to_file( const char *file_name, const Tree *tree_ptr )
{
    assert(file_name);
    assert(tree_ptr);

    FILE *file = fopen( file_name, "w" );
    if (!file)
        return 0;

    fprintf( file, "%lu ", tree_ptr->nodes_count);

    write_tree_node( file, tree_get_root( tree_ptr ) );

    fclose(file);

    return 1;
}

#define CHECK( char ) do{if ( getc(stream) != char ) return NULL;}while(0);

//! @brief Reads exactly 'n' chars from given 'stream' into 'str' in the 
//! the most simple way. Puts '\0' after them.
//! @attention 'str' MUST HAVE AT LEAST 'n' + 1 FREE SPACE! 
void inline read_n_chars(FILE* stream, size_t n, char *str)
{
    assert(stream);
    assert(str);
    assert(n > 0);

    while (n--)
    {
        *str = (char) getc( stream );
        str++;
    }

    *str = '\0';
}

//! @brief Hopefully does what it says.
void inline skip_spaces(FILE* stream)
{
    assert(stream);
    int c = 0;
    while ( isspace(c = getc(stream)) )
        ;

    ungetc( c, stream );
}

inline TreeNode *read_tree_node( FILE *stream, Tree *tree_ptr )
{
    assert(stream);
    assert(tree_ptr);

    CHECK( '(' );

    CHECK( ' ' );

    TreeNodeType type = (TreeNodeType) ( getc( stream ) - '0' );

    TreeNode *node     = NULL;
    ASTOpNameEnum op   = TREE_OP_DUMMY;
    num_t num          = 0;
    ident_t id         = 0;
    size_t str_len     = 0;
    char *str          = NULL;
    switch (type)
    {
    case TREE_NODE_TYPE_OP:
        fscanf( stream, "%d", (int*) &op );
        node = new_node_op( tree_ptr, op );
        break;
    case TREE_NODE_TYPE_CONST_NUM:
        fscanf( stream, "%f", &num );
        node = new_node_const_num( tree_ptr, num );
        break;
    case TREE_NODE_TYPE_VAR_LOCAL:
        fscanf( stream, "%d", &id );
        node = new_node_var_local( tree_ptr, id );
        break;
    case TREE_NODE_TYPE_FUNC_ARG:
        fscanf( stream, "%d", &id );
        node = new_node_func_arg( tree_ptr, id );
        break;
    case TREE_NODE_TYPE_STR_IDENT:
        fscanf( stream, "%lu", &str_len );
        str = (char*) calloc( str_len+1, sizeof(char) );
        skip_spaces(stream);
        read_n_chars( stream, str_len, str );
        node = new_node_str_ident( tree_ptr, str );
        break;
    case TREE_NODE_TYPE_CONST_STR:
        fscanf( stream, "%lu", &str_len );
        str = (char*) calloc( str_len+1, sizeof(char) );
        skip_spaces(stream);
        read_n_chars( stream, str_len, str );
        node = new_node_const_str( tree_ptr, str );
        break;
    default:
        ASSERT_UNREACHEABLE();
        break;
    }

    CHECK( ' ' );

    int c = 0;
    if ( (c = getc( stream ) ) != '_' )
    {
        ungetc( c, stream );
        TreeNode *node_left = read_tree_node( stream, tree_ptr );
        if ( !node_left )
            return NULL;
        tree_hang_loose_node_at_left( tree_ptr, node_left, node );
    }

    CHECK( ' ' );

    if ( (c = getc( stream ) ) != '_' )
    {
        ungetc( c, stream );
        TreeNode *node_right = read_tree_node( stream, tree_ptr );
        if (!node_right)
            return NULL;
        tree_hang_loose_node_at_right( tree_ptr, node_right, node );
    }

    CHECK( ' ' );

    CHECK( ')' );

    return node;
}

int read_tree_from_file( const char *file_name, Tree *tree_ptr )
{
    assert(file_name);
    assert(tree_ptr);

    FILE *file = fopen( file_name, "r" );
    if (!file)
        return 0;

    size_t nodes_count = 0;
    if ( fscanf( file, "%lu", &nodes_count ) != 1 )
    {
        fclose(file);
        return 0;
    }
    skip_spaces(file);

    *tree_ptr = {};
    tree_ctor( tree_ptr, sizeof(TreeNodeData), nodes_count, TreeNodeData_dtor, print_tree_node_data );

    TreeNode *root = read_tree_node( file, tree_ptr );

    if( !root )
    {
        tree_dtor( tree_ptr );
        fclose(file);
        return 0;
    }

    tree_hang_loose_node_as_root( tree_ptr, root );

    fclose(file);

    return 1;
}

TreeNode *new_node_op( Tree *tree_ptr, ASTOpNameEnum op )
{
    assert(tree_ptr);

    TreeNodeData data = {};
    data.type = TREE_NODE_TYPE_OP;
    data.op = op;
    return op_new_TreeNode( tree_ptr, &data );
}

TreeNode *new_node_const_num( Tree *tree_ptr, num_t num )
{
    assert(tree_ptr);

    TreeNodeData data = {};
    data.type = TREE_NODE_TYPE_CONST_NUM;
    data.num = num;
    return op_new_TreeNode( tree_ptr, &data );
}

TreeNode *new_node_var_local( Tree *tree_ptr, ident_t id )
{
    assert(tree_ptr);

    TreeNodeData data = {};
    data.type = TREE_NODE_TYPE_VAR_LOCAL;
    data.id = id;
    return op_new_TreeNode( tree_ptr, &data );
}

TreeNode *new_node_func_arg( Tree *tree_ptr, ident_t id )
{
    assert(tree_ptr);

    TreeNodeData data = {};
    data.type = TREE_NODE_TYPE_FUNC_ARG;
    data.id = id;
    return op_new_TreeNode( tree_ptr, &data );
}

TreeNode *new_node_str_ident( Tree *tree_ptr, char *ident )
{
    assert(tree_ptr);

    TreeNodeData data = {};
    data.type = TREE_NODE_TYPE_STR_IDENT;
    data.str = ident;
    return op_new_TreeNode( tree_ptr, &data );
}

TreeNode *new_node_const_str( Tree *tree_ptr, char *str )
{
    assert(tree_ptr);

    TreeNodeData data = {};
    data.type = TREE_NODE_TYPE_CONST_STR;
    data.str = str;
    return op_new_TreeNode( tree_ptr, &data );
}

void TreeNodeData_dtor( void *data )
{
    assert(data);
    
    TreeNodeData node_data = *((TreeNodeData*) data);
    if ( node_data.type == TREE_NODE_TYPE_STR_IDENT || node_data.type == TREE_NODE_TYPE_CONST_STR )
        free(node_data.str);
}

TreeNodeData get_node_data( TreeNode *node_ptr )
{
    assert(node_ptr);

    return *((TreeNodeData*)node_ptr->data_ptr);
}

int is_node_op( TreeNode *node_ptr, ASTOpNameEnum op )
{
    assert(node_ptr);

    return get_node_data(node_ptr).type == TREE_NODE_TYPE_OP && get_node_data(node_ptr).op == op;
}

int is_node_num( TreeNode *node_ptr, num_t num )
{
    assert(node_ptr);

    return get_node_data(node_ptr).type == TREE_NODE_TYPE_CONST_NUM
        && are_dbls_equal(get_node_data(node_ptr).num, num);
}

int is_node_var_local( TreeNode *node_ptr, ident_t id )
{
    assert(node_ptr);

    return get_node_data(node_ptr).type == TREE_NODE_TYPE_VAR_LOCAL && get_node_data(node_ptr).id == id;
}

int is_node_func_arg( TreeNode *node_ptr, ident_t id )
{
    assert(node_ptr);

    return get_node_data(node_ptr).type == TREE_NODE_TYPE_FUNC_ARG && get_node_data(node_ptr).id == id;
}

void realloc_arr_if_needed( void **arr_ptr, size_t *arr_cap_ptr, size_t arr_ind, size_t elem_size )
{
    if ( arr_ind >= *arr_cap_ptr )
    {
        size_t new_cap = REALLOC_DEFAULT_MULTIPLIER * (*arr_cap_ptr);
        void *new_mem = realloc( *arr_ptr, new_cap*elem_size );
        if (!new_mem)
        {
            free(*arr_ptr);
            *arr_ptr = NULL;
        }
        *arr_ptr = new_mem;
        *arr_cap_ptr = new_cap;
    }
}

void print_tree_node_data( FILE *stream, void *data_ptr )
{
    assert(data_ptr);

    TreeNodeData data = *((TreeNodeData*)data_ptr);

    switch (data.type)
    {
    case TREE_NODE_TYPE_CONST_NUM:
        fprintf(stream, "data_type: NUM, data_value: %g", data.num);
        break;
    case TREE_NODE_TYPE_OP:
        fprintf(stream, "data_type: OP, data_value: %d", data.op);
        break;
    case TREE_NODE_TYPE_VAR_LOCAL:
        fprintf(stream, "data_type: VAR_LOCAL, data_value: %d", data.id);
        break;
    case TREE_NODE_TYPE_FUNC_ARG:
        fprintf(stream, "data_type: FUNC_ARG, data_value: %d", data.id);
        break;
    case TREE_NODE_TYPE_STR_IDENT:
        fprintf(stream, "data_type: STR_IDENT, data_value: \"%s\"", data.str);
        break;
    case TREE_NODE_TYPE_CONST_STR:
        fprintf(stream, "data_type: STR_IDENT, data_value: \"%s\"", data.str);
        break;
    default:
        ASSERT_UNREACHEABLE();
        break;
    }
}

int is_dbl_zero( double a )
{
    return DBL_PRECISION <= a && a <= DBL_PRECISION;
}

int are_dbls_equal( double a, double b )
{
    return is_dbl_zero(a - b);
}

void put_n_chars( FILE *stream, char c, size_t n )
{
    assert(stream);

    while (n-- > 0)
    {
        putc( c, stream );
    }
}
