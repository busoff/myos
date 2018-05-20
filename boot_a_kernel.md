# Boot a kernel

## concept
 - BIOS
 - bootloader
 - kernel

```
---------       --------------     ----------
| BIOS  |  -->  | bootloader | --> | kernel |
---------       --------------     ----------
```

When PC is power on, the BIOS first take control over it. Then BIOS pass the control over a chain of bootloader and kernel. 

BIOS executes code at address XXX in real mode. This is the place where bootloader is located. Then bootloader start to load the kernel executable at a given address which is specified in the kernel image header (ELF header).

There is a protocol between bootloader and kernel called `multiboot`. According to the `multiboot` protocol, the bootloader should set up a suitable environment before kernel image take controls.

When kernel take control, it is already in protected mode and needs to setup a stack before call the kernel main function.