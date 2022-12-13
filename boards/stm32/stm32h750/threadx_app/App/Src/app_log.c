/**
  ******************************************************************************
  * @file           : app_log.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * nothing to write.
  ******************************************************************************
  */
  
#include "app_log.h"
#include "log.h"

#define LOG_OUTPUT_TIMEOUT  (100U)

extern UART_HandleTypeDef huart4;

static void kputstr(uint8_t *str, uint16_t len)
{
    if(huart4.gState != HAL_UART_STATE_READY)
    {
        HAL_UART_Abort(&huart4);
        __HAL_UNLOCK(&huart4);
    }
    HAL_UART_Transmit(&huart4, str, len, LOG_OUTPUT_TIMEOUT);
}

unsigned long kmpown(unsigned long m, unsigned long n)
{
    unsigned long i = 0, ret = 1;
    if (n < 0) 
    {
        return 0;
    }
    for (i = 0; i < n; i++)
    {
        ret *= m;
    }
    return ret;
}


int kstrlen(char* str)
{
    char* start = str;
    char* end = NULL;
    while (*str != '\0')
    {
        str++;
        end = str;
    }
    return (end - start);
}


static void kputchar(char ch)
{
    if(huart4.gState != HAL_UART_STATE_READY)
    {
        HAL_UART_Abort(&huart4);
        __HAL_UNLOCK(&huart4);
    }
    HAL_UART_Transmit(&huart4, (uint8_t *)&ch, 1, LOG_OUTPUT_TIMEOUT);    
}

