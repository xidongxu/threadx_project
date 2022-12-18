/**
  ******************************************************************************
  * @file           : kprintf.c
  * @brief          : kprintf program body
  ******************************************************************************
  * @attention
  *
  * nothing to write.
  ******************************************************************************
  */
  
#include "kprintf.h"
#include "service.h"

static kputchar_t kputchar = NULL;
static kbuffer_t kbuffer = { NULL };

int kprintf_putchar_register(kputchar_t func)
{
    kputchar = func;
    return 0;
}

static void kbuff_init(char *buff, size_t size)
{
    kbuffer.buff = buff;
    kbuffer.size = size;
    kbuffer.indx = 0;
}

static void kbuff_push(char ch)
{
    if(kbuffer.buff == NULL)
    {
        return;
    }
    if(kbuffer.indx == (kbuffer.size - 1))
    {
        kbuffer.buff[kbuffer.indx] = '\0';
        return;
    }
    else
    {
        kbuffer.buff[kbuffer.indx] = ch;
    }
    kbuffer.indx++;
}

static void kbuff_deinit(void)
{
    kbuffer.buff = NULL;
    kbuffer.size = 0;
    kbuffer.indx = 0;
}

size_t kvsnprintf(char *buffer, size_t size, const char *fmt, va_list args)
{
    char *pstr = (char *)fmt;
    size_t val_ret = 0;
    
    int val_int = 0;
    int val_cnt = 0;
    int val_flg = 0;
    unsigned long val_seg = 0;
    unsigned long val_hex = 0;
    unsigned long val_tmp = 0;
    char *val_str = NULL;
    double val_flo = 0.0;
    long long val_lld = 0;
    long long val_lls = 0;
    long val_lod = 0;
    long val_los = 0;
    
    kbuff_init(buffer, size);
    
    while(*pstr != '\0')
    {
        switch (*pstr)
        {
            case ' ' : kbuff_push(*pstr); val_ret += 1; break;
            case '\t': kbuff_push(*pstr); val_ret += 4; break;
            case '\r': kbuff_push(*pstr); val_ret += 1; break;
            case '\n': kbuff_push(*pstr); val_ret += 1; break;
            case '%' : 
            {
                pstr++;
                switch (*pstr)
                {
                    case '%': 
                    {
                        kbuff_push('%'); 
                        pstr++; 
                        val_ret++; 
                        continue;
                    }
                    case 'c': 
                    {
                        val_int = va_arg(args, int); 
                        kbuff_push((char)val_int); 
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
                            kbuff_push('-'); 
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
                            val_seg = val_int / kpow(10, val_cnt - 1);
                            val_int = val_int % kpow(10, val_cnt - 1);
                            kbuff_push((char)val_seg + '0');
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
                            kbuff_push('-');
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
                            val_seg = val_int / kpow(8, val_cnt - 1);
                            val_int = val_int % kpow(8, val_cnt - 1);
                            kbuff_push((char)val_seg + '0');
                            val_cnt--;
                        }
                        pstr++;
                        continue;
                    }
                    case 'X':
                    {
                        val_flg = 1;
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
                            val_seg = val_hex / kpow(16, val_cnt - 1);
                            val_hex = val_hex % kpow(16, val_cnt - 1);
                            if(val_seg <= 9)
                            {
                                kbuff_push((char)val_seg + '0');
                            }
                            else
                            {
                                if(val_flg > 0)
                                {
                                    kbuff_push((char)val_seg - 10 + 'A');
                                }
                                else
                                {
                                    kbuff_push((char)val_seg - 10 + 'a');
                                }
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
                            val_seg = val_int / kpow(2, val_cnt - 1);
                            val_int = val_int % kpow(2, val_cnt - 1);
                            kbuff_push((char)val_seg + '0');
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
                            kbuff_push(*val_str);
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
                            val_seg = val_tmp / kpow(10, val_cnt - 1);
                            val_tmp = val_tmp % kpow(10, val_cnt - 1);
                            kbuff_push((char)val_seg + '0');
                            val_cnt--;
                        }
                        kbuff_push('.');
                        val_ret++;
                        val_flo = val_flo * 1000000;
                        val_cnt = 6;
                        val_tmp = (int)val_flo;
                        while(val_cnt)
                        {
                            val_seg = val_tmp / kpow(10, val_cnt - 1);
                            val_tmp = val_tmp % kpow(10, val_cnt - 1);
                            kbuff_push((char)val_seg + '0');
                            val_cnt--;
                        }
                        val_ret += 6;
                        pstr++;
                        continue;
                    }
                    case 'l':
                    {
                        pstr++;
                        if (*pstr == 'l')
                        {
                            pstr++;
                            // %lld
                            if (*pstr == 'd')
                            {
                                val_lld = va_arg(args, long long); 
                                if(val_lld < 0) 
                                { 
                                    val_lld = -val_lld;
                                    kbuff_push('-'); 
                                    val_ret++; 
                                }
                                val_lls = val_lld;
                                if(val_lld)
                                {
                                    while(val_lls)
                                    {
                                        val_cnt++;
                                        val_lls = val_lls / 10;
                                    }
                                }
                                else
                                {
                                    val_cnt = 1;
                                }
                                val_ret += val_cnt;
                                while(val_cnt)
                                {
                                    val_lls = val_lld / kpow(10, val_cnt - 1);
                                    val_lld = val_lld % kpow(10, val_cnt - 1);
                                    kbuff_push((char)val_lls + '0');
                                    val_cnt--;
                                }
                                pstr++;
                            }
                            // %ll?
                            else
                            {
                                kbuff_push('%');
                                kbuff_push('l');
                                kbuff_push('l');
                                val_ret += 3;
                            }
                        }
                        // %ld
                        else if (*pstr == 'd')
                        {
                            val_lod = va_arg(args, long); 
                            if(val_lod < 0) 
                            { 
                                val_lod = -val_lod;
                                kbuff_push('-'); 
                                val_ret++; 
                            }
                            val_los = val_lod;
                            if(val_lod)
                            {
                                while(val_los)
                                {
                                    val_cnt++;
                                    val_los = val_los / 10;
                                }
                            }
                            else
                            {
                                val_cnt = 1;
                            }
                            val_ret += val_cnt;
                            while(val_cnt)
                            {
                                val_los = val_lod / kpow(10, val_cnt - 1);
                                val_lod = val_lod % kpow(10, val_cnt - 1);
                                kbuff_push((char)val_los + '0');
                                val_cnt--;
                            }
                            pstr++;
                        }
                        // %l?
                        else
                        {
                            kbuff_push('%');
                            kbuff_push('l');
                            val_ret += 2;
                        }
                        continue;
                    }
                    case 'p':
                    {
                        //%p
                    }
                    default:
                    {
                        kbuff_push(' ');
                        val_ret++;
                        continue;
                    }
                }
            } 
            default:
            {
                kbuff_push(*pstr);
                val_ret++;
                break;
            }
        }
        pstr++;
    }

    kbuff_deinit();
    return val_ret;
}

int ksnprintf(char *buff, size_t size, const char *fmt, ...)
{
    int length = 0;
    va_list args;
    
    va_start(args, fmt);
    length = kvsnprintf(buff, size, fmt, args);
    va_end(args);
    
    return length;
}

int kprintf(const char *fmt, ...)
{
    static char buffer[512] = { NULL };
    size_t size = sizeof(buffer);
    size_t length;
    size_t index;
    va_list args;

    va_start(args, fmt);
    length = kvsnprintf(buffer, (size - 1), fmt, args);
    va_end(args);
    
    if(kputchar != NULL)
    {
        for(index = 0; index < length; index++)
        {
            kputchar(buffer[index]);
        }
    }
    
    kmemset(buffer, 0, size);
    return length;
}
