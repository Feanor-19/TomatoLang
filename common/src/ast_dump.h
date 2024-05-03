#ifndef AST_DUMP_H
#define AST_DUMP_H

#include "common.h"


#define DUMP_DOT_EXTENSION "dot"
#define DUMP_IMG_EXTENSION "jpg"
#define DUMP_FILE_DIGITS_COUNT_AS_NUM 3
#define DUMP_FILE_DIGITS_COUNT_AS_STR "3"


void init_img_dumps( const char *folder_path );

void close_img_dumps( void );

void dump_ast( Tree *comp_tree );

#endif /* AST_DUMP_H */
