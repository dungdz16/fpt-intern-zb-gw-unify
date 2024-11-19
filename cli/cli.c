#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <unistd.h>
#include <termios.h>

#include "error.h"
#include "cli_time.h"
#include "cli.h"

/*
*********************************************************************************************************
*                                            DEFINES
*********************************************************************************************************
*/

// // Command parameters, thia structure can be extended with more parameters if needed 
// struct CommandParams{
//     int argc;
//     char *argv[MAX_ARGS];
//     char *string_param_1;
//     char *string_param_2;q
//     char char_param;
// };

/* Supported commands */
Command commands[] = {
    {"now", cli_process_time},
    {"help", cli_show_commands},
    {NULL, NULL}
};

/*
*********************************************************************************************************
*                                            LOCAL VARIABLES
*********************************************************************************************************
*/
static char history[MAX_CMD_COUNT][MAX_CMD_LEN];
static uint8_t history_count = 0; // number of commands in the history


static struct termios old_termios; // old termios structure


/*
*********************************************************************************************************
*                                            LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                         STATIC FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static cli_status_t cli_enable_raw_rode( struct termios *old_termios);
static cli_status_t cli_disable_raw_mode(struct termios *old_termios);
static cli_status_t cli_process(char *cmd);
static cli_status_t cli_parse_command(char *cmd, int *argc, char *argv[]);
static cli_status_t cli_execute_command(int argc, char *argv[]);

static void clear_line();


/*
*********************************************************************************************************
*                                         STATIC FUNCTIONS
*********************************************************************************************************
*/


/*
* @brief   Enable raw mode for the terminal
* @param   *old_termios: pointer to the old termios structure
* @retval  cli_status_t: status of the function
*/
static cli_status_t cli_enable_raw_rode( struct termios *old_termios)
{
    struct termios raw; // new termios structure

    tcgetattr(STDIN_FILENO, old_termios); // get the current termios structure
    raw = *old_termios; // copy the current termios structure to the new termios structure
    raw.c_lflag &= ~(ECHO | ICANON); // disable echo (off dislay char) and canonical mode (off wait Enter)
    raw.c_cc[VMIN] = 1; //read 1 character at a time
    raw.c_cc[VTIME] = 0; // no wait time
    
    // Return error if failed to set the new termios structure
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        return ENABLE_RAW_MODE_ERROR;
    }
    else {
        return ENABLE_RAW_MODE;
    }

}

/*
* @brief    Disable raw mode for the terminal
* @param    *old_termios: pointer to the old termios structure
* @retval  cli_status_t: status of the function
*/
static cli_status_t cli_disable_raw_mode(struct termios *old_termios)
{
    // Return error if failed to set the old termios structure
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, old_termios) == -1) {
        return DISABLE_RAW_MODE_ERROR;
    }
    else {
        return DISABLE_RAW_MODE;
    }
}

