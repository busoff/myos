#include "driver/keyboard.h"
#include "arch/irq.h"
#include "kstdlib.h"
#include "arch/port.h"

static const uint32_t KEYBOARD_IRQ = 1;
static const uint8_t DATA_PORT = 0x60;
static void keyboard_isr(struct regs regs)
{
    (void)regs;
    uint8_t scancode = inb(DATA_PORT);
    kprintf("0x%x \n", scancode);
}

void keyboard_init()
{
    irq_register(KEYBOARD_IRQ, &keyboard_isr);
}