/*
******************************************************************************
* @file    main.c
* @brief   Main program for showing the current time of system
******************************************************************************
*/

#include <stdio.h>
#include <string.h>

#include "cli_time.h"
#include "cli.h"


void main( int argc, char *argv[] )
{
    cli_init();

    printf("Main program is running\n");

    if(cli_process_line() == CLI_PROCESS_LINE_ERROR)
    {
        printf("Error: Failed to process command\n");
    }
}



