#include <stdint.h>
#include <stddef.h>

#include "arch/gdt.h"
#include "arch/idt.h"
#include "arch/irq.h"

#include "driver/keyboard.h"

#include "kstdlib.h"

#include "userspace/terminal.h"

void kmain(void* multiboot_information, uint32_t magic_number)
{
    (void) multiboot_information;
    (void) magic_number;

    gdt_install();
    idt_install();

    keyboard_init();

    irq_enable();

    term_init();

    kprintf("==%c===%s %d\n", '!', "Hello MyOS\nhello again");

    kprintf("%d, %d, 0x%x\n", 1234567, -1234567, 0x1234567);

    kprintf("format: %018d, %08x\n", 0x1234567, 0x1234567);

    // verify ISR interrupt
    // uint8_t value = 0;
    // value = 1/value;

    while(1)
    {

    }

    return;
}