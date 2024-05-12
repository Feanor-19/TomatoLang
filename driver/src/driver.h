#ifndef DRIVER_H
#define DRIVER_H

#include "common.h"
#include "config_driver.h"

#define DEF_STATUS(name, msg) DRIVER_STATUS_##name,
enum DriverStatus
{
    #include "driver_statuses.h"
};
#undef DEF_STATUS


#define DEF_STATUS(name, message) message,
const char * const driver_status_messages[] =
{
    #include "driver_statuses.h"
    "FICTIONAL MESSAGE!"
};
#undef DEF_STATUS


void driver_print_status_message( FILE *stream, DriverStatus status );

int driver_init_log( DriverConfig cfg );


#endif /* DRIVER_H */