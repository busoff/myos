#include "arch/isr.h"
#include "kstdlib.h"
#include "port.h"

static const char *exception_messages[32] = {
    "Division by zero",
    "Debug",
    "Non-maskable interrupt",
    "Breakpoint",
    "Detected overflow",
    "Out-of-bounds",
    "Invalid opcode",
    "No coprocessor",
    "Double fault",
    "Coprocessor segment overrun",
    "Bad TSS",
    "Segment not present",
    "Stack fault",
    "General protection fault",
    "Page fault",
    "Unknown interrupt",
    "Coprocessor fault",
    "Alignment check",
    "Machine check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

static interrupt_handler_t isr_table[256];

static uint8_t PIC_CMD_EOI = 0x20; /* end of interrupt command*/

void isr_dispatch(struct regs regs)
{
    if (isr_table[regs.interrupt_num] != 0)
    {
        isr_table[regs.interrupt_num](regs);
    }
    else /* default interrupt handling for interrupt without handler */
    {
        if (regs.interrupt_num < 32)
        {
            kprintf("exception happen: %s (ISR%d)\n", exception_messages[regs.interrupt_num], regs.interrupt_num);

            // the system halts
            while(1)
            {

            }
        }
        else
        {
            /* TODO: "handle missing interrupt" */
            // kprintf("missing handler for IRQ%d\n", regs.interrupt_num);
        }

    }

    /*
     * send EOI to PIC1 or PIC2 upon completion of interrupt, otherwise
     * the interrupt will be ignored by PICs
     */
    if (regs.interrupt_num >= 32 && regs.interrupt_num <= 39)
    {
        outb(0x20, PIC_CMD_EOI);
    }
    else if (regs.interrupt_num >= 40 && regs.interrupt_num <= 47)
    {
        outb(0xA0, PIC_CMD_EOI);
    }
}

void isr_register(uint32_t interrupt, interrupt_handler_t handler)
{
    if (interrupt >= 256)
    {
        kprintf("ERR: exceeds maximum interrupt number 256\n");
        return;
    }
    isr_table[interrupt] = handler;
}

void isr_enable()
{
    __asm__ volatile ("sti");
}

void isr_disable()
{
    __asm__ volatile ("cli");
}
