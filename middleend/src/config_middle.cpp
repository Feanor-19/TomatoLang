#include "config_middle.h"
const char* FLAG_HELP               = "-h";
const char* FLAG_INPUT_FILE         = "-i";
const char* FLAG_OUTPUT_FILE        = "-o";
const char* FLAG_LOG_FILE           = "-l";
const char* FLAG_IMG_DUMPS_FOLDER   = "--img-dumps";

CmdLineFlag supported_flags[] = {
                                    { FLAG_HELP             , 0, 0, "" },
                                    { FLAG_INPUT_FILE       , 0, 1, "" },
                                    { FLAG_OUTPUT_FILE      , 0, 1, "" },
                                    { FLAG_LOG_FILE         , 0, 1, "" },
                                    { FLAG_IMG_DUMPS_FOLDER , 0, 1, "" }
                                };

const char *help_message = "No help message yet :-(";

/*!
    @brief Assembles struct Config from array of structs CmdLineFlag.
    @param [in] n_flags Length of array flags[].
    @param [in] flags[] Array of structs CmdLineFlag.
    @return Assembled struct Config. If some error occurred,
    Config.error is set to ConfigError enum value.
*/
static Config assemble_config(size_t n_flags, CmdLineFlag flags[]);

//----------------------------------------------------------------

Config get_config(int argc, const char *argv[])
{
    assert(argc > 0);
    assert(argv != NULL);

    const size_t N_FLAGS = sizeof(supported_flags)/sizeof(supported_flags[0]);

    int unread_flags = parse_cmd_args(argc, argv, N_FLAGS, supported_flags);

    if ( extract(N_FLAGS, supported_flags, FLAG_HELP)->state )
    {
        printf("%s\n", help_message);
        exit(0);
    }

    Config cfg = assemble_config(N_FLAGS, supported_flags);
    cfg.unread_flags = unread_flags;
    return cfg;
}

static Config assemble_config(size_t n_flags, CmdLineFlag flags[])
{
    assert(flags != NULL);

    const char *FILE_IN_DEFAULT_NAME        = "prog.txt";
    const char *FILE_OUT_DEFAULT_NAME       = "compiler_tree.txt";

    Config config = {"", "", "", "", CONFIG_NO_ERROR};

    CmdLineFlag *p_curr_flag = NULL;

    if ( ( p_curr_flag = extract(n_flags, supported_flags, FLAG_INPUT_FILE) )!= NULL
       && p_curr_flag->state )
    {
        if ( is_str_empty(p_curr_flag->add_arg) )
        {
            config.error = CONFIG_ERROR_INPUT;
            return config;
        }
        config.input_file_name = p_curr_flag->add_arg;
    }
    else
    {
        config.input_file_name = FILE_IN_DEFAULT_NAME;
    }

    if ( (p_curr_flag = extract(n_flags, supported_flags, FLAG_OUTPUT_FILE) )!= NULL
       && p_curr_flag->state )
    {
        if ( is_str_empty(p_curr_flag->add_arg) )
        {
            config.error = CONFIG_ERROR_OUTPUT;
            return config;
        }
        config.output_file_name = p_curr_flag->add_arg;
    }
    else
    {
        config.output_file_name = FILE_OUT_DEFAULT_NAME;
    }

    if ( (p_curr_flag = extract(n_flags, supported_flags, FLAG_LOG_FILE) )!= NULL
       && p_curr_flag->state )
    {
        if ( is_str_empty(p_curr_flag->add_arg) )
        {
            config.error = CONFIG_ERROR_LOG;
            return config;
        }
        config.log_file_name = p_curr_flag->add_arg;
    }
    else
    {
        config.log_file_name = NULL;
    }

    if ( (p_curr_flag = extract(n_flags, supported_flags, FLAG_IMG_DUMPS_FOLDER) )!= NULL
       && p_curr_flag->state )
    {
        if ( is_str_empty(p_curr_flag->add_arg) )
        {
            config.error = CONFIG_ERROR_IMG_DUMPS_FOLDER;
            return config;
        }
        config.img_dumps_folder = p_curr_flag->add_arg;
    }
    else
    {
        config.img_dumps_folder = NULL;
    }

    return config;

}

void print_config(FILE *stream, Config cfg)
{
    assert(stream != NULL);
    assert(cfg.error == CONFIG_NO_ERROR);

    fprintf(stream,
            "The following configuration is set:\n"
            "data source:                               <%s>\n"
            "output destination:                        <%s>\n"
            "log:                                       <%s>\n"
            "image dumps folder:                        <%s>\n",
            cfg.input_file_name,
            cfg.output_file_name,
            cfg.log_file_name ? cfg.log_file_name : "stdout",
            cfg.img_dumps_folder);
}

void print_cfg_error_message(FILE *stream, ConfigError error)
{
    assert(stream != NULL);

    fprintf(stream, "Some error occured during confgiruation of the prorgam: ");

    switch (error)
    {
    case CONFIG_ERROR_INPUT:
        fprintf(stream, "Input file error.\n");
        break;
    case CONFIG_ERROR_OUTPUT:
        fprintf(stream, "Output file error.\n");
        break;
    case CONFIG_ERROR_LOG:
        fprintf(stream, "Log file error.\n");
        break;
    case CONFIG_ERROR_IMG_DUMPS_FOLDER:
        fprintf(stream, "Image dumps folder error.\n");
        break;
    case CONFIG_NO_ERROR:
    default:
        assert(0 && "Default case in ConfigError switch!");
        break;
    }

    fprintf(stream, "Please, restart and try again.\n");

    return;
}

int is_str_empty(const char *str)
{
    assert( str != NULL );

    return str[0] == '\0';
}
