#include "driver/screen.h"


static const uint8_t WIDTH = 80;
static const uint8_t HEIGHT = 25;

static uint8_t currentx = 0;
static uint8_t currenty = 0;

static void newline(uint8_t* x, uint8_t* y)
{
    *x = 0;
    (*y)++;
    if (*y >= HEIGHT)
    {
        *y = 0;
    }
}

static void next(uint8_t* x, uint8_t* y)
{
    (*x)++;
    if (*x >= WIDTH)
    {
        newline(x, y);
    }
}

static void scr_putchar_at(char ch, uint8_t x, uint8_t y)
{
    if (x >= WIDTH || y >= HEIGHT)
    {
        return;
    }

    /*
     * a chararcter is represented by uint16_t
     * lowest 8 bit is ASCII and high 8 bits are color
     */
    volatile uint16_t * video_buffer = (volatile uint16_t*) 0xB8000;
    const uint8_t white_color = 15;

    video_buffer[x + WIDTH * y] = ch | white_color << 8;
}

void scr_putchar(char ch)
{
    if (ch == '\n')
    {
        newline(&currentx, &currenty);
    }
    else // non-control char
    {
        scr_putchar_at(ch, currentx, currenty);
        next(&currentx, &currenty);
    }
}

void scr_puts(const char* str)
{
    const char* s = str;
    while(*s != 0)
    {
        scr_putchar(*s);
        s++;
    }
}
