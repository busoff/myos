KERNEL_PREFIX = i686-elf-

CC = ${KERNEL_PREFIX}gcc
AS = ${KERNEL_PREFIX}as

C_FLAGS = -g -std=gnu11 -ffreestanding  -Wall -Wextra

OBJECTS = main.o boot.o

all: myos.bin

clean:
	rm -rf *.o *.bin

%.o: %.c
	${CC} ${C_FLAGS} -o $@ -c $<

%.o: %.S
	${AS} -o $@ -c $< 

myos.bin: ${OBJECTS} linker.ld
	${CC} -T linker.ld -o $@ -ffreestanding -nostdlib ${OBJECTS}


