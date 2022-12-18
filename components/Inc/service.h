/**
  ******************************************************************************
  * @file           : service.h
  * @brief          : Header for service.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * nothing to write.
  *
  ******************************************************************************
  */

#ifndef __SERVICE_H__
#define __SERVICE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include <stdio.h>
#include <stdlib.h>

/* Function */
unsigned long long kpow(unsigned long long m, unsigned long long n);
int kstrlen(const char* str);
void *kmemset(void *str, int fill, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* __SERVICE_H__ */
