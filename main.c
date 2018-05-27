#include <stdint.h>
#include <stddef.h>

#include "gdt.h"
#include "idt.h"
#include "screen.h"

// /**
//  * @brief print a char at a given position on a screen 80 * 25
//  */
// void printAt(const char* str, uint8_t x, uint8_t y)
// {
//     if (str == 0)
//     {
//         return;
//     }

//     if ( x >= 80 || y >= 25)
//     {
//         return;
//     }

//     /* a chararcter shown on screen is represented as uint16_t
//      * lowest 8 bit is ASCII and high 8 bits are color
//      */
//     volatile uint16_t * video_buffer = (volatile uint16_t*) 0xB8000;
//     const uint8_t white_color = 15;

//     uint8_t x_pos = x;
//     uint8_t y_pos = y;

//     const char* s = str;
//     while(*s != 0)
//     {
//         video_buffer[x_pos + 80 * y_pos] = *s | white_color << 8;

//         ++x_pos;
//         if (x_pos >= 80)
//         {
//             x_pos = 0;
//             y_pos++;
//             if ( y_pos >= 25 )
//             {
//                 y_pos = 0;
//             }
//         }

//         s++;
//     }
// }

void kmain(void* multiboot_information, uint32_t magic_number)
{
    (void) multiboot_information;
    (void) magic_number;

    gdt_install();
    idt_install();

    scr_print("Hello MyOS\nhello again");

    while(1)
    {

    }

    return;
}