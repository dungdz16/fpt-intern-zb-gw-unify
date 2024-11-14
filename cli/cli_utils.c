#include <stdio.h>
#include <stdint.h>

// #include "common/error.h"
#include "cli_utils.h"
#include "cli.h"
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

cli_status_t cli_parse_int8(char *cmd, int8_t *value)
{
    int8_t result = 1;  // default is valid command
    int8_t sign = 1;    // default is positive number
    int16_t val = 0;   // default value is 0, use int16_t to avoid overflow
    char *p = cmd;      // pointer to the command string

    // Handle optional sign
    if (*p == '-') {
        sign = -1;
        p++;
    } else if (*p == '+') {
        p++;
    }

    // Check if the string is empty after sign
    if (*p == '\0') {
        result = 0;
        return ERROR_INVALID_VALUE;
    }

    // Process each character
    while (*p != '\0') {
        if (*p >= '0' && *p <= '9') {
            val = val * 10 + (*p - '0');

            // Check for overflow
            if ((sign == 1 && val > INT8_MAX) || (sign == -1 && -val < INT8_MIN)) {
                result = 0;
                break;
            }
            p++;
        } else {
            // Invalid character encountered
            result = 0;
            break;
        }
    }

    if (result == 1) {
        *value = (int8_t)(sign * val);
    }

    if (result == 0) {
        return ERROR_INVALID_VALUE;
    }
    else {
        return ERROR_VALID_VALUE_OK;
    }
}

/*
* @brief   Parse the command string to uint8 not using string.h (strcpy, strcmp, strtol ...)
* @param   *cmd: pointer to the command string
* @param   *value: pointer to the value
* @retval  ERROR_INVALID_VALUE: if the command is invalid  ERROR_VALID_VALUE_OK: if the command is valid
*/

cli_status_t cli_parse_uint8(char *cmd, uint8_t *value)
{
    int8_t result = 1;  // default is valid command
    uint16_t val = 0;   // default value is 0, use uint16_t to avoid overflow
    char *p = cmd;      // pointer to the command string

    // Check if the string is empty
    if (*p == '\0') {
        result = 0;
        return ERROR_INVALID_VALUE;
    }

    // Process each character
    while (*p != '\0') {
        if (*p >= '0' && *p <= '9') {
            val = val * 10 + (*p - '0');

            // Check for overflow
            if (val > UINT8_MAX) {
                result = 0;
                break;
            }
            p++;
        } else {
            // Invalid character encountered
            result = 0;
            break;
        }
    }

    if (result == 1) {
        *value = (uint8_t)val;
    }

    if (result == 0) {
        return ERROR_INVALID_VALUE;
    }
    else {
        return ERROR_VALID_VALUE_OK;
    }
}

/*
* @brief   Parse the command string to int16 not using string.h (strcpy, strcmp, strtol ...)
* @param   *cmd: pointer to the command string
* @param   *value: pointer to the value
* @retval  ERROR_INVALID_VALUE: if the command is invalid  ERROR_VALID_VALUE_OK: if the command is valid
*/

cli_status_t cli_parse_int16(char *cmd, int16_t *value)
{
    int8_t result = 1;  // default is valid command
    int8_t sign = 1;    // default is positive number
    int32_t val = 0;   // default value is 0, use int32_t to avoid overflow
    char *p = cmd;      // pointer to the command string

    // Handle optional sign
    if (*p == '-') {
        sign = -1;
        p++;
    } else if (*p == '+') {
        p++;
    }

    // Check if the string is empty after sign
    if (*p == '\0') {
        result = 0;
        return ERROR_INVALID_VALUE;
    }

    // Process each character
    while (*p != '\0') {
        if (*p >= '0' && *p <= '9') {
            val = val * 10 + (*p - '0');

            // Check for overflow
            if ((sign == 1 && val > INT16_MAX) || (sign == -1 && -val < INT16_MIN)) {
                result = 0;
                break;
            }
            p++;
        } else {
            // Invalid character encountered
            result = 0;
            break;
        }
    }

    if (result == 1) {
        *value = (int16_t)(sign * val);
    }

    if (result == 0) {
        return ERROR_INVALID_VALUE;
    }
    else {
        return ERROR_VALID_VALUE_OK;
    }
}

