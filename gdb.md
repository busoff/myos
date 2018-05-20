# GDB

## Print

Print register  
```
gdb> info registers
gdb> info registers eax
```

Print memory
```
gdb> x 
```

## Memory
* syntax: x/nfu \<address\>  
`n`: count <br>
`f`: printf format <br>
`u`: unit. b=1 byte, h=2 bytes, w=4 bytes g=8 bytes

```
gdb> x/16xb 0x123456
```

## Stack frame
```
# show call frame stack
gdb> bt

# select frame
gdb> frame #1
```

## Layout
gdb layout allows to debug and watch src/asm/registers side by side

```
# assembly view
gdb> layout asm

# source view 
gdb> layout src

# register view
gdb> layout regs

# source & assembly views
gdb> layout split

# focus layout, where <name> = next | prev | src | asm | regs | cmd
gdb> focus <name>
```

## Tricks
- debug assembly  
```
# Alternative 1
gdb> layout asm
gdb> si

# Alternative 2
gdb> display/i $pc
gdb> si
```
