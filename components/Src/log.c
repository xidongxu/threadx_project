/**
  ******************************************************************************
  * @file           : log.c
  * @brief          : log program body
  ******************************************************************************
  * @attention
  *
  * nothing to write.
  ******************************************************************************
  */
  
#include "log.h"

static log_t _log;
static TX_MUTEX _locker;

static void log_lock(void)
{
    tx_mutex_get(&_locker, TX_WAIT_FOREVER);
}

static void log_unlock(void)
{
    tx_mutex_put(&_locker);
}

int log_init(void)
{
    tx_mutex_create(&_locker, "log_lock", TX_NO_INHERIT);
    
    _log.level = LOG_TRACE;
    _log.output = TX_NULL;
    _log.locker.lock = log_lock;
    _log.locker.unlock = log_unlock;
    _log.data = TX_NULL;
    return 0;
}

int log_set_level(log_level_t level)
{
    int result = -1;
    if(level < LOG_UNKNOW)
    {
        _log.level = level;
        result = 0;
    }
    return result;
}

int log_set_output(log_output_t output)
{
    int result = -1;
    if(output != TX_NULL)
    {
        _log.output = output;
        result = 0;
    }
    return result;
}

int log_set_locker(log_lock_t *locker)
{
    int result = -1;
    if(locker != TX_NULL)
    {
        _log.locker.lock = locker->lock;
        _log.locker.unlock = locker->unlock;
        result = 0;
    }
    return result;
}

void log_output(log_level_t level, const char *fmt, ...)
{

    _log.locker.lock();
    if((_log.level > level) && (_log.output != TX_NULL))
    {
        va_list args;
        va_start(args, fmt);
        _log.output(level, fmt, args);
        va_end(args);
    }
    _log.locker.unlock();
}

int log_deinit(void)
{
    _log.level = LOG_UNKNOW;
    _log.output = NULL;
    _log.locker.lock = NULL;
    _log.locker.unlock = NULL;
    _log.data = NULL;
    return 0;
}
