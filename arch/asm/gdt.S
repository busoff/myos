.section .text
.align 4

.global load_gdtr
.type  load_gdtr, @function

/*
 * @breif store gdtr and code segment register %ds, %ss, %es and %cs.
 * @param  address of struct gdtr
 */
load_gdtr:
    /* store gdtr */
    mov 4(%esp), %eax
    lgdt (%eax)

    mov $16, %ax
    mov %ax, %ds
    mov %ax, %ss
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    /* store cs by jumping*/
    ljmp $0x08, $flush_cs

flush_cs:
    ret
