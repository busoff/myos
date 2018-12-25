#include "arch/idt.h"

#include <stdbool.h>

#include "arch/gdt.h"
#include "kstdlib.h"
#include "arch/port.h"

extern void ISR0();
extern void ISR1();
extern void ISR2();
extern void ISR3();
extern void ISR4();
extern void ISR5();
extern void ISR6();
extern void ISR7();
extern void ISR8();
extern void ISR9();

extern void ISR10();
extern void ISR11();
extern void ISR12();
extern void ISR13();
extern void ISR14();
extern void ISR15();
extern void ISR16();
extern void ISR17();
extern void ISR18();
extern void ISR19();

extern void ISR20();
extern void ISR21();
extern void ISR22();
extern void ISR23();
extern void ISR24();
extern void ISR25();
extern void ISR26();
extern void ISR27();
extern void ISR28();
extern void ISR29();
extern void ISR30();
extern void ISR31();

extern void IRQ0();
extern void IRQ1();
extern void IRQ2();
extern void IRQ3();
extern void IRQ4();
extern void IRQ5();
extern void IRQ6();
extern void IRQ7();
extern void IRQ8();
extern void IRQ9();
extern void IRQ10();
extern void IRQ11();
extern void IRQ12();
extern void IRQ13();
extern void IRQ14();
extern void IRQ15();

extern void idt_flush(void* idt_pointer);

static void idt_init();
static void idt_install_interrupt(uint8_t interrupt_num, uint16_t segment, uint32_t offset, uint8_t flags);

/* TODO: split setup isr and irq to seperate .c files */
static void idt_install_isrs();
static void idt_install_irqs();
static void idt_remap_irqs();

static const uint8_t IDT_FLAG_PRESENT = 1 << 7;
static const uint8_t IDT_FLAG_DPL_RING0 = 0 << 5;
static const uint8_t IDT_FLAG_STORAGE = 0;
static const uint8_t IDT_FLAG_GATE_INT32 = 0xE;

static const uint8_t IRQ_BASE = 0x20;

struct interrupt_descriptor
{
    uint16_t offset_low;
    uint16_t selector;
    uint8_t reserved;
    uint8_t flags;
    uint16_t offset_high;
} __attribute__((packed));

static struct interrupt_descriptor idt[256];

struct idtr
{
    uint16_t size;
    uint32_t base;
} __attribute__((packed));

void idt_init()
{
    memset(&idt, sizeof(idt), 0);
}


void idt_install_interrupt(uint8_t interrupt_num, uint16_t segment, uint32_t offset, uint8_t flags)
{
    idt[interrupt_num].offset_high = (offset >> 16) & 0xffff;
    idt[interrupt_num].offset_low = offset & 0xffff;
    idt[interrupt_num].selector = segment;
    idt[interrupt_num].flags = flags;
    idt[interrupt_num].reserved = 0;
}

