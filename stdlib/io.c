#include "kstdlib.h"

#include "driver/screen.h"

void putchar(char ch)
{
    scr_putchar(ch);
}

void puts(const char* str)
{
    scr_puts(str);
}