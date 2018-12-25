# Interrupt

There are exception and interrupt 
  
Interrupt or exception signals the CPU that something happen. It cause the CPU pause the current task to handle that interrupt or exception. The exception is caused by the CPU itself when executing a instruction.  The interrupt is generated by the hardware device such as keyboard or timer. The handling of an interrupt or exception is done by a special subroutine called `interrupt service routine (ISR)` or `interrupt handler`. After done with the interrupt or exception, the CPU typically will resume the interrupted task.

Each interrupt or exception is assigned to an unique number called interrupt number which is also an index to the `interrupt descriptor table (IDT)`. 

## Interrupt Descriptor Table

`IDT` (Interrupt descriptor table) is an array of up to `256` interrupt descriptors. Each interrupt descriptor contains an address of `interrupt function` which handles interrupt. The index where interrupt descriptor is located in IDT is also known as an interrupt number. When an interrupt with a number occurs, CPU will get a interrupt handler at `interrupt number` of IDT to handle the interrupt

The structure of interrupt descriptor:

```
31                             16 15                              0
--------------------------------------------------------------------
|        Selector                |              Offset 0..15       |
---------------------------------+----------------+-----------------
|        Offset 16..31           |P|DPL|S|GateType|   Reserved     |
--------------------------------------------------------------------
63                             48 47             40 39            32
```
`Selector` (16 bit): segment selector where the `interrupt function` is located

`Offset` (32 bit): offset to the `interrupt function` within the code segment

`P` (1 bit):   present, (1=present, 0=not present)

`DPL`(2 bits): descriptor privilege level,  the privilege level the interrupt can be called from (1,2,3,4)

`S` (1 bit): Storage Segment, always 0

`Gate type` (4 bits): gate type, use `32-bit trap gate` for 32-bit system
- 0x5: 32-bit task gate
- 0x6: 16-bit interrupt gate
- 0x7: 16-bit trap gate
- 0xE: 32-bit interrupt gate
- 0xF: 32-bit trap gate

`Reserved:` always 0

### Exception
The interrupt number 0 - 31 are reserved to x86 predefined exceptions:

| Interrupt Number | Exception | error code | Source |
|------------------|-----------|------------|--------|
|00 | divide by 0 | No |
|01 | debug exceptions | No |
|02 | Non-maskable interrupt | No |
|03 | Breakpoint (INT3 instruction) | No |
|04 | Overflow (INTO instruction) | No |
|05 | Bound checks | No |
|06 | Invalid opcode | No |
|07 | Device Not Available (No Math Coprocessor) | No |
|08 | Double fault | Yes (zero)
|09 | Coprocessor segment overrun | No |
|10 | Invalid TSS | Yes |
|11 | Segment Not Present | Yes |
|12 | Stack-Segment Fault | Yes |
|13 | General Protection | Yes | Any memory reference and other protection checks | 
|14 | Page Fault | Yes | Any memory reference |
|15 | reserved | No | 
|16 | Coprecessor error | No |
|17 | Alignment Check |  Yes (zero) | Any data reference in memory |
|18 | Machine Check | No |
|19 | SIMD Floating-Point Exception | No |
|20 | Virtualization Exception | No |
|21-31| reserved |

### Interrupt
The IRQ pins are connected programmable interrupt controllers (PIC), PIC1 and PIC2

| IRQ pin | Interrupt vector | Interrupt |
|---------|------------------|-----------|
|IRQ0|08|system timer
|IRQ1|	09|	keyboard
|IRQ2|	0A|	bridged to PIC2
|IRQ3|	0B|	COM2
|IRQ4|	0C|	COM1
|IRQ5|	0D|	LPT2
|IRQ6|	0E|	floppy disk drive
|IRQ7|	0F|	LPT1
|IRQ8|	70|	CMOS Real Time Clock
|IRQ9|	71|	
|IRQ10|	72|	
|IRQ11|	73|	
|IRQ12|	74|	PS/2 Mouse
|IRQ13|	75|	numeric coprocessor
|IRQ14|	76|	hard disk drive IDE0
|IRQ15|	77|	hard disk drive IDE1

**Note: IRQ0-IRQ7 have conflict with the predefined exception, we need to remap the these IRQs**

## IDTR
IDTR register store the physical address of IDT.
```
 47                    16 15        0
-------------------------+-------------
|  Base (32 bits)        | Limit      |
---------------------------------------
```

`Base`:  The linear address of IDT

`Limit`: The size of IDT - 1

## Handling an interrupt
When an interrupt occurs, the CPU will push registers value onto the stack. Then the environment is saved before interrupt handling and reserves the environment by pushing back these registers after interrupt handling
```
/*save environment by the CPU*/
push %eflags
push %cs
push %eip
push errorcode?
```

After interrupt handling is done, the `iret` instruction must be executed to pops all the registers saved before. Then the %eflags is restored, and the CPU jumps to the restored %eip:%cs.

When an interrupt occurs the CPU push the interrupt number nowhere. Therefore a handler can't know which interrupt happens. To solve this, we needs to define 256 interrupt handlers and each is hard-coded an interrupt number and installed in IDT according to their interrupt number. Once an interrupt handler is called, the associated interrupt number will be the one hard-coded in it.

```
ISR1:
    push 1
    call common_interrupt_routine
    iret

ISR2:
    pusdh 2
    call commone_interrupt_routine
    iret
....

```

