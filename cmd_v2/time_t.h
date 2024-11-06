/*
*********************************************************************************************************
*                                            INCLUDE FILES SUPPORT PROCESS COMMAND
*********************************************************************************************************
*/

#ifndef __TIME_T_H__
#define __TIME_T_H__

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#include "cmd.h"
/*
*********************************************************************************************************
*                                            DEFINES    
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            LOCAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*
* @brief   Convert the current time to UTC + Default time zone
* @param   *timeinfo: pointer to the time structure
* @retval  None
*/
static void convert_To_Default_Time_Zone(struct tm *timeinfo);

/*
* @brief   Show the current hour
* @param   None
* @retval  None
*/
static void show_Hour(void);

/*
* @brief   Show the current Day
* @param   None
* @retval  None
*/
static void show_Day(void);

/*
* @brief   Show the current Month
* @param   None
* @retval  None
*/
static void show_Month(void);

/*
* @brief   Show the current Year
* @param   None
* @retval  None
*/
static void show_Year(void);

/*
* @brief   Show the current time
* @param   None
* @retval  None
*/
static void show_Current_Time(void);

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

int process_Time_Command(CommandParams *params);

#endif // __TIME_T_H__

