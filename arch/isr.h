#ifndef _ISR_H_
#define _ISR_H_

#include <stdint.h>

struct regs
{
    uint32_t esp;
    uint32_t gs;
    uint32_t fs;
    uint32_t es;
    uint32_t ds;
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t old_esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t interrupt_num;
    uint32_t error_code;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
}  __attribute__((packed));

typedef void (*interrupt_handler_t)(struct regs);

void isr_register(uint32_t interrupt, interrupt_handler_t handler);
void isr_dispatch(struct regs registers);
void isr_enable();
void isr_disable();

#endif // _ISR_H_
