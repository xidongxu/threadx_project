/**
  ******************************************************************************
  * @file           : service.c
  * @brief          : service program body
  ******************************************************************************
  * @attention
  *
  * nothing to write.
  ******************************************************************************
  */
  
#include "service.h"

unsigned long long kpow(unsigned long long m, unsigned long long n)
{
    unsigned long long i = 0, ret = 1;
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

int kstrlen(const char* str)
{
    const char* start = str;
    const char* end = NULL;
    while (*str != '\0')
    {
        str++;
        end = str;
    }
    return (end - start);
}

void *kmemset(void *str, int fill, size_t size)
{
    char *pstr = (char *)str;

    while (size--)
    {
        *pstr++ = fill;
    }
    return str;
}
