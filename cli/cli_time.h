/*
*********************************************************************************************************
*                                            INCLUDE FILES SUPPORT PROCESS COMMAND
*********************************************************************************************************
*/

#ifndef __CLI_TIME_H__
#define __CLI_TIME_H__

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#include "cli.h"
/*
*********************************************************************************************************
*                                            DEFINES    
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            API FUNCTIONS
*********************************************************************************************************
*/

/*
* @brief   Initialize the command line interface
* @param   None
* @retval  None
*/
void cmd_Time_Init(void);

/*
* @brief  Process the time command
* @param  *cmd: pointer to the command string
* @retval result: 1 if the command is valid, 0 if the command is invalid
*/

int cli_process_time(CommandParams *params);

#endif // __CLI_TIME_H__

