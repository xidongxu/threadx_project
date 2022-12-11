#include "stm32h7xx_hal.h"
#include "tx_api.h"
#include "tx_initialize.h"
#include "tx_thread.h"
#include "tx_timer.h"


const uint32_t SYSTEM_CLOCK =  400000000;                   /* 系统主频 */
const uint32_t SYSTICK_CYCLES = ((SYSTEM_CLOCK / 1000) -1); /* 周期配置 */
extern VOID  _tx_timer_interrupt(VOID);

VOID _tx_initialize_low_level(VOID)
{
  /* 关闭中断 */
  __set_PRIMASK(1);

  /* 下面这两个用不上，直接注释掉 */    
  //_tx_initialize_unused_memory = __INITIAL_SP;
  //_tx_thread_system_stack_ptr = __Vectors;

  /* 配置滴答定时器 */
  SysTick_Config(SYSTICK_CYCLES);

  /* 设置SVC中断优先级并使能 */
  HAL_NVIC_SetPriority(SVCall_IRQn, 15, 0);
  HAL_NVIC_EnableIRQ(SVCall_IRQn);

  /* 设置PendSV中断优先级并使能 */
  HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);
  HAL_NVIC_EnableIRQ(PendSV_IRQn);

  /* 设置Systick中断优先级并使能 */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(SysTick_IRQn);	
}     

VOID _tx_thread_stack_error_handler(TX_THREAD *thread_ptr)
{

}

void SysTick_Handler(void)
{
  _tx_timer_interrupt();
}
