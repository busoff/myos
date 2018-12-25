.section .text
.align 4

/* use for exception with error code pushed on stack by CPU */
.macro ISR_ERROR number
    .global ISR\number
    .type _ISR\number, @function
    ISR\number:
         /*the CPU push an error code before interrupt number here*/
        push $\number
        jmp common_interrupt

        add $4, %esp /* 'pop up' interrupt number */
        iret
.endm


/* use for exception without error code provided by CPU */
.macro ISR_NOERR number
    .global ISR\number
    .type _ISR\number, @function
    ISR\number:
        push $0x00 /* a dummy error code*/
        push $\number /* interrupt number */
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

.global isr_dispatch
.type isr_dispatch, @function

common_interrupt:
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
    call isr_dispatch

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
