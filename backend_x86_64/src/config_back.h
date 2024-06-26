#ifndef CONFIG_BACK_H
#define CONFIG_BACK_H

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser_cmd_args.h"

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    HOW TO ADD A NEW FLAG
    1) Add a new member in struct Config in config.h (if needed)
    2) Add a new element in supported_flags[] in config.cpp
    3) Add a new constant string right before supported_flags[] in config.cpp
    4) Modify get_config(), assemble_config(), print_config() in config.cpp
    5) If needed, add a new member in ConfigError enum in config.h and modify print_cfg_error_message()
    6) Profit!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

//-------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------

enum ConfigError
{
    CONFIG_NO_ERROR = 0,
    CONFIG_ERROR_INPUT,
    CONFIG_ERROR_OUTPUT,
    CONFIG_ERROR_LOG,
    CONFIG_ERROR_IMG_DUMPS_FOLDER,
};

/*!
    @brief Contains all configurable parametres of the automaton.
*/
struct Config
{
    const char *input_file_name;        //!< Source of the data.
    const char *output_file_name;       //!< Destination for the output.
    const char *log_file_name;          //!< Log file name.
    const char *img_dumps_folder;       //!< Path to the folder for image dumps.
    ConfigError error;                  //!< ConfigError enum value.
    int unread_flags;                   //!< Number of unrecognized flags.
};

//! @brief Gets all configurable parametres of the automaton.
//! @param argc
//! @return All collected information packed in the Config struct.
Config get_config(int argc, const char *argv[]);

void print_config(FILE *stream, Config cfg);

void print_cfg_error_message(FILE *stream, ConfigError error);

int is_str_empty(const char *str);

#endif /* CONFIG_BACK_H */
