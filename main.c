#include <stdint.h>
#include <stddef.h>

#include "arch/gdt.h"
#include "arch/idt.h"
#include "driver/screen.h"

void kmain(void* multiboot_information, uint32_t magic_number)
{
    (void) multiboot_information;
    (void) magic_number;

    gdt_install();
    idt_install();

    scr_print("Hello MyOS\nhello again");

    int b = 0;
    int a = 1/b;
    (void)a;
    // trigger divide-by-0 exception
    while(1)
    {

    }

    return;
}