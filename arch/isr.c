#include "arch/isr.h"
#include "kstdlib.h"
#include "port.h"

#define MAX_ISR  32

static const char* exception_messages[MAX_ISR] = {
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

static isr_handler_t isr_table[MAX_ISR];

void isr_dispatch(struct regs regs)
{
    if (regs.int_num < MAX_ISR)
    {
        kprintf("exception happen: %s (ISR%d)\n", exception_messages[regs.int_num], regs.int_num);
        if (isr_table[regs.int_num] != 0)
        {
            isr_table[regs.int_num](regs);
        }

        while (1)
        {

        }
    }
    else
    {
        kprintf("ERR: invalid isr number");
    }
}

bool isr_register(uint32_t interrupt, isr_handler_t handler)
{
    if (interrupt >= MAX_ISR)
    {
        kprintf("ERR: exceeds maximum interrupt number %d\n", MAX_ISR);
        return false;
    }

    isr_table[interrupt] = handler;

    return true;
}