/*
* @brief Quick command from keyboard
* @param *cmd: pointer to the command string
* @retval cli_status_t: status of the function
*/
static cli_status_t cli_process(char *cmd)
{
    uint8_t reval = 1;
    uint16_t index = 0; // index of the current character in the command string
    uint8_t history_index = history_count; // index of the current command in the history
    int c; // character from keyboard
    char temp_cmd[MAX_CMD_LEN] = {0}; // command string
    int cursor_pos = 0;

    if(cli_enable_raw_rode(&old_termios) == ENABLE_RAW_MODE_ERROR)
    {
        printf("Error: Failed to enable raw mode\n");
        return CLI_PROCESS_ERROR;
    }

    printf("> ");
    fflush(stdout);

    while (1) {
        c = fgetc(stdin);
        // check error from keyboard
        if (c == EOF) {
            if(cli_disable_raw_mode(&old_termios) == DISABLE_RAW_MODE_ERROR)
            {
                printf("Error: Failed to disable raw mode\n");
                fflush(stdout);
            }
            return CLI_PROCESS_ERROR;
        }

        if (c == '\n') {
            temp_cmd[index] = '\0';
            printf("\n");
            break;
        } else if (c == 27) { // Escape sequence
            int next1 = fgetc(stdin);
            int next2 = fgetc(stdin);
            if (next1 == '[') {
                if (next2 == 'A') { // Up arrow
                    if (history_index > 0) {
                        history_index--;
                        strcpy(temp_cmd, history[history_index]);
                        index = strlen(temp_cmd);
                        cursor_pos = index;
                        clear_line();
                        printf("> %s", temp_cmd);
                        fflush(stdout);
                    }
                } else if (next2 == 'B') { // Down arrow
                    if (history_index < history_count - 1) {
                        history_index++;
                        strcpy(temp_cmd, history[history_index]);
                        index = strlen(temp_cmd);
                        cursor_pos = index;
                    } else {
                        history_index = history_count;
                        temp_cmd[0] = '\0';
                        index = 0;
                        cursor_pos = 0;
                    }
                    clear_line();
                    printf("> %s", temp_cmd);
                    fflush(stdout);
                } else if (next2 == 'D') { // Left arrow
                    if (cursor_pos > 0) {
                        cursor_pos--;
                        printf("\b");
                        fflush(stdout);
                    }
                } else if (next2 == 'C') { // Right arrow
                    if (cursor_pos < index) {
                        printf("%c", temp_cmd[cursor_pos]);
                        cursor_pos++;
                        fflush(stdout);
                    }
                }
            }
        } else if (c == 127 || c == '\b') { // Backspace
            if (cursor_pos > 0) {
                memmove(&temp_cmd[cursor_pos - 1], &temp_cmd[cursor_pos], index - cursor_pos + 1);  // move the characters after the cursor to the left 
                index--;
                cursor_pos--;
                clear_line();
                printf("> %s", temp_cmd);
                for (int i = cursor_pos; i < index; i++) {
                    printf("\b");
                }
                fflush(stdout);
            }
        } else {
            if (index < MAX_CMD_LEN - 1) {
                memmove(&temp_cmd[cursor_pos + 1], &temp_cmd[cursor_pos], index - cursor_pos);
                temp_cmd[cursor_pos] = c;
                index++;
                cursor_pos++;
                clear_line();
                printf("> %s", temp_cmd);
                for (int i = cursor_pos; i < index; i++) {
                    printf("\b");
                }
                fflush(stdout);
            }
        }
    }
    
    if(strcpy(cmd, temp_cmd) == NULL)
    {
        printf("Error: Failed to copy command\n");
        fflush(stdout);
        reval = 0;
    }

    if(cli_disable_raw_mode(&old_termios) == DISABLE_RAW_MODE_ERROR)
    {
        printf("Error: Failed to disable raw mode\n");
        fflush(stdout);
        reval = 0;
    }

    if (strlen(cmd) > 0) {
        strcpy(history[history_count % MAX_CMD_COUNT], cmd);
        history_count++;
    }

    if (reval == 0) {
        return CLI_PROCESS_ERROR;
    }
    else {
        return CLI_PROCESS_OK;
    }
}

/*
* @brief   Parse the command string
* @param   *cmd: pointer to the command string
* @param   *argc: pointer to the number of arguments
* @param   *argv: pointer to the arguments
* @retval  CLI_PARSE_CMD_OK: if the command is valid  CLI_PARSE_CMD_ERROR: if the command is invalid
*/
static cli_status_t cli_parse_command(char *cmd, int *argc, char *argv[])
{
    char *token;
    int arg_index = 0;

    // Trim leading and trailing whitespace if no command 
    while (isspace((unsigned char)*cmd)) cmd++;
    if (*cmd == 0) {
        *argc = 0;
        return CLI_PARSE_CMD_NO_CMD; 
    }

    token = strtok(cmd, " ");
    while (token != NULL && arg_index < MAX_ARGS) {
        argv[arg_index++] = token;
        token = strtok(NULL, " ");
    }
    *argc = arg_index;

    // if(arg_index == 0 && strcmp(argv[0], "q") == 0)
    // {
    //     return CLI_PARSE_CMD_ERROR;
    // }
        
    return CLI_PARSE_CMD_OK;
}

