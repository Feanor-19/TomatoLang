#include <stdio.h>

#include "config_back.h"
#include "ast_dump.h"
#include "common.h"
#include "backend.h"
#include "IR_interface.h"

#define HANDLE_RET_STATUS(func__) \
do{                                                             \
    Status status__ = func__;                                   \
    if (status__ != STATUS_OK)                                  \
    {                                                           \
        ERROR( "Some error happened during translation:" );     \
        print_status_message( log_get_stream(), status__ );     \
        putc( '\n', log_get_stream() );                         \
        ERROR( "Shutting down." );                              \
        IR_dtor(&IR);                                           \
        tree_dtor(&AST);                                        \
        close_img_dumps();                                      \
        log_end();                                              \
        return status__;                                        \
    }                                                           \
}while(0);                                                  


int main( int argc, const char *argv[])
{
    Config cfg = get_config(argc, argv);
    if ( !init_log(cfg) )
    {
        print_status_message( stdout, STATUS_ERROR_CANT_INITIALIZE_LOG );
        return STATUS_ERROR_CANT_INITIALIZE_LOG;
    }
    if (cfg.error)
    {
        print_cfg_error_message( log_get_stream(), cfg.error );
        return cfg.error;
    }
    print_config(log_get_stream(), cfg);

    LOG( "Reading AST from the input file..." );
    Tree AST = {};
    if ( !read_tree_from_file( cfg.input_file_name, &AST ) )
    {
        ERROR("Something went wrong during reading tree from input file.");
        return STATUS_ERROR_EMPTY_AST;
    }
    LOG( "Reading AST from the input file is done!" );

    if ( cfg.img_dumps_folder )
    {
        LOG( "Because config includes image dumps folder, creating image dump of the AST..." );
        init_img_dumps( cfg.img_dumps_folder );
        dump_ast( &AST );
        LOG( "AST image dump is created." );
    }

    IR IR = {};
    LOG("Translating AST to IR...");
    HANDLE_RET_STATUS(translate_AST_to_IR( &AST, &IR ));
    LOG("Translating AST to IR done!");
    // TODO optimize IR

    // TODO make realistic (e.g. pop and push, which use xmm regs)

    LOG("Translating IR to NASM...");
    HANDLE_RET_STATUS(translate_IR_to_NASM( &IR, cfg.output_file_name ));
    LOG("Translating IR to NASM done!");

    IR_dtor(&IR);
    tree_dtor(&AST);
    close_img_dumps();
    LOG( "All work done, shutting down!" );
    log_end();

    return 0;
}
