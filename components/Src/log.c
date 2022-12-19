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
#include "service.h"

static log_t private_log = { 0 };
static TX_MUTEX private_locker = { 0 };

static void log_lock(void)
{
    tx_mutex_get(&private_locker, TX_WAIT_FOREVER);
}

static void log_unlock(void)
{
    tx_mutex_put(&private_locker);
}

int log_init(void)
{
    tx_mutex_create(&private_locker, "log_lock", TX_NO_INHERIT);
    
    private_log.level = LOG_TRACE;
    private_log.locker.lock = log_lock;
    private_log.locker.unlock = log_unlock;
    return 0;
}

int log_set_level(log_level_t level)
{
    int result = -1;
    if(level < LOG_UNKNOW)
    {
        private_log.level = level;
        result = 0;
    }
    return result;
}

int log_set_putchar(kputchar_t output)
{
    int result = -1;
    result = kprintf_putchar_register(output);
    return result;
}

int log_setprivate_locker(log_lock_t *locker)
{
    int result = -1;
    if(locker != TX_NULL)
    {
        private_log.locker.lock = locker->lock;
        private_log.locker.unlock = locker->unlock;
        result = 0;
    }
    return result;
}

void log_output(log_level_t level, const char *file, int line, const char *fmt, ...)
{
    va_list args;
    char buffer[512] = { NULL };
    size_t length = sizeof(buffer);
    ULONG tick = tx_time_get();
    
    private_log.locker.lock();
    if(private_log.level >= level)
    {
        ksnprintf(buffer, length, "[%ld][%s: %d] ", tick, file, line);
        kprintf("%s", buffer);
        kmemset(buffer, 0, length);
        va_start(args, fmt);
        kvsnprintf(buffer, length, fmt, args);
        va_end(args);
        kprintf("%s", buffer);
        kmemset(buffer, 0, length);
    }
    private_log.locker.unlock();
}

int log_deinit(void)
{
    private_log.level = LOG_UNKNOW;
    private_log.locker.lock = NULL;
    private_log.locker.unlock = NULL;
    return 0;
}