/*
* @brief   Clear the current line
* @param   None
* @retval  None
*/
static void clear_line() {
    printf("\33[2K\r"); // ANSI escape to clear line and return cursor
}

/*
* @brief   execute the command 
* @param   argc: number of arguments
* @param   *argv: pointer to the arguments
* @retval  CLI_EXEC_CMD_OK: if the command is valid  CLI_EXEC_CMD_ERROR: if the command is invalid
*/
static cli_status_t cli_execute_command(int argc, char *argv[])
{
    // if (argc == 0) return CLI_EXEC_CMD_ERROR;

    CommandParams params;
    memset(&params, 0, sizeof(params));

    params.argc = argc;
    for (int i = 0; i < argc; i++) {
        params.argv[i] = argv[i];
    }

    // printf("argc = %d\n", params.argc);
    // printf("argv[0] = %s\n", params.argv[0]);

    for (int i = 0; commands[i].name != NULL; i++)
    {
        if (strcmp(argv[0], commands[i].name) == 0)
        {   
            // many name of group command
            // if (strcmp(argv[0], "time") == 0 && argc > 1)
            // {
            //     params.string_param_1 = argv[1];
            // }
            commands[i].handler(&params);
            //printf("huhu");

            return CLI_EXEC_CMD_OK;
        }
    }
    printf("Invalid command: %s\n", argv[0]);
    printf("Please type 'help' to show all supported commands\n");
    return CLI_EXEC_CMD_ERROR;
}

/*
*********************************************************************************************************
*                                            API FUNCTIONS
*********************************************************************************************************
*/

/*
* @brief   Wait for a command from user
* @param   None
* @retval  CLI_PROCESS_LINE_OK: if the command is valid  CLI_PROCESS_LINE_ERROR: if the command is invalid
*/
cli_status_t cli_process_line(void)
{
    uint8_t reval = 1;
    char cmd[MAX_CMD_LEN];
    char *argv[MAX_ARGS];
    int argc;

    while(1)
    {
        if(cli_process(cmd) == CLI_PROCESS_ERROR)
        {
            printf("Error: Failed to process command\n");
            reval = 0;
            continue;
        } 
        uint8_t result_cli_parse_command = cli_parse_command(cmd, &argc, argv);
        
            if (result_cli_parse_command == CLI_PARSE_CMD_OK)
            {
                // Kiểm tra lệnh 'q' sau khi phân tích lệnh
                if (strcmp(argv[0], "q") == 0)
                {   
                    reval = 1;
                    break; // Thoát khỏi vòng lặp
                }
                if (cli_execute_command(argc, argv) == CLI_EXEC_CMD_ERROR)
                {
                    // printf("sao lai nhay vao day\n");
                    reval = 0;
                }
                else
                {
                    reval = 1;
                }
            } 
            else if (result_cli_parse_command == CLI_PARSE_CMD_NO_CMD)
            {
                reval = 1;
            }

        

    }

    if (reval == 0) {
        return CLI_PROCESS_LINE_ERROR;
    }
    else {
        return CLI_PROCESS_LINE_OK;
    }

}


/*
* @brief   Show all of cli command supported
* @param   commands supported in the lookup table
* @retval  None
*/

int cli_show_commands(CommandParams *params) 
{
    int i = 0;
    printf("Supported commands group:\n");
    printf("-----------------------------------------------------------------------------------------------\n");
    while (commands[i].name != NULL)
    {
        printf("    %s", commands[i].name);

        if(strcmp(commands[i].name, "now") == 0)
        printf(": supported command group for show time\n");
        else if(strcmp(commands[i].name, "help") == 0)
        printf(": show all supported commands\n");

        i++;
    }
    printf("    q: exit the program\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("Please type  <name_of_group> help  to show all supported commands and their description\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("\n");
}

/*
* @brief   Initialize the command line interface
*/

void cli_init(void)
{
    cli_show_commands(NULL);
}

