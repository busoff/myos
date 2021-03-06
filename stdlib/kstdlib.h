#ifndef _KSTDLIB_H_
#define _KSTDLIB_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

void memset(void* buffer, size_t len, uint8_t value);

bool isdigit(char ch);

void kprintf(const char *fmt, ...);

void putchar(char ch);

void puts(const char* str);

#endif //_KSTDLIB_H_