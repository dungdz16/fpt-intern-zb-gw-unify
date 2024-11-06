/*
******************************************************************************
* @file    main.c
* @brief   Main program for showing the current time of system
******************************************************************************
*/

#include <stdio.h>
#include <string.h>

#include "time_t.h"
#include "cmd.h"


void main( int argc, char *argv[] )
{
    cmd_Time_Init();

    printf("Main program is running\n");

    wait_A_Command();
}



