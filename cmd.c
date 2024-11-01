/*
******************************************************************************
* @file    cmd.c
* @brief   Command line interface for showing the current time of system
******************************************************************************
*/

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "cmd.h"

/*
******************************************************************************
*                               DEFINES
******************************************************************************
*/
#define MAX_CMD_LEN  512

/*
******************************************************************************
*                           LOCAL VARIABLES
******************************************************************************
*/
static char cmd[MAX_CMD_LEN];

/*
******************************************************************************
*                       LOCAL FUNCTION PROTOTYPES
******************************************************************************
*/

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
void cmd_Init(void)
{
    printf("Command Line Interface is ALL READY\n");
    printf("--------------------------------------------------------------\n");
    printf("Supported commands:\n");
    printf("    now: show time in format yyyy-MM-dd HH:mm:ss\n");
    printf("    now -y: show year\n");
    printf("    now -M: show month\n");
    printf("    now -d: show day\n");
    printf("    now -H: show hour\n");
    printf("    help  : show all supported commands and their description.\n");
    printf("    q     : exit the program\n");
    printf("--------------------------------------------------------------\n");
}

/*
* @brief   Wait for a command from user
* @param   None
* @retval  None
*/
void wait_A_Command(void)
{
    while(1)
    {
        printf("Please enter a command: \n");
        printf(">> ");
        fgets(cmd, MAX_CMD_LEN, stdin);
        cmd[strlen(cmd) - 1] = '\0'; // remove the '\n' character at the end of the string

        if(strcmp(cmd, "now -H")==0)
        {
            show_Hour();
        }
        

        if(strcmp(cmd, "now") == 0)
        {
            show_Current_Time();
        }
        else if(strcmp(cmd, "now -y") == 0)
        {
            show_Year();
        }
        else if(strcmp(cmd, "now -M") == 0)
        {
            show_Month();
        }
        else if(strcmp(cmd, "now -d") == 0)
        {
            show_Day();
        }
        else if(strcmp(cmd, "now -H") == 0)
        {
            show_Hour();
        }
        else if(strcmp(cmd, "help") == 0)
        {
            cmd_Init();
        }
        else if(strcmp(cmd, "q") == 0)
        {
            break;
        }
        else
        {
            printf("Invalid command. Please enter 'help' to see all supported commands.\n");
        }
    }
}

