#include "gdt.h"

#include <stdint.h>

#include "kstdlib.h"

static void gdt_init();
static void gdt_install_segment(uint8_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);
static void gdt_store_gdtr();

/**
 * @brief segment descriptor structure
 */
struct segment_descriptor
{
    uint16_t limit_low; /* limit (0:15) */
    uint16_t base_low;  /* base (0:15) */
    uint8_t base_mid;   /* base (16:23) */
    uint8_t access;     /* pr, privi, 1, ex, dc, rw, ac */
    uint8_t flags_limit_high; /* limit (16:19), flags (size, granu, 0, 0) */
    uint8_t base_high;
} __attribute__((packed));


/**
 * specifies the base address and limit of the GDT
 * and load to
 */
struct gdtr
{
    uint16_t size;
    uint32_t base;
} __attribute__((packed));

static struct segment_descriptor gdt[8];
static size_t gdt_cnt = 0;
static uint8_t CODE_SEGMENT = 1;
static uint8_t DATA_SEGMENT = 2;

void gdt_init()
{
    memset(gdt, sizeof(gdt), 0);
    gdt_cnt = 1; /*reserved null descriptor for the first one*/
    CODE_SEGMENT = 1;
    DATA_SEGMENT = 2;
}

/**
 *
 */
void gdt_install_segment(uint8_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
    (void)base;
    (void)access;
    (void)flags;

    gdt[index].limit_low = limit & 0xffff;
    gdt[index].base_low = base & 0xffff;
    gdt[index].base_mid = (base >> 16) & 0xff;
    gdt[index].access = (base >> 16) & 0xff;
    gdt[index].flags_limit_high = ((flags & 0xf) << 4) | ((limit >> 16) & 0xf);
    gdt[index].base_high = (base >> 24) & 0xff;
}

void gdt_store_gdtr()
{
    struct gdtr gdtr_val = {.size = sizeof(gdt) - 1, .base = (uint32_t)&gdt};
    asm volatile("lgdt %0"::"m" (gdtr_val));
}

void gdt_install()
{
    gdt_init();

    /* code segment
     * base: 0
     * limit: 0xfffff
     * access: pr=1, privi=0, ex=1, dc=0, rw=1, ac=0
     * flags: gr=1,sz=0
     */
    gdt_install_segment(CODE_SEGMENT, 0, 0, 0x9a, 0x8);

    /* data segment
     * base: 0
     * limit: 0xfffff
     * access: pr=1, privi=0, ex=0, dc=1, rw=1, ac=0
     * flags: gr=1,sz=0
     */
    gdt_install_segment(DATA_SEGMENT, 0, 0, 0x96, 0x8);

    gdt_store_gdtr();
}