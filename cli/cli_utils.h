#ifndef __CLI_UTILS_H__
#define __CLI_UTILS_H__

#include <stdio.h>

#include "error.h"

/*
 *********************************************************************************************************
 *                                            API FUNCTION 
 *********************************************************************************************************
 */

/*
* @brief   Parse the command string to int8 not using string.h (strcpy, strcmp, strtol ...)
* @param   *cmd: pointer to the command string
* @param   *value: pointer to the value
* @retval   ERROR_INVALID_VALUE: if the command is invalid  ERROR_VALID_VALUE_OK: if the command is valid
*/
cli_status_t cli_parse_int8(char *cmd, int8_t *value);

/*
* @brief   Parse the command string to uint8 not using string.h (strcpy, strcmp, strtol ...)
* @param   *cmd: pointer to the command string
* @param   *value: pointer to the value
* @retval  ERROR_INVALID_VALUE: if the command is invalid  ERROR_VALID_VALUE_OK: if the command is valid
*/
cli_status_t cli_parse_uint8(char *cmd, uint8_t *value);

/*
* @brief   Parse the command string to int16 not using string.h (strcpy, strcmp, strtol ...)
* @param   *cmd: pointer to the command string
* @param   *value: pointer to the value
* @retval  ERROR_INVALID_VALUE: if the command is invalid  ERROR_VALID_VALUE_OK: if the command is valid
*/
cli_status_t cli_parse_int16(char *cmd, int16_t *value);

/*
* @brief   Parse the command string to uint16 not using string.h (strcpy, strcmp, strtol ...)
* @param   *cmd: pointer to the command string
* @param   *value: pointer to the value
* @retval  ERROR_INVALID_VALUE: if the command is invalid  ERROR_VALID_VALUE_OK: if the command is valid
*/
cli_status_t cli_parse_uint16(char *cmd, uint16_t *value);

/*
* @brief   Parse the command string to int32 not using string.h (strcpy, strcmp, strtol ...)
* @param   *cmd: pointer to the command string
* @param   *value: pointer to the value
* @retval  ERROR_INVALID_VALUE: if the command is invalid  ERROR_VALID_VALUE_OK: if the command is valid
*/
cli_status_t cli_parse_int32(char *cmd, int32_t *value);

/*
* @brief   Parse the command string to uint32 not using string.h (strcpy, strcmp, strtol ...)
* @param   *cmd: pointer to the command string
* @param   *value: pointer to the value
* @retval  ERROR_INVALID_VALUE: if the command is invalid  ERROR_VALID_VALUE_OK: if the command is valid
*/
cli_status_t cli_parse_uint32(char *cmd, uint32_t *value);


#endif // __CLI_UTILS_H__
