# Build a Kernel Image

Ingredient  
- [boot.S](boot_S.md)
- a dummy main.cpp
- optional makefile 
- [linker script](linker_script.md)
- x86-elf cross-compile
- [grub2](grub.md)
- [qemu](qemu.md)

## boot.S
```assembly
.set MULTIBOOT_MAGIC,              0x1BADB002
.set MULTIBOOT_FLAG_PAGE_ALIGN,   1 << 0
.set MULTIBOOT_FLAG_MEM_MAP,      1 << 1
.set MULTIBOOT_FLAG_VIDEO_FLAG,   1 << 2
.set MULTIBOOT_FLAGS,             MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEM_MAP | MULTIBOOT_VIDEO
.set MULTIBOOT_CHECKSUM,          -(MULTIBOOT_MAGIC + MULTIBOOT_MEM_MAP)

.section .multiboot
.align 4
.long MULTIBOOT_MAGIC
.long MULTIBOOT_FLAG
.long MULTIBOOT_CHECKSUM

/*image load location (not used)*/
.long 0
.long 0
.long 0
.long 0
.long 0

/* video mode */
.long 0 
.long 0
.long 0
.long 32  /* 32 bit per pixel*/

.section .bss .stack
stack_bottom:
.skip 32768
stack_top:

.global start
.type start @function

.section .text
start:
/* make sure stack is 16-byte aligned */
mov stack_top %esp
and $-16 %esp

/* disable interrupt */
cli

push %esp /* save the stack frame */
push %eax /* push multiboot magic number */
push %ebx /* physical address of multiboot information structure filled by bootloader */
call kmain

/* disable interrupt */
cli

/* halt loop */
hang:
    hlt
    jmp hang

```
Note:
```
/* set a value to a symbol */
.set <symbol>, value

/* assemble the following code into a section named */
.section <name>

/* */
.align
```

compile:
```sh
i686-elf-as boot.S -o boot.o 
```

## a dummy main.c
It defines a dummy main function
```c
void kmain()
```