static int kprintf(const char *str, ...)
{
    char *pstr = (char *)str;
    int val_ret = 0;
    int val_int = 0;
    int val_cnt = 0;
    unsigned long val_seg = 0;
    unsigned long val_hex = 0;
    unsigned long val_tmp = 0;
    char *val_str = NULL;
    double val_flo = 0.0;
    
    va_list args;
    va_start(args, str);
    
    while(*pstr != '\0')
    {
        switch (*pstr)
        {
            case ' ' : kputchar(*pstr); val_ret += 1; break;
            case '\t': kputchar(*pstr); val_ret += 4; break;
            case '\r': kputchar(*pstr); val_ret += 1; break;
            case '\n': kputchar(*pstr); val_ret += 1; break;
            case '%' : 
            {
                pstr++;
                switch (*pstr)
                {
                    case '%': 
                    {
                        kputchar('%'); 
                        pstr++; 
                        val_ret++; 
                        continue;
                    }
                    case 'c': 
                    {
                        val_int = va_arg(args, int); 
                        kputchar((char)val_int); 
                        pstr++; 
                        val_ret++; 
                        continue;
                    }
                    case 'd' : 
                    {
                        val_int = va_arg(args, int); 
                        if(val_int < 0) 
                        { 
                            val_int = -val_int;
                            kputchar('-'); 
                            val_ret++; 
                        }
                        val_seg = val_int;
                        if(val_int)
                        {
                            while(val_seg)
                            {
                                val_cnt++;
                                val_seg = val_seg / 10;
                            }
                        }
                        else
                        {
                            val_cnt = 1;
                        }
                        val_ret += val_cnt;
                        while(val_cnt)
                        {
                            val_seg = val_int / kmpown(10, val_cnt - 1);
                            val_int = val_int % kmpown(10, val_cnt - 1);
                            kputchar((char)val_seg + '0');
                            val_cnt--;
                        }
                        pstr++;
                        continue;
                    }
                    case 'o':
                    {
                        val_int = va_arg(args, int);
                        if(val_int < 0)
                        {
                            val_int = -val_int;
                            kputchar('-');
                            val_ret++;
                        }
                        val_seg = val_int;
                        if(val_int)
                        {
                            while(val_seg)
                            {
                                val_cnt++;
                                val_seg = val_seg / 8;
                            }
                        }
                        else
                        {
                            val_cnt = 1;
                        }
                        val_ret += val_cnt;
                        while(val_cnt)
                        {
                            val_seg = val_int / kmpown(8, val_cnt - 1);
                            val_int = val_int % kmpown(8, val_cnt - 1);
                            kputchar((char)val_seg + '0');
                            val_cnt--;
                        }
                        pstr++;
                        continue;
                    }
                    case 'x':
                    {
                        val_hex = va_arg(args, unsigned long);
                        val_seg = val_hex;
                        if(val_hex)
                        {
                            while(val_seg)
                            {
                                val_cnt++;
                                val_seg = val_seg / 16;
                            }
                        }
                        else
                        {
                            val_cnt = 1;
                        }
                        val_ret += val_cnt;
                        while(val_cnt)
                        {
                            val_seg = val_hex / kmpown(16, val_cnt - 1);
                            val_hex = val_hex % kmpown(16, val_cnt - 1);
                            if(val_seg <= 9)
                            {
                                kputchar((char)val_seg + '0');
                            }
                            else
                            {
                                kputchar((char)val_seg - 10 + 'a');
                            }
                            val_cnt--;
                        }
                        pstr++;
                        continue;
                    }
                    case 'b':
                    {
                        val_int = va_arg(args, int);
                        val_seg = val_int;
                        if(val_int)
                        {
                            while(val_seg)
                            {
                                val_cnt++;
                                val_seg = val_seg / 2;
                            }
                        }
                        else
                        {
                            val_cnt = 1;
                        }
                        val_ret += val_cnt;
                        while(val_cnt)
                        {
                            val_seg = val_int / kmpown(2, val_cnt - 1);
                            val_int = val_int % kmpown(2, val_cnt - 1);
                            kputchar((char)val_seg + '0');
                            val_cnt--;
                        }
                        pstr++;
                        continue;
                    }
                    case 's':
                    {
                        val_str = va_arg(args, char*);
                        val_ret = val_ret + kstrlen(val_str);
                        while(*val_str)
                        {
                            kputchar(*val_str);
                            val_str++;
                        }
                        pstr++;
                        continue;
                    }
                    case 'f':
                    {
                        val_flo = va_arg(args, double);
                        val_seg = (unsigned long)val_flo;
                        val_tmp = val_seg;
                        val_flo = val_flo - val_seg;
                        if(val_seg)
                        {
                            while(val_seg)
                            {
                                val_cnt--;
                                val_seg = val_seg / 10;
                            }
                        }
                        else
                        {
                            val_cnt = 1;
                        }
                        val_ret += val_cnt;
                        while(val_cnt)
                        {
                            val_seg = val_tmp / kmpown(10, val_cnt - 1);
                            val_tmp = val_tmp % kmpown(10, val_cnt - 1);
                            kputchar((char)val_seg + '0');
                            val_cnt--;
                        }
                        kputchar('.');
                        val_ret++;
                        val_flo = val_flo * 1000000;
                        val_cnt = 6;
                        val_tmp = (int)val_flo;
                        while(val_cnt)
                        {
                            val_seg = val_tmp / kmpown(10, val_cnt - 1);
                            val_tmp = val_tmp % kmpown(10, val_cnt - 1);
                            kputchar((char)val_seg + '0');
                            val_cnt--;
                        }
                        val_ret += 6;
                        pstr++;
                        continue;
                    }
                    default:
                    {
                        kputchar(' ');
                        val_ret++;
                        continue;
                    }
                }
            } 
            default:
            {
                kputchar(*pstr);
                val_ret++;
                break;
            }
        }
        pstr++;
    }
    
    va_end(args);
    return val_ret;
}

static void app_log_output(log_level_t level, const char *file, int line, const char *fmt, ...)
{
    kprintf("[%s][%d] - %s\r\n", file, line, "hello world");
}

int app_log_init(void)
{
    log_set_output(app_log_output);
    return 0;
}
