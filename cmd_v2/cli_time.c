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

#include "cli_time.h"
#include "cli.h"

/*
******************************************************************************
*                               DEFINES
******************************************************************************
*/

#define DEFAULT_TIME_ZONE 7
#define PRINTF_TIME_COMMAND_INVALID printf("Invalid command\n");

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

static void convert_to_default_time_zone(struct tm *timeinfo);
static void cli_process_time_show_hour(void);
static void cli_process_time_show_day(void);
static void cli_process_time_show_month(void);
static void cli_process_time_cli_process_time_show_year(void);
static void cli_process_time_show_current_time(void);


/*
******************************************************************************
*                           LOCAL FUNCTIONS
******************************************************************************
*/


/*
* @brief   Convert the current time to UTC + Default time zone
* @param   *timeinfo: pointer to the time structure
* @retval  None
*/
static void convert_to_default_time_zone(struct tm *timeinfo)
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
static void cli_process_time_show_hour(void)
{
    time_t now;                                              
    struct tm *timeinfo;                                   

    time(&now);
    timeinfo = localtime(&now);

    convert_to_default_time_zone(timeinfo);

    printf("Current hour: %d\n", timeinfo->tm_hour);

}

/*
* @brief   Show the current Day
* @param   None
* @retval  None
*/
static void cli_process_time_show_day(void)
{
    time_t now;                          
    struct tm *timeinfo;

    time(&now);
    timeinfo = localtime(&now);

    convert_to_default_time_zone(timeinfo);

    printf("Current day: %d\n", timeinfo->tm_mday);
}

/*
* @brief   Show the current Month
* @param   None
* @retval  None
*/
static void cli_process_time_show_month(void)
{
    time_t now;                          
    struct tm *timeinfo;

    time(&now);
    timeinfo = localtime(&now);

    convert_to_default_time_zone(timeinfo);

    printf("Current month: %d\n", timeinfo->tm_mon + 1);
}

/*
* @brief   Show the current Year
* @param   None
* @retval  None
*/
static void cli_process_time_show_year(void)
{
    time_t now;                          
    struct tm *timeinfo;

    time(&now);
    timeinfo = localtime(&now);

    convert_to_default_time_zone(timeinfo);

    printf("Current year: %d\n", timeinfo->tm_year + 1900);
}

/*
* @brief   Show the current time
* @param   None
* @retval  None
*/
static void cli_process_time_show_current_time(void)
{
    time_t now;                          
    struct tm *timeinfo;

    time(&now);
    timeinfo = localtime(&now);

    convert_to_default_time_zone(timeinfo);

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
    printf("Command Line Interface of time is ALL READY\n");
    printf("Supported commands:\n");

    printf("--------------------------------------------------------------\n");
    printf("Struct of command: <name_of_group> <name_of_atributte>\n");
    printf("    now     : show time in format yyyy-MM-dd HH:mm:ss\n");
    printf("    now -y  : show year\n");
    printf("    now -M  : show month\n");
    printf("    now -d  : show day\n");
    printf("    now -H  : show hour\n");
    printf("    now help: show all supported commands and their description.\n");
    printf("    help    : show all supported commands\n");
    printf("    q       : exit the program\n");
    printf("--------------------------------------------------------------\n");
    printf("\n");
}

/*
* @brief  Process the time command
* @param  *cmd: pointer to the command string
* @retval CLI_PROCESS_TIME_OK: if the command is valid, CLI_PROCESS_TIME_ERROR: if the command is invalid
*/

int cli_process_time(CommandParams *params)
{
    uint8_t result = 1;
    // printf(" argc = %d\n", params->argc);
    // printf(" argv[1] = %s\n", params->argv[1]);
    if(params->argc == 1)
    {
        cli_process_time_show_current_time();
    }
    else if(params->argc == 2)
    {
        if(strcmp(params->argv[1], "-y") == 0)
        {
            cli_process_time_show_year();
        }
        else if(strcmp(params->argv[1], "-M") == 0)
        {
            cli_process_time_show_month();
        }
        else if(strcmp(params->argv[1], "-d") == 0)
        {
            cli_process_time_show_day();
        }
        else if(strcmp(params->argv[1], "-H") == 0)
        {
            cli_process_time_show_hour();
        }
        else if(strcmp(params->argv[1], "help") == 0)
        {
            cmd_Time_Init();
        }
        else
        {
            printf("Invalid command: %s\n", params->argv[1]);
            result = 0;
        }
    }
    else
    {   
        printf("Invalid command\n");
        result = 0;
    }

    if (result == 1)
    {
        return CLI_PROCESS_TIME_OK;
    }
    else
    {
        return CLI_PROCESS_TIME_ERROR;
    }
}

