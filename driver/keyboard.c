#include "driver/keyboard.h"
#include "arch/isr.h"
#include "kstdlib.h"

static const uint32_t KEYBOARD_IRQ = 32;

static void keyboard_isr(struct regs regs)
{
    kprintf("keyboard hit %d\n", regs.interrupt_num);
}

void keyboard_init()
{
    isr_register(KEYBOARD_IRQ, &keyboard_isr);
}