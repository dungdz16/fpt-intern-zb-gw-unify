#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <unistd.h>
#include <termios.h>

#include "time_t.h"
#include "cmd.h"

/*
*********************************************************************************************************
*                                            DEFINES
*********************************************************************************************************
*/

// Command parameters, thia structure can be extended with more parameters if needed 
struct CommandParams{
    int argc;
    char *argv[MAX_ARGS];
    char *string_param_1;
    char *string_param_2;
    char char_param;
};

/* Supported commands */
Command commands[] = {
    {"now", process_Time_Command},
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
* @brief   Enable raw mode for the terminal
* @param   *old_termios: pointer to the old termios structure
* @retval  None
*/
static void enable_Raw_Mode( struct termios *old_termios)
{
    struct termios raw; // new termios structure

    tcgetattr(STDIN_FILENO, old_termios); // get the current termios structure
    raw = *old_termios; // copy the current termios structure to the new termios structure
    raw.c_lflag &= ~(ECHO | ICANON); // disable echo (off dislay char) and canonical mode (off wait Enter)
    raw.c_cc[VMIN] = 1; //read 1 character at a time
    raw.c_cc[VTIME] = 0; // no wait time
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); // set the new termios structure for terminal 
}

/*
* @brief    Disable raw mode for the terminal
* @param    *old_termios: pointer to the old termios structure
* @retval   None
*/
static void disable_Raw_Mode(struct termios *old_termios)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, old_termios); // set the old termios structure for terminal
}

/*
* @brief Quick command from keyboard
* @param *cmd: pointer to the command string
* @retval None
*/
static void quick_Command(char *cmd)
{
    uint16_t index = 0; // index of the current character in the command string
    uint8_t history_index = history_count; // index of the current command in the history
    int c; // character from keyboard
    char temp_cmd[MAX_CMD_LEN] = {0}; // command string
    int cursor_pos = 0;

    enable_Raw_Mode(&old_termios); // enable raw mode for the terminal

    printf("> ");
    fflush(stdout);

    while (1) {
        c = fgetc(stdin);
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
                memmove(&temp_cmd[cursor_pos - 1], &temp_cmd[cursor_pos], index - cursor_pos + 1);
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
    
    strcpy(cmd, temp_cmd);

    disable_Raw_Mode(&old_termios); // disable raw mode for the terminal

    if (strlen(cmd) > 0) {
        strcpy(history[history_count % MAX_CMD_COUNT], cmd);
        history_count++;
    }
    
}

/*
* @brief   Parse the command string
* @param   *cmd: pointer to the command string
* @param   *argc: pointer to the number of arguments
*/
static void parse_command(char *cmd, int *argc, char *argv[])
{
    char *token;
    int arg_index = 0;

    token = strtok(cmd, "\t");
    while (token != NULL && arg_index < MAX_ARGS) {
        argv[arg_index++] = token;
        token = strtok(NULL, "\t");
    }
    *argc = arg_index;
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
* @retval  None
*/
static void execute_command(int argc, char *argv[])
{
    if (argc == 0) return;

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

            return;
        }
    }
    printf("Invalid command: %s\n", argv[0]);
}

/*
*********************************************************************************************************
*                                            API FUNCTIONS
*********************************************************************************************************
*/

/*
* @brief   Wait for a command from user
* @param   None
* @retval  None
*/
void wait_A_Command(void)
{
    char cmd[MAX_CMD_LEN];
    char *argv[MAX_ARGS];
    int argc;

    while(1)
    {

        quick_Command(cmd);

        parse_command(cmd, &argc, argv);

        if (argc > 0 && strcmp(argv[0], "q") == 0) {
            break;
        }

        execute_command(argc, argv);
    }

}





