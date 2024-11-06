/*
******************************************************************************
* @file    main.c
* @brief   Main program for showing the current time of system
******************************************************************************
*/

#include <stdio.h>
#include <string.h>

#include "cmd.h"

void main()
{
    cmd_Init();

    printf("Main program is running\n");

    wait_A_Command();
}



