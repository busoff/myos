# boot.S
boot.S is technically start entry point of a kernel, it at least to setup a stack before call kernel main function.

1. provide multiboot header for bootloader
2. setup stack and store stack start address to %escp
3. clear interrupt
4. call kernel main function
5. enable interrupt
6. provide a halt loop afch'nongter kernel main function exit


## multiboot header

The `bootloader` will search kernel for a `magic number` within the first 8KiB memory. Then bootloader knows where multiboot header. And read the following data after the magic number. The magic number and data read by bootloader are composed of a `multiboot header`.

Note: the header must be `4-bytes-aligned`.

```cpp
struct multiboot_header
{
    /* magic number 0x1BADB002 used for indicating the start of the multiboot header  */
    multiboot_uint32_t magic;

    /* Feature flags. 
     * bit 0: the kernel must be aligned to 4 KiB
     * bit 1: boolloader must provide memory map to kernel in multiboot information sturcutre
     * bit 2: bootloader must provide video information to kernel in multiboot information sturcutre
     * bit 16: the fields at offset 12 - 28 in the multiboot header are valid. And the bootloader should use them instead of the fields in the actual executable header to calculate where to load the OS image.
     The information doesn't need to be provided if the kernel image is in ELF format, but it must be provided if the image is in a.out format or in other format.
     */
    multiboot_uint32_t flags;

    /* The above fields plus this one must equal 0 mod 2^32.
     * checksum = -(magic + flags)
     */
    multiboot_uint32_t checksum; 

    /* These are only valid if MULTIBOOT_AOUT_KLUDGE is set. 
     * They can be left 0 if ELF format is used
     */
    multiboot_uint32_t header_addr;
    multiboot_uint32_t load_addr;
    multiboot_uint32_t load_end_addr;
    multiboot_uint32_t bss_end_addr;
    multiboot_uint32_t entry_addr;

    /* These are only valid if MULTIBOOT_VIDEO_MODE is set. */
    multiboot_uint32_t mode_type;
    multiboot_uint32_t width;
    multiboot_uint32_t height;
    multiboot_uint32_t depth;
};
```

## after kernel image is loaded
After bootloader loads the kernel, the machine state must be:
- `%eax`: contains magic value `"0x2BADB002"`
- `%ebx`: contains physical address of multiboot information structure provided by bootloader
- `%cr0`: PG is cleared and PE is set

## call kernel main function
before calling a kernel main,   
 - The stack must be setup, as the X86 stack grow downwards, set the %esp to the stack start address +  size
 - push arguments `%eax` and `%ebx` into stack

## after kernel main exit
- provide a loop within which `hlt` executes. only a `hlt` instruction is not enough as it can be interrupted.

## section
As the boot.S will be compiled to a object file, the data section `.bss` and code section `.text` should be present. The stack can be defined in the `.bss` section and code can be in `.text` sections

## Reference
- https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#multiboot_002eh
