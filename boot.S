/* set the multiboot constants */
.set MULTIBOOT_MAGIC,              0x1BADB002
.set MULTIBOOT_FLAG_PAGE_ALIGN,   1 << 0
.set MULTIBOOT_FLAG_MEM_MAP,      1 << 1
; .set MULTIBOOT_FLAG_VIDEO_FLAG,   1 << 2
.set MULTIBOOT_FLAGS,             MULTIBOOT_FLAG_PAGE_ALIGN | MULTIBOOT_FLAG_MEM_MAP
.set MULTIBOOT_CHECKSUM,           -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

/* set the multiboot header */
.section .multiboot
.align 4
.long MULTIBOOT_MAGIC
.long MULTIBOOT_FLAGS
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
.long 0  /* 32 bit per pexel*/

.section .bss
stack_bottom:
.skip 32768 /*32 KiB size*/
stack_top:

.global start
.type start @function

.section .text
start:
/* make sure stack is 16-byte aligned */
mov $stack_top, %esp
and $-16, %esp

/* disable interrupt */
cli

pushl %esp /* why push %esp? */
pushl %eax /* magic number */
pushl %ebx /* multiboot information */

call kmain

/* disalbe interrup */
cli

/* halt loop */
hang:
    hlt
    jmp hang
