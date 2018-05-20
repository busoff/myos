# linker script

它描述一个可执行文件的内存布局。linker根据它来生成可执行文件。

- 段:  一个程序是由多个段(section)组成。有已初始化的的数据段(.data)，未初始化的数据段(.bss)，代码段(.text)。

每个段都有一个起始地址和大小。段的地址是通过符号 `.` 来指定的。 该符的还有个名字叫 `location counter`。 当 `location counter` 遇到一个段， 该段就以`location counter`作为自己的起始地址，同时`location counter`会自增该段大小。

每个段还可以按照特定大小对齐。 这时`location counter`除了会加上段的大小，还会加上为了对齐额外多出的大小(`padding size`)。

```ld
SECTIONS
{
    /* program loaded at address 1M */
    . = 1M
    .text: ALIGN(4K)
    {
        *(.txt)
    }

    .data: ALIGN(4K)
    {
        *(.data)
    }

    .bss: ALIGN(4K)
    {
        *(.bss)
        *(.stack)
    }
}
```

- 起始点: 程序的起始地址

程序的起始地址可以通过符号来指定

```ld
/* program is executed from symbol 'start' */
ENTRY(start)
```

起始点还可以是.text段的第一个地址又或默认以`'start'`符号开始

- 输出格式: linker输出的可执行文件的格式，一般是elf
```ld
/* the file format for executable file */
OUTPUT_FORMAT(elf32-i386)
```
## Reference
- https://sourceware.org/binutils/docs/ld/Scripts.html
