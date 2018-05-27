.section .text
.align 4

.set BASE_NUMBER, 0x20

.macro ISR_NOERR number
    .global ISR\number
    .type _ISR\number, @function
    ISR\number:
        push $0x00 /* a dummy error code*/
        push \number /* interrupt number */
        jmp common_interrupt

        add $8, %esp /* 'pop up' interrupt number and error code */
        iret
.endm

.macro ISR_ERROR number
    .global ISR\number
    .type _ISR\number, @function
    ISR\number:
         /*the CPU push an error code before interrupt number here*/
        push \number
        jmp common_interrupt

        add $8, %esp /* 'pop up' interrupt number and error code */
        iret
.endm

/* standard x86 interrupt service routine */
ISR_NOERR 0
ISR_NOERR 1
ISR_NOERR 2
ISR_NOERR 3
ISR_NOERR 4
ISR_NOERR 5
ISR_NOERR 6
ISR_NOERR 7
ISR_ERROR 8
ISR_NOERR 9
ISR_ERROR 10
ISR_ERROR 11
ISR_ERROR 12
ISR_ERROR 13
ISR_ERROR 14
ISR_NOERR 15
ISR_NOERR 16
ISR_NOERR 17
ISR_NOERR 18
ISR_NOERR 19
ISR_NOERR 20
ISR_NOERR 21
ISR_NOERR 22
ISR_NOERR 23
ISR_NOERR 24
ISR_NOERR 25
ISR_NOERR 26
ISR_NOERR 27
ISR_NOERR 28
ISR_NOERR 29
ISR_NOERR 30
ISR_NOERR 31
ISR_NOERR 127

.macro IRQ number
    .global IRQ\number
    .type IRQ\number, @function
    IRQ\number:
        cli
        push $0x00 /*a dummy error code for compatible to some CPU exceptions*/
        push \number + BASE_NUMBER /* push interrupt number from 0x20 */

        jmp common_interrupt

        add  $8, %esp /* pop the interrupt number and error code */

        iret
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

.global dispatch_interrupt
.type dispatch_interrupt, @function

common_interrupt:
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
    call dispatch_interrupt
    add $4, %esp /*pop up %esp*/

    pop %gs
    pop %fs
    pop %es
    pop %ds

    popa
