#include "driver/screen.h"


static const uint8_t WIDTH = 80;
static const uint8_t HEIGHT = 25;
static const uint32_t VIDEO_BUF_BASE = 0xB8000;

static uint8_t currentx = 0;
static uint8_t currenty = 0;

void scr_size(uint8_t* width, uint8_t* height)
{
    if (width != 0)
    {
        *width = WIDTH;
    }

    if (height != 0)
    {
        *height = HEIGHT;
    }

}

void scr_char_at(char ch, uint8_t x, uint8_t y)
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

void scr_str_at(const char* str, uint8_t x, uint8_t y)
{
    if (str == 0)
    {
        return;
    }

    if (x >= WIDTH || y >= HEIGHT)
    {
        return;
    }

    uint8_t xpos = x;
    uint8_t ypos = y;

    const char* s = str;
    while(*s != 0)
    {
        if (*s == '\n')
        {
            newline(&xpos, &ypos);
        }
        else // non-control char
        {
            scr_char_at(*s, xpos, ypos);
            next(&xpos, &ypos);
        }

        s++;
    }
}


void scr_print(const char* str)
{
    const char* s = str;
    while(*s != 0)
    {
        if (*s != '\n')
        {
            scr_char_at(*s, currentx, currenty);
        }

        if (*s == '\n')
        {
            newline(&currentx, &currenty);
        }
        else
        {
            currentx++;
            if (currentx >= WIDTH)
            {
                newline(&currentx, &currenty);
            }
        }

        s++;
    }
}
