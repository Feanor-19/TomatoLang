#include "driver.h"

void driver_print_status_message( FILE *stream, DriverStatus status )
{
    fprintf(stream, "%s", driver_status_messages[status]);
}

int driver_init_log( DriverConfig cfg )
{
    if (cfg.log_file_name)
    {
        if (!logger_init_log( cfg.log_file_name ))
        {
            return 0;
        }
    }
    else
    {
        if (!logger_init_log( stdout ))
        {
            return 0;
        }
    }

    return 1;
}