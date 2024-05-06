#include <stdio.h>

#include "middleend.h"
#include "config_middle.h"
#include "ast_dump.h"

int main(int argc, const char *argv[])
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

    Tree AST = {};
    if (!read_tree_from_file( cfg.input_file_name, &AST ))
    {
        ERROR("Something went wrong during reading the tree from file.");
        return STATUS_ERROR_CANT_READ_TREE_FROM_FILE;
    }

    LOG("AST is successfully read from file!");

    dump_ast( &AST );
    LOG("AST dump done! (if it could be done...)");

    log_end();

    return 0;
}
