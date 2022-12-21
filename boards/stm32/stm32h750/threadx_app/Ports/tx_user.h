/**
  ******************************************************************************
  * @file           : tx_user.h
  * @brief          : Header for threadx user file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * nothing to write.
  *
  ******************************************************************************
  */

#ifndef __TX_USER_H__
#define __TX_USER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* USER CODE BEGIN DEFINE */

#ifndef TX_ENABLE_STACK_CHECKING
#define TX_ENABLE_STACK_CHECKING
#endif

#ifndef TX_ENABLE_FPU_SUPPORT
#define TX_ENABLE_FPU_SUPPORT
#endif

#ifndef TX_INCLUDE_USER_DEFINE_FILE
#define TX_INCLUDE_USER_DEFINE_FILE
#endif

/* USER CODE END DEFINE */

#ifdef __cplusplus
}
#endif

#endif /* __TX_USER_H__ */
