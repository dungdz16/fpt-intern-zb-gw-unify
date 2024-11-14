
#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdio.h>

typedef enum{
    ERROR_NONE = 0,
    
    ERROR_INVALID_VALUE,            // error for cli_Parse_Uint16, cli_Parse_Int16, cli_Parse_Uint8, cli_Parse_Int8, ...
    ERROR_VALID_VALUE_OK,           // error for cli_Parse_Uint16, cli_Parse_Int16, cli_Parse_Uint8, cli_Parse_Int8, ...
    
    ENABLE_RAW_MODE_ERROR,          // error for cli_Enable_Raw_Mode
    ENABLE_RAW_MODE,
    
    DISABLE_RAW_MODE_ERROR,         // error for cli_Disable_Raw_Mode
    DISABLE_RAW_MODE,
    
    CLI_PROCESS_ERROR,              // error for cli_Process
    CLI_PROCESS_OK,

    CLI_PARSE_CMD_ERROR,            // error for cli_Parse_Command
    CLI_PARSE_CMD_OK, 

    CLI_EXEC_CMD_ERROR,             // error for cli_Exec_Command
    CLI_EXEC_CMD_OK,

    CLI_PROCESS_LINE_ERROR,          // error for cli_Process_Command
    CLI_PROCESS_LINE_OK,                

    CLI_PROCESS_TIME_ERROR,         // error for cli_Process_Time
    CLI_PROCESS_TIME_OK

} cli_Status_t;







#endif // __ERROR_H__
