/**
  ******************************************************************************
  * @file           : app_log.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * nothing to write.
  ******************************************************************************
  */
  
#include "app_log.h"
#include "log.h"

#define LOG_OUTPUT_TIMEOUT  (100U)

extern UART_HandleTypeDef huart4;

static void putstr(uint8_t *str, uint16_t len)
{
    if(huart4.gState != HAL_UART_STATE_READY)
    {
        HAL_UART_Abort(&huart4);
        __HAL_UNLOCK(&huart4);
    }
    HAL_UART_Transmit(&huart4, str, len, LOG_OUTPUT_TIMEOUT);
}

static void app_log_output(log_level_t level, const char *file, int line, const char *fmt, ...)
{
    char buffer[128] = { 0 };
    snprintf(buffer, sizeof(buffer), "[%s][%d]\r\n", file, line);
    putstr((uint8_t *)buffer, sizeof(buffer));
}

int app_log_init(void)
{
    log_set_output(app_log_output);
    return 0;
}
