#include "port.h"

void outb(uint16_t port, uint8_t value)
{
    __asm__ volatile ("outb %0, %1"::"a"(value), "Nd"(port));
}

void outs(uint16_t port, uint16_t value)
{
    __asm__ volatile ("outw %0, %1"::"a"(value), "Nd"(port));
}

void outl(uint16_t port, uint32_t value)
{
    __asm__ volatile ("outl %0, %1"::"a"(value), "Nd"(port));
}

uint8_t inb(uint16_t port)
{
    uint8_t ret = 0;

    __asm__ volatile ("inb %1, %0":"=a"(ret):"Nd"(port));

    return ret;
}

uint16_t ins(uint16_t port)
{
    uint16_t ret = 0;

    __asm__ volatile ("inw %1, %0":"=a"(ret):"Nd"(port));

    return ret;
}

uint32_t inl(uint16_t port)
{
    uint32_t ret;

    __asm__ volatile ("inl %1, %0":"=a"(ret):"Nd"(port));

    return ret;
}

