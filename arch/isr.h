#pragma once

#include <stdint.h>
#include <stdbool.h>

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
    uint32_t int_num;
    uint32_t error_code;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
}  __attribute__((packed));

typedef void (*isr_handler_t)(struct regs);

bool isr_register(uint32_t number, isr_handler_t handler);
void isr_dispatch(struct regs registers);
