ENTRY(start)
OUTPUT_FORMAT(elf32-i386) /* output file */

SECTIONS
{
    . = 0x1M; /* load kernel at 1M */
    .text : ALIGN(4K)
    {
        *(.multiboot)
        *(.text)
    }

    .data : ALIGN(4K)
    {
        *(.data)
    }

    .bss : ALIGN(4K)
    {
        *(.bss)
    }
}