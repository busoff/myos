#include "kstdlib.h"
#include <stdarg.h>
#include "driver/screen.h"

static char* convert(uint32_t number, uint8_t base)
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
        if (ch == '\0')
        {
            return;
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
                puts(convert(n, 16));
                break;
            }
            case 'd':
            {
                int32_t v = va_arg(arg, int);
                if (v<0)
                {
                    putchar('-');
                    puts(convert(-v, 10));
                }
                else
                {
                    puts(convert(v, 10));
                }
                break;
            }
            default:
            /* known format */
            putchar('%');
            putchar(*ch);
        }
    }
}