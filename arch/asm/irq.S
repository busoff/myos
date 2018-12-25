.section .text
.align 4

.set BASE_NUMBER, 0x20

/* used for interrupt */
.macro IRQ number
    .global IRQ\number
    .type IRQ\number, @function
    IRQ\number:
        cli
        push $0x00 /*a dummy error code for compatible to some CPU exceptions*/
        push $(\number + BASE_NUMBER) /* push interrupt number from 0x20 */

        jmp common_irq
.endm

IRQ 0
IRQ 1
IRQ 2
IRQ 3
IRQ 4
IRQ 5
IRQ 6
IRQ 7
IRQ 8
IRQ 9
IRQ 10
IRQ 11
IRQ 12
IRQ 13
IRQ 14
IRQ 15

.global irq_dispatch
.type irq_dispatch, @function


common_irq:
    /*
     * save environment before entering interrupt routine
     */

    pusha /* push all registers */

    /*push segments*/
    push %ds
    push %es
    push %fs
    push %gs

    /* link to the data segment*/
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    cld

    push %esp
    call irq_dispatch

    /**
     * restore saved environment after exit interrupt routine
     */
    add $4, %esp /*esp currently points to old %esp, skip the the current one*/

    pop %gs /*restore %esp*/
    pop %fs
    pop %es
    pop %ds

    popa

    add  $8, %esp /* pop the interrupt number and error code */
    iret
