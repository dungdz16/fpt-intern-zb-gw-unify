#ifndef __CMD_H__
#define __CMD_H__

#include <stdio.h>
#include <string.h>
#include <termios.h>



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
*                                         STATIC FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*
* @brief   Enable raw mode for the terminal
* @param   *old_termios: pointer to the old termios structure
* @retval  None
*/
static void enable_Raw_Mode( struct termios *old_termios);

/*
* @brief    Disable raw mode for the terminal
* @param    *old_termios: pointer to the old termios structure
* @retval   None
*/
static void disable_Raw_Mode(struct termios *old_termios);

/*
* @brief Quick command from keyboard
* @param *cmd: pointer to the command string
* @retval None
*/
static void quick_Command(char *cmd);

/*
* @brief   Clear the current line
* @param   None
* @retval  None
*/
static void clear_line();

/*
* @brief   Parse the command string
* @param   *cmd: pointer to the command string
* @param   *argc: pointer to the number of arguments
*/
static void parse_command(char *cmd, int *argc, char *argv[]);

/*
* @brief   execute the command 
* @param   argc: number of arguments
* @param   *argv: pointer to the arguments
* @retval  None
*/
static void execute_command(int argc, char *argv[]);

/*
*********************************************************************************************************
*                                         API FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*
* @brief   Wait for a command from user
* @param   None
* @retval  None
*/
void wait_A_Command(void);




#endif // __CMD_H__

