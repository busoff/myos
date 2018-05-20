KERNEL_PREFIX = i686-elf-

CC = ${KERNEL_PREFIX}gcc
AS = ${KERNEL_PREFIX}as

C_FLAGS = -g -std=gnu11 -ffreestanding -fno-stack-protector -Wall -Wextra -Werror

OBJECTS = main.o boot.o gdt.o kstdlib.o

all: myos.iso

clean:
	rm -rf *.o *.bin *.iso

%.o: %.c
	${CC} ${C_FLAGS} -o $@ -c $<

%.o: %.S
	${AS} -o $@ -c $<

myos.bin: ${OBJECTS} linker.ld
	${CC} -T linker.ld -o $@ -ffreestanding -nostdlib ${OBJECTS}

myos.iso: myos.bin
	cp myos.bin iso/boot
	grub-mkrescue --output=myos.iso iso

run: myos.iso
	(killall qemu-system-i386 && sleep 1 ) || true
	qemu-system-i386 -cdrom $< -m 32 -s -monitor stdio --show-cursor

debug: myos.iso
	(killall qemu-system-i386 && sleep 1 ) || true
	qemu-system-i386 -cdrom $< -m 32 -s -S -monitor stdio