# GAS assembly

# Instruction
- `%`: designates register name
- `$`: designates literal value 
- `push <operand>`: decreases %esp by the size of operator and store the operand to memory at address stored in %esp
- 


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

## reference:  
- https://en.wikibooks.org/wiki/X86_Assembly/GAS_Syntax
- https://gist.github.com/mishurov/6bcf04df329973c15044