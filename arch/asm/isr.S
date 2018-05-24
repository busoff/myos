.section .text
.align 4

.set BASE_NUMBER, 0x20

.macro IRQ number
    .global _IRQ\number
    .type _IRQ\number, @function
    _IRQ\number:
        cli
        push $0x00 /*a dummy error code for compatible to some CPU exceptions*/
        push \number + BASE_NUMBER /* push interrupt number from 0x20 */

        call common_isr

        add  $8, esp /* pop the interrupt number and error code */

        iret
.endm

common_isr:
    pusha /* push all registers */

    /*push segments*/
    push %ds
    push %es
    push %fs
    push %gs

    /* link to the data segment*/
    mov 0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    push %esp
    /* call irq_handler */
    add $4, %esp /*pop up %esp*/

    pop %gs
    pop %fs
    pop %es
    pop %ds

    popa
