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
#include "tx_api.h"
#include <stdint.h>
#include <stdio.h>

static uint8_t thread1_stack[4096];
static uint8_t thread2_stack[4096];
static TX_THREAD thread1;
static TX_THREAD thread2;

void thread_stack_error_handler(TX_THREAD *thread_ptr)
{
    printf("\r\n");
    printf("------------------ thread stack error. ------------------\r\n");
    const char *thread_name = thread_ptr->tx_thread_name;
    ULONG thread_prio= (ULONG)(thread_ptr->tx_thread_priority);
    ULONG stack_size = (ULONG)(thread_ptr->tx_thread_stack_size);
    ULONG stack_curr = (ULONG)((ULONG)thread_ptr->tx_thread_stack_end - (ULONG)thread_ptr->tx_thread_stack_ptr);
    ULONG stack_used = (ULONG)((ULONG)thread_ptr->tx_thread_stack_end - (ULONG)thread_ptr->tx_thread_stack_highest_ptr);
    printf("\r\n");
    printf("stack_end = %p\r\n", thread_ptr->tx_thread_stack_end);
    printf("stack_ptr = %p\r\n", thread_ptr->tx_thread_stack_ptr);
    printf("stack_max = %p\r\n", thread_ptr->tx_thread_stack_highest_ptr);
    printf("\r\n");
    printf("prio   stack_size   stack_use    stack_max    thread_name \r\n");
    printf(" %02ld      %05ld        %05ld        %05ld       %-8.8s  \r\n", \
         thread_prio, stack_size, stack_curr, stack_used, thread_name);
    printf("\r\n");
    while(1);
}

void thread1_entry(ULONG thread_input)
{
    int count = 0;
	/* Enter into a forever loop. */
	while(1)
	{
        tx_thread_sleep(10);
        printf("thread1: hello world - %d\r\n", count);
        count++;
	}
}

void thread2_entry(ULONG thread_input)
{
    int count = 0;
    /* Enter into a forever loop. */
	while(1)
	{
		tx_thread_sleep(10);
        printf("thread2: hello world - %d\r\n", count);
        count++;
	}
}

void tx_application_define(void *first_unused_memory)
{
    tx_thread_stack_error_notify(thread_stack_error_handler);
	/* Create my_thread! */
    tx_thread_create(&thread1, "Thread1", thread1_entry, 0x1234, thread1_stack, sizeof(thread1_stack), 3, 3, TX_NO_TIME_SLICE, TX_AUTO_START);
    tx_thread_create(&thread2, "Thread2", thread2_entry, 0x1234, thread2_stack, sizeof(thread2_stack), 3, 3, TX_NO_TIME_SLICE, TX_AUTO_START);
}

#ifndef TX_ENABLE_STACK_CHECKING
void _tx_thread_stack_error_handler(void)
{

}
#endif /* TX_ENABLE_STACK_CHECKING */
