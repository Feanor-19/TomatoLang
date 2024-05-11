#include <stdio.h>

#include "config_back.h"
#include "ast_dump.h"
#include "common.h"
#include "backend.h"
#include "IR_interface.h"

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

    LOG( "Initializing image dumps folder..." );
    if (cfg.img_dumps_folder)
       init_img_dumps( cfg.img_dumps_folder );
    LOG( "Initializing image dumps folder is done!" );

    LOG( "Reading AST from the input file..." );
    Tree AST = {};
    if ( !read_tree_from_file( cfg.input_file_name, &AST ) )
    {
        ERROR("Something went wrong during reading tree from input file.");
    }
    LOG( "Reading AST from the input file is done!" );

    if ( cfg.img_dumps_folder )
    {
        LOG( "Because config includes image dumps folder, creating image dump of the AST..." );
        init_img_dumps( cfg.img_dumps_folder );
        dump_ast( &AST );
        LOG( "AST image dump is created." );
    }

    // make IR
    IR IR = {};
    translate_AST_to_IR( &AST, &IR );

    // optimize IR

    // translate IR to nasm

    IR_dtor(&IR);
    tree_dtor(&AST);

    close_img_dumps();

    LOG( "All work done, shutting down!" );

    log_end();

    return 0;
}