/*
* @brief   Parse the command string to uint16 not using string.h (strcpy, strcmp, strtol ...)
* @param   *cmd: pointer to the command string
* @param   *value: pointer to the value
* @retval  ERROR_INVALID_VALUE: if the command is invalid  ERROR_VALID_VALUE_OK: if the command is valid
*/

cli_status_t cli_parse_uint16(char *cmd, uint16_t *value)
{
    int8_t result = 1;  // default is valid command
    uint32_t val = 0;   // default value is 0, use uint32_t to avoid overflow
    char *p = cmd;      // pointer to the command string

    // Check if the string is empty
    if (*p == '\0') {
        result = 0;
        return ERROR_INVALID_VALUE;
    }

    // Process each character
    while (*p != '\0') {
        if (*p >= '0' && *p <= '9') {
            val = val * 10 + (*p - '0');

            // Check for overflow
            if (val > UINT16_MAX) {
                result = 0;
                break;
            }
            p++;
        } else {
            // Invalid character encountered
            result = 0;
            break;
        }
    }

    if (result == 1) {
        *value = (uint16_t)val;
    }

    if (result == 0) {
        return ERROR_INVALID_VALUE;
    }
    else {
        return ERROR_VALID_VALUE_OK;
    }
}

/*
* @brief   Parse the command string to int32 not using string.h (strcpy, strcmp, strtol ...)
* @param   *cmd: pointer to the command string
* @param   *value: pointer to the value
* @retval  ERROR_INVALID_VALUE: if the command is invalid  ERROR_VALID_VALUE_OK: if the command is valid
*/

cli_status_t cli_parse_int32(char *cmd, int32_t *value)
{
    int8_t result = 1;  // default is valid command
    int8_t sign = 1;    // default is positive number
    int64_t val = 0;   // default value is 0, use int64_t to avoid overflow
    char *p = cmd;      // pointer to the command string

    // Handle optional sign
    if (*p == '-') {
        sign = -1;
        p++;
    } else if (*p == '+') {
        p++;
    }

    // Check if the string is empty after sign
    if (*p == '\0') {
        result = 0;
        return ERROR_INVALID_VALUE;
    }

    // Process each character
    while (*p != '\0') {
        if (*p >= '0' && *p <= '9') {
            val = val * 10 + (*p - '0');

            // Check for overflow
            if ((sign == 1 && val > INT32_MAX) || (sign == -1 && -val < INT32_MIN)) {
                result = 0;
                break;
            }
            p++;
        } else {
            // Invalid character encountered
            result = 0;
            break;
        }
    }

    if (result == 1) {
        *value = (int32_t)(sign * val);
    }

    if (result == 0) {
        return ERROR_INVALID_VALUE;
    }
    else {
        return ERROR_VALID_VALUE_OK;
    }
}

/*
* @brief   Parse the command string to uint32 not using string.h (strcpy, strcmp, strtol ...)
* @param   *cmd: pointer to the command string
* @param   *value: pointer to the value
* @retval  ERROR_INVALID_VALUE: if the command is invalid  ERROR_VALID_VALUE_OK: if the command is valid
*/

cli_status_t cli_parse_uint32(char *cmd, uint32_t *value)
{
    int8_t result = 1;  // default is valid command
    uint64_t val = 0;   // default value is 0, use uint64_t to avoid overflow
    char *p = cmd;      // pointer to the command string

    // Check if the string is empty
    if (*p == '\0') {
        result = 0;
        return ERROR_INVALID_VALUE;
    }

    // Process each character
    while (*p != '\0') {
        if (*p >= '0' && *p <= '9') {
            val = val * 10 + (*p - '0');

            // Check for overflow
            if (val > UINT32_MAX) {
                result = 0;
                break;
            }
            p++;
        } else {
            // Invalid character encountered
            result = 0;
            break;
        }
    }

    if (result == 1) {
        *value = (uint32_t)val;
    }

    if (result == 0) {
        return ERROR_INVALID_VALUE;
    }
    else {
        return ERROR_VALID_VALUE_OK;
    }
}

