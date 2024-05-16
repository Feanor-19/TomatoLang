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


    Status status = STATUS_OK;
    Tree AST = {};
    LOG("Reading AST from file...");
    if (!read_tree_from_file( cfg.input_file_name, &AST ))
    {
        ERROR("Something went wrong during reading the AST from file.");
        status = STATUS_ERROR_CANT_READ_TREE_FROM_FILE;
        goto finally;
    }
    LOG("AST is successfully read from file!");
    
    if ( cfg.img_dumps_folder )
    {
        LOG( "Because config includes image dumps folder, creating image dump of the AST..." );
        init_img_dumps( cfg.img_dumps_folder );
        dump_ast( &AST );
        LOG( "AST image dump is created." );
    }
    
    LOG( "Optimizing AST..." );

    LOG( "Optimizing AST done!" );

    if ( cfg.img_dumps_folder )
    {
        LOG( "Creating image dunp of the AST after optimization..." );
        dump_ast( &AST );
        LOG( "AST image dump is created." );
    }

    LOG( "Writing AST to output file..." );
    if (!write_tree_to_file(cfg.output_file_name, &AST))
    {
        ERROR("Something went wrong during writing the AST to file.");
        status = STATUS_ERROR_CANT_WRITE_TREE_TO_FILE;
        goto finally;
    }
    LOG( "Writing AST to output file done!" );

// REVIEW 
// Final exit from the program, freeing all memory
finally:
    tree_dtor(&AST);
    close_img_dumps();
    log_end();

    return status;
}
