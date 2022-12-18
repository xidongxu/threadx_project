/**
  ******************************************************************************
  * @file           : log.h
  * @brief          : Header for log.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * nothing to write.
  *
  ******************************************************************************
  */

#ifndef __LOG_H__
#define __LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "tx_api.h"
#include "kprintf.h"

/* Typedef  */
typedef enum _log_level
{
    LOG_TRACE   = 0x00,
    LOG_DEBUG   = 0x01,
    LOG_INFO    = 0x02,
    LOG_WARING  = 0x03,
    LOG_ERROR   = 0x04,
    LOG_UNKNOW  = 0x05,
} log_level_t;

#define log_trace(...)  log_output(LOG_TRACE,  __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...)  log_output(LOG_DEBUG,  __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...)   log_output(LOG_INFO,   __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...)   log_output(LOG_WARING, __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...)  log_output(LOG_ERROR,  __FILE__, __LINE__, __VA_ARGS__)

typedef struct _log_lock
{
    void (*lock)(void);
    void (*unlock)(void);
} log_lock_t;

typedef struct _log
{
    log_level_t level;
    log_lock_t locker;
} log_t;

/* Function */
int log_init(void);
int log_deinit(void);
int log_set_level(log_level_t level);
int log_set_putchar(kputchar_t output);
int log_set_locker(log_lock_t *locker);

void log_output(log_level_t level, const char *file, int line, const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* __LOG_H__ */
