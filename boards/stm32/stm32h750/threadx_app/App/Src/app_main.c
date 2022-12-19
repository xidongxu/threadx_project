/**
  ******************************************************************************
  * @file           : user_main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * nothing to write.
  ******************************************************************************
  */
  
#include "app_main.h"
#include "log.h"
#include "tx_api.h"

static uint8_t thread1_stack[1024];
static uint8_t thread2_stack[1024];
static TX_THREAD thread1;
static TX_THREAD thread2;

void thread1_entry(ULONG thread_input)
{
	/* Enter into a forever loop. */
	while(1)
	{
        HAL_GPIO_WritePin(GPIOI, GPIO_PIN_8, GPIO_PIN_SET);
		tx_thread_sleep(700);
        HAL_GPIO_WritePin(GPIOI, GPIO_PIN_8, GPIO_PIN_RESET);
        tx_thread_sleep(300);
	}
}

void thread2_entry(ULONG thread_input)
{
    int count = 0;
    /* Enter into a forever loop. */
	while(1)
	{
		tx_thread_sleep(100);
        log_trace("hello world - %d\r\n", count);
        count++;
	}
}

void tx_application_define(void *first_unused_memory)
{
	/* Create my_thread! */
    tx_thread_create(&thread1, "Thread1", thread1_entry, 0x1234, thread1_stack, 1024, 3, 3, TX_NO_TIME_SLICE, TX_AUTO_START);
    tx_thread_create(&thread2, "Thread2", thread2_entry, 0x1234, thread2_stack, 1024, 3, 3, TX_NO_TIME_SLICE, TX_AUTO_START);
}
