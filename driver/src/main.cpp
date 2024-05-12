#include <stdio.h>

#include "config_driver.h"
#include "driver.h"
#include "ast_dump.h"
#include "common.h"
#include "frontend.h"
#include "backend.h"

#define HANDLE_RET_STATUS(func__) \
do{                                                             \
    DriverStatus status__ = func__;                                   \
    if (status__ != STATUS_OK)                                  \
    {                                                           \
        ERROR( "Some error happened" );                         \
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
    DriverConfig cfg = get_config(argc, argv);
    if ( !driver_init_log(cfg) )
    {
        driver_print_status_message( stdout, DRIVER_STATUS_ERROR_CANT_INITIALIZE_LOG );
        return STATUS_ERROR_CANT_INITIALIZE_LOG;
    }
    if (cfg.error)
    {
        print_cfg_error_message( log_get_stream(), cfg.error );
        return cfg.error;
    }
    print_config(log_get_stream(), cfg);

    if (cfg.img_dumps_folder)
    {
        LOG( "Initializing image dumps folder..." );
        init_img_dumps( cfg.img_dumps_folder );
        LOG( "Initializing image dumps folder is done!" );
    }

    LOG("Reading program from the input file...");
    char *prog_str = read_file_to_str( cfg.input_file_name );
    if (!prog_str)
    {
        driver_print_status_message( log_get_stream(), DRIVER_STATUS_ERROR_CANT_READ_INPUT_FILE );
        return STATUS_ERROR_CANT_READ_INPUT_FILE;
    }
    LOG("Reading program from the input file done!");

    LOG( "Starting compilation..." );
    CompiledProgram compiled_prog = {};
    Status comp_err = compile_prog( prog_str, &compiled_prog );
    if (comp_err == STATUS_OK)
    {
        LOG( "Compilation is done!" );
    }

    if (cfg.img_dumps_folder)
        close_img_dumps();

    LOG( "All work done, shutting down!" );
    log_end();

    return 0;
}