#define ISR_ENTRY(number)                                                                                            \
    do {                                                                                                             \
        const uint8_t IDT_FLAGS = (IDT_FLAG_PRESENT | IDT_FLAG_DPL_RING0 | IDT_FLAG_STORAGE | IDT_FLAG_GATE_INT32); \
        idt_install_interrupt(number, gdt_code_segment(), (uint32_t)ISR##number, IDT_FLAGS);                         \
    }while(false)

void idt_install_isrs()
{
    ISR_ENTRY(0);
    ISR_ENTRY(1);
    ISR_ENTRY(2);
    ISR_ENTRY(3);
    ISR_ENTRY(4);
    ISR_ENTRY(5);
    ISR_ENTRY(6);
    ISR_ENTRY(7);
    ISR_ENTRY(8);
    ISR_ENTRY(9);

    ISR_ENTRY(10);
    ISR_ENTRY(11);
    ISR_ENTRY(12);
    ISR_ENTRY(13);
    ISR_ENTRY(14);
    ISR_ENTRY(15);
    ISR_ENTRY(16);
    ISR_ENTRY(17);
    ISR_ENTRY(18);
    ISR_ENTRY(19);

    ISR_ENTRY(20);
    ISR_ENTRY(21);
    ISR_ENTRY(22);
    ISR_ENTRY(23);
    ISR_ENTRY(24);
    ISR_ENTRY(25);
    ISR_ENTRY(26);
    ISR_ENTRY(27);
    ISR_ENTRY(28);
    ISR_ENTRY(29);

    ISR_ENTRY(30);
    ISR_ENTRY(31);
}

#define IRQ_ENTRY(number)                                                                                            \
    do {                                                                                                             \
        const uint8_t IDT_FLAGS = (IDT_FLAG_PRESENT | IDT_FLAG_DPL_RING0 | IDT_FLAG_STORAGE | IDT_FLAG_GATE_INT32); \
        idt_install_interrupt(number + IRQ_BASE, gdt_code_segment(), (uint32_t)IRQ##number, IDT_FLAGS);                         \
    }while(false)

void idt_install_irqs()
{
    idt_remap_irqs();

    IRQ_ENTRY(0);
    IRQ_ENTRY(1);
    IRQ_ENTRY(2);
    IRQ_ENTRY(3);
    IRQ_ENTRY(4);
    IRQ_ENTRY(5);
    IRQ_ENTRY(6);
    IRQ_ENTRY(7);
    IRQ_ENTRY(8);
    IRQ_ENTRY(9);
    IRQ_ENTRY(10);
    IRQ_ENTRY(11);
    IRQ_ENTRY(12);
    IRQ_ENTRY(13);
    IRQ_ENTRY(14);
    IRQ_ENTRY(15);
}


#define PIC_WAIT() \
	do { \
		/* May be fragile */ \
		__asm__ volatile("jmp 1f\n\t" \
		             "1:\n\t" \
		             "    jmp 2f\n\t" \
		             "2:"); \
	} while (0)

static void idt_remap_irqs()
{
    static const uint16_t PIC1_COMMAND_PORT = 0x20;
    static const uint16_t PIC1_DATA_PORT    = 0x21;
    static const uint8_t  PIC1_OFFSET       = 0x20;

    static const uint16_t PIC2_COMMAND_PORT = 0xA0;
    static const uint16_t PIC2_DATA_PORT    = 0xA1;
    static const uint8_t  PIC2_OFFSET       = 0x28;

    static const uint8_t ICW1_ICW4      = 0x01;
    static const uint8_t ICW1_INIT      = 0x10;

	/* Cascade initialization */
	outb(PIC1_COMMAND_PORT, ICW1_INIT|ICW1_ICW4); PIC_WAIT();
	outb(PIC2_COMMAND_PORT, ICW1_INIT|ICW1_ICW4); PIC_WAIT();

	/* Remap */
	outb(PIC1_DATA_PORT, PIC1_OFFSET); PIC_WAIT();
	outb(PIC2_DATA_PORT, PIC2_OFFSET); PIC_WAIT();

	/* Cascade identity with slave PIC at IRQ2 */
	outb(PIC1_DATA_PORT, 0x04); PIC_WAIT();
	outb(PIC2_DATA_PORT, 0x02); PIC_WAIT();

	/* Request 8086 mode on each PIC */
	outb(PIC1_DATA_PORT, 0x01); PIC_WAIT();
	outb(PIC2_DATA_PORT, 0x01); PIC_WAIT();

    /* set interrupt mask register to enable all interrupts except interrupt 7 and interrupt 15*/
	outb(PIC1_DATA_PORT, 0x80); PIC_WAIT();
	outb(PIC2_DATA_PORT, 0x80); PIC_WAIT();
}

void idt_install()
{
    idt_init();
    idt_install_isrs();
    idt_install_irqs();

    struct idtr idtr = {.size = sizeof(idt) -1, .base = (uint32_t)idt};
    idt_flush(&idtr);
}

