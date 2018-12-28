#include <stdint.h>
#include <stddef.h>

#include "arch/gdt.h"
#include "arch/idt.h"
#include "arch/irq.h"

#include "driver/keyboard.h"

#include "kstdlib.h"

static void keyboard_handler(key_event_t event)
{
    kprintf("keycode: %d modifier: %02x action: %d\n", 
        event.keycode, event.modifiers, event.action);
}

void kmain(void* multiboot_information, uint32_t magic_number)
{
    (void) multiboot_information;
    (void) magic_number;

    gdt_install();
    idt_install();

    keyboard_init();

    keyboard_register(keyboard_handler);

    irq_enable();

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