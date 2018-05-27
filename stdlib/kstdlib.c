#include "kstdlib.h"

#include <stdbool.h>

void memset(void* buffer, size_t len, uint8_t value)
{
    if (buffer == 0) return;

    uint8_t* b = (uint8_t*) buffer;
    for (size_t i = 0; i < len; ++i)
    {
        b[i] = value;
    }
}

void halt()
{
    while(true)
    {}
}