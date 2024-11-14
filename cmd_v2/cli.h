#ifndef __CLI_H__
#define __CLI_H__

#include <stdio.h>
#include <string.h>
#include <termios.h>

#include "error.h"



/*
*********************************************************************************************************
*                                            DEFINES
*********************************************************************************************************
*/

#define MAX_CMD_LEN  512
#define MAX_CMD_COUNT 20
#define MAX_ARGS 10

/*
*********************************************************************************************************
*                                             VARIABLES
*********************************************************************************************************
*/

// Command parameters, thia structure can be extended with more parameters if needed 
typedef struct {
    int argc;
    char *argv[MAX_ARGS];
    char *string_param_1;
    char *string_param_2;
    char char_param;
} CommandParams;

// Command handler
typedef int (*CommandHandler)(CommandParams *params);

// Command structure
typedef struct {
    char *name;
    CommandHandler handler;
} Command;







/*
*********************************************************************************************************
*                                         API FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*
* @brief   Wait for a command from user
* @param   None
* @retval  CLI_PROCESS_LINE_OK: if the command is valid  CLI_PROCESS_LINE_ERROR: if the command is invalid
*/
cli_Status_t cli_process_line(void);

/*
* @brief   Show all of cli command supported
* @param   commands supported in the lookup table
* @retval  None
*/

int cli_show_commands(CommandParams *params);

void cli_init(void);

#endif // __CLI_H__

