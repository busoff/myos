# grub

### Check multiboot compliant executable binary  
```
# multiboot 1
grub-file --is-x86-multiboot <os.bin>

# multiboot 2
grub-file --is-x85-multiboot2 <os.bin>
```

### generate iso out of kernel bin  
#### 1. copy `grub.cfg` folder *\<myos\>/iso/boot/grub/*

grub.cfg  
```
set timeout = 0
set default=0

menuentry "My operating system" 
{
    multiboot /boot/<myos.bin>
    boot
}
```

Note: replace \<myos.bin\> to your os binary filename

#### 2. copy your os binary file to folder \<myos\>/iso/boot

#### 3. enter
```sh
grub-mkrescue --output=myos.iso iso
```
