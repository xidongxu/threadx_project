/**
  ******************************************************************************
  * @file           : kprintf.h
  * @brief          : Header for kprintf.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * nothing to write.
  *
  ******************************************************************************
  */

#ifndef __KPRINTF_H__
#define __KPRINTF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "stdarg.h"
#include "stdlib.h"

typedef void (*kputchar_t)(char ch);

/* Function */
int kprintf(const char *str, ...);
int kprintf_output_register(kputchar_t func);

#ifdef __cplusplus
}
#endif

#endif /* __KPRINTF_H__ */
