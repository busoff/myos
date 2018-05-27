# GAS assembly

# Instruction
- `%`: designates register name
- `$`: designates literal value 
- `push <operand>`: decreases %esp by the size of operator and store the operand to memory at address stored in %esp
- `pushad`: push all general purpose registers `EAX, ECX, EDX, EBX, original ESP, EBP, ESI, and EDI`


- Calling convention
```
caller:
    push %ebp
    mov %esp %ebp
    push xxx /* arg3 */
    push xxx /* arg2 */
    push xxx /* arg1 */
    call callee

    mov %ebp %esp
```

- what is different to %ebp and %esp?  
- How `call` actually do?
 store the address of instruction follows `call` on stack
- How `ret` do?
 store the address saved by call on stack to `EIP`

- How subroutine save local variable on stack

## Directive

directive | syntax | comment
----------| -------| ------- |
.section | .section \<name\> | define a section, the  `name` could be `.bss`, `.text`, `.data`, `bss` |
.align | .align \<size\>   |  align to given `size`, the `size` could be `xM`, `xK`,  `x`, while `x` is a number |
.global| .global \<symbol\> | define a global `symbol` |
.type | .type \<symbol\>, \<type\> | declare what `type` of the `symbol` is |
.extern| .extern \<symbol\> | declare an external `symbol`|
.set | .set \<symbol\>, value | assign a `symbol` a `value` |

## macro
```
.macro <name> <parameter....>
/* The '\' denotes an parameter. For example, '\number' represents an parameter 'number'*/
.endm
```




## reference:  
- https://en.wikibooks.org/wiki/X86_Assembly/GAS_Syntax
- https://gist.github.com/mishurov/6bcf04df329973c15044