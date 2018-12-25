#include "irq.h"
#include "kstdlib.h"
#include "arch/port.h"

#define MAX_IRQ 32u

static const uint8_t IRQ_BASE = 32; // IRQ starts from interrupt number 32
static irq_handler_t irq_table[MAX_IRQ];

void irq_enable()
{
    __asm__ volatile ("sti");
}

void irq_disable()
{
    __asm__ volatile ("cli");
}

bool irq_register(uint32_t number, irq_handler_t handler)
{
    if (number >= MAX_IRQ)
    {
        kprintf("ERR: exceeds maximum IRQ number %d\n", MAX_IRQ);
        return false;
    }

    irq_table[number] = handler;

    return true;
}

static uint8_t PCI1_CMD_PORT = 0x20;
static uint8_t PCI2_CMD_PORT = 0xA0;
static uint8_t PIC_CMD_EOI = 0x20; /* end of interrupt command*/

void irq_dispatch(struct regs regs)
{
    irq_disable();

    if (regs.int_num  >= IRQ_BASE &&  regs.int_num < (IRQ_BASE + MAX_IRQ))
    {
        uint8_t irq_num = regs.int_num - IRQ_BASE;
        irq_handler_t handler = irq_table[irq_num];
        if (handler != 0)
        {
            handler(regs);
        }

        /*
         * send EOI to PIC1 or PIC2 upon completion of interrupt, otherwise
         * the interrupt will be ignored by PICs
         */
        if (irq_num < 8)
        {
            outb(PCI1_CMD_PORT, PIC_CMD_EOI);
        }
        else if (irq_num >= 8 && regs.int_num < 16)
        {
            outb(PCI2_CMD_PORT, PIC_CMD_EOI);
        }
    }
    else
    {
        kprintf("ERR: invalid interrupt number");
    }

    irq_enable();
}