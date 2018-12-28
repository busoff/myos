# KERNEL_PREFIX := i386-elf-

CC := ${KERNEL_PREFIX}gcc
AS := ${KERNEL_PREFIX}as

INCLUDE_PATH := -Istdlib -I. -Iinclude
C_FLAGS := -g -std=gnu11 -ffreestanding -fno-stack-protector -Wall -Wextra -Werror ${INCLUDE_PATH}

C_SRC := main.c arch/gdt.c arch/isr.c arch/irq.c arch/idt.c arch/port.c
C_SRC += stdlib/io.c stdlib/string.c stdlib/kprintf.c
C_SRC += driver/keyboard.c  driver/screen.c
C_SRC += userspace/terminal.c 

ASM_SRC := arch/asm/boot.S arch/asm/gdt.S arch/asm/isr.S arch/asm/idt.S arch/asm/irq.S

OBJECTS :=  $(patsubst %.c, objects/%.o, $(C_SRC))
OBJECTS += $(patsubst %.S, objects/%.o, $(ASM_SRC))

all: myos.iso

clean:
	rm -rf *.o *.bin *.iso objects

objects/%.o: %.c
	mkdir -p $(dir $@)
	${CC} ${C_FLAGS} -o $@ -c $<

objects/%.o: %.S
	mkdir -p $(dir $@)
	${AS} -o $@ -c $<

myos.bin: ${OBJECTS} linker.ld
	${CC} -T linker.ld -o $@ -ffreestanding -nostdlib ${OBJECTS}

myos.iso: myos.bin
	rm -rf iso
	mkdir iso
	mkdir -p iso/boot/grub

	cp $< iso/boot/

	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "My OS" {'>> iso/boot/grub/grub.cfg
	echo '    multiboot /boot/myos.bin' >> iso/boot/grub/grub.cfg
	echo '    boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	cat iso/boot/grub/grub.cfg

	grub-mkrescue --output=myos.iso iso

run: myos.iso
	(killall qemu-system-i386 && sleep 1 ) || true
	qemu-system-i386 -cdrom $< -m 32 -s -monitor stdio --show-cursor

debug: myos.iso
	(killall qemu-system-i386 && sleep 1 ) || true
	qemu-system-i386 -cdrom $< -m 32 -s -S -monitor stdio


# print variable for debugging
print-%  : ; @echo $* = $($*)
