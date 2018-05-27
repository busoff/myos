#include "arch/gdt.h"

#include <stdint.h>
#include <stdbool.h>

#include "kstdlib.h"

static void gdt_init();
static void gdt_install_segment(uint8_t index, uint32_t base, uint32_t limit, bool granua4k, uint8_t access);

void load_gdtr(void* gdtr); /* defined in gdt.S */

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

static struct segment_descriptor gdt[3];
static size_t gdt_cnt = 0;
static uint8_t CODE_SEGMENT = 1;
static uint8_t DATA_SEGMENT = 2;

static const uint8_t ACCESS_PRESENT_FLAG = 1 << 7;
static const uint8_t ACCESS_PRIV_RING0_FLAG = ((0 << 5) & 0x3);
static const uint8_t ACCESS_RESERVED_FLAG = 1 << 4;
static const uint8_t ACCESS_EXE_FLAG = 1 << 3;
static const uint8_t ACCESS_READ_FLAG = 1 << 1;
static const uint8_t ACCESS_WRITE_FLAG = 1 << 1;

static const uint8_t GRANULARITY_FLAG = 1 << 3;
static const uint8_t BIT_32_FLAG = 1 << 2;

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
void gdt_install_segment(uint8_t index, uint32_t base, uint32_t limit, bool granua4k, uint8_t access)
{
    gdt[index].base_low = base & 0xffff;
    gdt[index].base_mid = (base >> 16) & 0xff;
    gdt[index].base_high = (base >> 24) & 0xff;

    uint8_t granularity = granua4k ? GRANULARITY_FLAG: 0;

    uint8_t flag = ((BIT_32_FLAG | granularity) & 0xf ) << 4;
    gdt[index].flags_limit_high = flag | ((limit >> 16) & 0xf);
    gdt[index].limit_low = limit & 0xffff;

    gdt[index].access = access;
}

void gdt_install()
{
    gdt_init();

    gdt_install_segment(0,0,0,0,0);

    /* code segment
     * base: 0
     * limit: 0xfffff
     * access: pr=1, privi=0, ex=1, dc=0, rw=1, ac=0
     * flags: gr=1,sz=1
     */
    gdt_install_segment(CODE_SEGMENT, 0, 0xfffff, true,
        ACCESS_PRESENT_FLAG | ACCESS_PRIV_RING0_FLAG | ACCESS_RESERVED_FLAG |
        ACCESS_EXE_FLAG  | ACCESS_READ_FLAG);

    /* data segment
     * base: 0
     * limit: 0xfffff
     * access: pr=1, privi=0, ex=0, dc=0, rw=1, ac=0
     * flags: gr=1,sz=1
     */
    gdt_install_segment(DATA_SEGMENT, 0, 0xfffff, true,
        ACCESS_PRESENT_FLAG | ACCESS_PRIV_RING0_FLAG | ACCESS_RESERVED_FLAG |
        !ACCESS_EXE_FLAG | ACCESS_WRITE_FLAG);

    struct gdtr gdtr_val = {.size = sizeof(gdt) - 1, .base = (uint32_t)&gdt};
    load_gdtr(&gdtr_val);
}

uint16_t gdt_code_segment()
{
    return CODE_SEGMENT * 8;
}

uint16_t gdt_data_segment()
{
    return DATA_SEGMENT * 8;
}