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

typedef struct kbuffer {
    char *buff;
    size_t size;
    size_t indx;
} kbuffer_t;

typedef void (*kputchar_t)(char ch);

/* Function */
size_t kvsnprintf(char *buffer, size_t size, const char *fmt, va_list args);
int ksnprintf(char *buff, size_t size, const char *fmt, ...);
int kprintf(const char *fmt, ...);

int kprintf_putchar_register(kputchar_t func);

#ifdef __cplusplus
}
#endif

#endif /* __KPRINTF_H__ */
