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

/* Typedef  */
typedef enum _log_level
{
    LOG_TRACE   = 0x00,
    LOG_INFO    = 0x01,
    LOG_WARING  = 0x02,
    LOG_ERROR   = 0x03,
    LOG_UNKNOW  = 0x04,
} log_level_t;

typedef struct _log_lock
{
    void (*lock)(void);
    void (*unlock)(void);
} log_lock_t;

typedef struct _log log_t;
typedef void (*log_output_t)(log_level_t level, const char *fmt, ...);

struct _log
{
    log_level_t level;
    log_lock_t locker;
    log_output_t output;
    void *data;
};

/* Function */
int log_init(void);
int log_deinit(void);
int log_set_level(log_level_t level);
int log_set_output(log_output_t output);
int log_set_locker(log_lock_t *locker);

void log_output(log_level_t level, const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* __LOG_H__ */
