/**
  ******************************************************************************
  * @file           : uart.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * nothing to write.
  ******************************************************************************
  */
  
#include "uart.h"
#include "log.h"

#define LOG_OUTPUT_TIMEOUT  (100U)

extern UART_HandleTypeDef huart4;

static void kputchar(char ch)
{
    if(huart4.gState != HAL_UART_STATE_READY)
    {
        HAL_UART_Abort(&huart4);
        __HAL_UNLOCK(&huart4);
    }
    HAL_UART_Transmit(&huart4, (uint8_t *)&ch, 1, LOG_OUTPUT_TIMEOUT);    
}

int uart_init(void)
{
    log_set_putchar(kputchar);
    return 0;
}
