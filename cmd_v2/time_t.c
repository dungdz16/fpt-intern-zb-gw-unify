/*
******************************************************************************
* @file    cmd.c
* @brief   Command line interface for showing the current time of system
******************************************************************************
*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#include "time_t.h"
#include "cmd.h"

/*
******************************************************************************
*                               DEFINES
******************************************************************************
*/

#define DEFAULT_TIME_ZONE 7

/*
******************************************************************************
*                           LOCAL VARIABLES
******************************************************************************
*/

/*
******************************************************************************
*                       LOCAL FUNCTION PROTOTYPES
******************************************************************************
*/

/*
* @brief   Convert the current time to UTC + Default time zone
* @param   *timeinfo: pointer to the time structure
* @retval  None
*/
static void convert_To_Default_Time_Zone(struct tm *timeinfo)
{
    timeinfo-> tm_hour += DEFAULT_TIME_ZONE;
    if(timeinfo->tm_hour >= 24)
    {
        timeinfo->tm_hour -= 24;
        timeinfo->tm_mday += 1;
    }

    if(timeinfo->tm_mday > 31)
    {
        timeinfo->tm_mday = 1;
        timeinfo->tm_mon += 1;
    }

    if(timeinfo->tm_mon > 12)
    {
        timeinfo->tm_mon = 1;
        timeinfo->tm_year += 1;
    }
}

/*
* @brief   Show the current hour
* @param   None
* @retval  None
*/
static void show_Hour(void)
{
    time_t now;                                              
    struct tm *timeinfo;                                   

    time(&now);
    timeinfo = localtime(&now);

    convert_To_Default_Time_Zone(timeinfo);

    printf("Current hour: %d\n", timeinfo->tm_hour);

}

/*
* @brief   Show the current Day
* @param   None
* @retval  None
*/
static void show_Day(void)
{
    time_t now;                          
    struct tm *timeinfo;

    time(&now);
    timeinfo = localtime(&now);

    convert_To_Default_Time_Zone(timeinfo);

    printf("Current day: %d\n", timeinfo->tm_mday);
}

/*
* @brief   Show the current Month
* @param   None
* @retval  None
*/
static void show_Month(void)
{
    time_t now;                          
    struct tm *timeinfo;

    time(&now);
    timeinfo = localtime(&now);

    convert_To_Default_Time_Zone(timeinfo);

    printf("Current month: %d\n", timeinfo->tm_mon + 1);
}

/*
* @brief   Show the current Year
* @param   None
* @retval  None
*/
static void show_Year(void)
{
    time_t now;                          
    struct tm *timeinfo;

    time(&now);
    timeinfo = localtime(&now);

    convert_To_Default_Time_Zone(timeinfo);

    printf("Current year: %d\n", timeinfo->tm_year + 1900);
}

/*
* @brief   Show the current time
* @param   None
* @retval  None
*/
static void show_Current_Time(void)
{
    time_t now;                          
    struct tm *timeinfo;

    time(&now);
    timeinfo = localtime(&now);

    convert_To_Default_Time_Zone(timeinfo);

    printf("Current time: %s", asctime(timeinfo));
}




/*
******************************************************************************
*                         API FUNCTIONS
******************************************************************************
*/


/*
* @brief   Initialize the command line interface
* @param   None
* @retval  None
*/
void cmd_Time_Init(void)
{
    printf("Command Line Interface is ALL READY\n");
    printf("Supported commands:\n");
    printf("Struct of command: name_of_group+tab+name_of_atributte\n");
    printf("--------------------------------------------------------------\n");
    printf("    now: show time in format yyyy-MM-dd HH:mm:ss\n");
    printf("    now     -y: show year\n");
    printf("    now     -M: show month\n");
    printf("    now     -d: show day\n");
    printf("    now     -H: show hour\n");
    printf("    now     help  : show all supported commands and their description.\n");
    printf("    q     : exit the program\n");
    printf("--------------------------------------------------------------\n");
}

/*
* @brief  Process the time command
* @param  *cmd: pointer to the command string
* @retval result: 1 if the command is valid, 0 if the command is invalid
*/

int process_Time_Command(CommandParams *params)
{
    uint8_t result = 1;
    // printf(" argc = %d\n", params->argc);
    // printf(" argv[1] = %s\n", params->argv[1]);
    if(params->argc == 1)
    {
        show_Current_Time();
    }
    else if(params->argc == 2)
    {
        if(strcmp(params->argv[1], "-y") == 0)
        {
            show_Year();
        }
        else if(strcmp(params->argv[1], "-M") == 0)
        {
            show_Month();
        }
        else if(strcmp(params->argv[1], "-d") == 0)
        {
            show_Day();
        }
        else if(strcmp(params->argv[1], "-H") == 0)
        {
            show_Hour();
        }
        else if(strcmp(params->argv[1], "help") == 0)
        {
            cmd_Time_Init();
        }
        else
        {
            result = 0;
        }
    }
    else
    {
        result = 0;
    }

    return result;
}
