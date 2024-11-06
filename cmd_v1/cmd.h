/*
*********************************************************************************************************
*                                            INCLUDE FILES SUPPORT PROCESS COMMAND
*********************************************************************************************************
*/

#ifndef __CMD_H__
#define __CMD_H__

#include <stdio.h>
#include <string.h>
#include <time.h>

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
void cmd_Init(void);

/*
* @brief   Wait for a command from user
* @param   None
* @retval  None
*/
void wait_A_Command(void);











#endif










