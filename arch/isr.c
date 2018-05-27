#include "isr.h"

static interrupt_handler_t isr_table[256];

void dispatch_interrupt(struct regs regs)
{
    if (isr_table[regs.interrupt_num] != 0)
    {
        isr_table[regs.interrupt_num](regs);
    }
    else
    {
        // TODO: how to handle a miss an interrupt handler
    }
}

void register_isr(uint32_t interrupt, interrupt_handler_t handler)
{
    if (interrupt >= 256)
    {
        // TODO: log error
        return;
    }
    isr_table[interrupt] = handler;
}