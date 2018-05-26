#ifndef _GDT_H_
#define _GDT_H_
#include <stdint.h>

void gdt_install();
uint16_t gdt_code_segment();
uint16_t gdt_data_segment();
#endif // _GDT_H_
