#include <stdint.h>
#include <stddef.h>

#include "arch/gdt.h"
#include "arch/idt.h"
#include "arch/isr.h"
#include "kstdlib.h"

void kmain(void* multiboot_information, uint32_t magic_number)
{
    (void) multiboot_information;
    (void) magic_number;

    gdt_install();
    idt_install();

    isr_enable();

    kprintf("==%c===%s %d\n", '!', "Hello MyOS\nhello again");

    kprintf("%d, %d, 0x%x\n", 1234567, -1234567, 0x1234567);

    while(1)
    {

    }

    return;
}