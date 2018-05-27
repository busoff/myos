#include "arch/isr.h"
#include "driver/screen.h"
#include "kstdlib.h"

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

void dispatch_interrupt(struct regs regs)
{
    if (isr_table[regs.interrupt_num] != 0)
    {
        isr_table[regs.interrupt_num](regs);
    }
    else
    {
        if (regs.interrupt_num < 32)
        {
            // print exception
            scr_print("exception happen: ");
            scr_print(exception_messages[regs.interrupt_num]);
			halt();
        }
        else
        {
            // TODO: "handle missing interrupt";
        }

    }
}

void register_isr(uint32_t interrupt, interrupt_handler_t handler)
{
    if (interrupt >= 256)
    {
        scr_print("ERR: exceeds maximum interrupt number 256\n");
        return;
    }
    isr_table[interrupt] = handler;
}
