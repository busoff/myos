#ifndef _PORT_H_
#define _PORT_H_
#include <stdint.h>

void outb(uint16_t port, uint8_t value);
void outs(uint16_t port, uint16_t value);
void outl(uint16_t port, uint32_t value);

uint8_t inb(uint16_t port);
uint16_t ins(uint16_t port);
uint32_t inl(uint16_t port);

#endif // _PORT_H_