.section .text
.align 4

.global flush_gdt
.type flush_gdt @function

/*
 * @breif store gdtr and code segment register %ds, %ss, %es and %cs.
 * @param  address of struct gdtr
 */
flush_gdt:
    /* store gdtr */
    mov 4(%esp), %eax
    lgdt (%eax)

    mov $16, %ax
    mov %ax, %ds
    mov %ax, %ss
    mov %ax, %es

    /* store cs by jumping*/
    ljmp $0x08, $flush_cs

flush_cs:
    ret
