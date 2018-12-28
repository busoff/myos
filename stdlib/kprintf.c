#include "kstdlib.h"
#include <stdarg.h>
#include <stdbool.h>
#include "driver/screen.h"

/**
 * NOTE!!!!  Only support print up to 63 characters. if the size of result excces,
 * this function won't behaviour correctly. 
 */
static char* convert(uint32_t number, uint8_t base, char padding, uint8_t len_spec)
{
    static const char represents[]= "0123456789ABCDEF";
    static char buffer[64];
    buffer[sizeof(buffer) -1] = '\0';
    char* p = &buffer[sizeof(buffer) -1];

    do
    {
        *(--p) = represents[number%base];
        number = number/base;
    }while (number > 0);

    uint8_t len = &buffer[sizeof(buffer)-1] - p;
    if (len < len_spec) {
        for(uint8_t i = 0; i < len_spec - len; ++i)
            *(--p) = padding;
    }
    return p;
}

void kprintf(const char *format, ...)
{
    va_list arg;
    va_start(arg, format);

    for(const char* ch = format; *ch != '\0'; ch++)
    {
        while (*ch != '%')
        {
            putchar(*ch);
            ch++;
            if( *ch == '\0')
            {
                return;
            }
        }

        ch++;
        if (*ch == '\0')
        {
            return;
        }

        /* calcualte padding size */
        char padding = ' ';
        uint8_t len_spec = 0;
        if (*ch == '0') {
            padding = '0';
            
            while(isdigit(*(++ch))) {
                len_spec *= 10;
                len_spec += *ch - '0';
            }
        }

        switch (*ch)
        {
            case 's':
            {
                char* s = va_arg(arg,char *);
                puts(s);
                break;
            }

            case 'c':
            {
                char c = va_arg(arg, int);
                putchar(c);
                break;
            }

            case 'x':
            {
                uint32_t n = va_arg(arg, uint32_t);
                puts(convert(n, 16, padding, len_spec));
                break;
            }
            case 'd':
            {
                int32_t v = va_arg(arg, int);
                if (v<0)
                {
                    putchar('-');
                    puts(convert(-v, 10, padding, len_spec));
                }
                else
                {
                    puts(convert(v, 10, padding, len_spec));
                }
                break;
            }
            default:
                /* unknown format */
                putchar('%');
                putchar(*ch);
        }
    }
}