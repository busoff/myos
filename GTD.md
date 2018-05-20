# Segmentation

Segmentation means you access memory via segment. The segmentation provides you hardware level memory access protection. `(TODO: give an example for it)`.

## Segment
A segment is a portion of address spaces, possibly overlapping, specified by a base address and a limit. To address a byte in segmented memory, you use 16 bites that specifies a segment selector and 32-bits for an offset within that segment.

```
15                0       31                             0        
-------------------       -------------------------------------
|segment selector |       |               offset              |
-------------------       -------------------------------------
       |                                       |
       |      GDT or LDT                       |
       |     ---------------                   |
       |     |             |                   |
       |     |             |                   v
       |     |-------------|  Base address   -----
       |---> | segment     | --------------> | + |
             | descriptor  |                 ----- 
             |-------------|                   |
             |             |                   |
             |             |                   |
             ---------------                   |
                                               |
                           31                  v               0
                           -------------------------------------
                           |         linear  address           |
                           -------------------------------------
```
## Segment Selector
The segment selector are stored `%cs`, `%ds`, `%ss`. 
- `%cs` is used as code segment for fetching instruction
- `%ds` is used as data segment for access data
- `%ss` is used as stack segment for access stack

```
func:
    mov %eax, [%esp+4]
    mov %ebx, [%eax]
    add %ebx, 8
    mov [%eax], %ebx
    ret

/*equivalent:*/

func:
    mov %eax, [%ss:%esp+4]
    mov %ebx, [%ds:%eax]
    add %ebx, 8
    mov [%ds:%eax], %ebx
    ret
```

## GDT
GDT is an array of segment descriptors. A segment descriptor defines a segment with attribute. The fist segment descriptor in GDT must be null.

### Segment Descriptor

```
31                       16   15                         0
-----------------------------+----------------------------
| Base 0:15                  |    limit 0:15             |
|                            |                           |
-------------+-------+-------+-------------+--------------
| Base 24:31 | Flags | Limit |   Access    | Base 16:23  |
|            |       | 16:19 |             |             |
---------------------------- -----------------------------
63         56 55   52 51   48 47         40 39          32   
```

`Base` (32 bit): base address with 32 bit length

`Limit` (20 bit): segment size with 16 bit length, the granularity could be byte or 4Kib (if `granularity bit` set in `Flags`)

`Flags` (4 bit):
```
 4  3  2  1
-------------
|sz|gr|0 |0 |
-------------
```
  - bit 0: not used
  - bit 1: not used <br>
  - bit 2 (size bit): if 0 define 16 bit protected mode, if 1 define 32 bit protected mode <br>
  - bit 3 (granularity bit): if 0 set, byte granularity for limit. if 1 set, 4 KiB granularity for limit.

`Access` (8 bit):  
 ```
  7   6 5  4  3  2  1  0
 ------------------------
 |pr|privi|1|Ex|DC|RW|Ac|
 ------------------------
 ```
  
  - `bit 0 (access bit)`: set `0`. The CPU set this to `1` when the segment is accessed<br>
  - `bit 1 (RW bit)`:  
    `Readable bit for code segment`, set 1 to allows code segment to be read <br>
    `Writable bit for data segment`, set 1 to allows data segment to be written <br>
  - `bit 2 (direction bit)`: <br>
    `Direction bit for data segment`. set 0 for segment grows up, set 1 for segments grows down<br>
    `Conforming bit for code segment`. set `1` for allowing low prio. code segment can far jump to high prio. code segment. set 0 for only allowing the code segment can only far jump to same priority code segment<br>
  - `bit 3 (executable bit)`: set 1 for code segment and set 0 for data segment<br>
  - `bit 4`: always 1
  - `bit 5,6 (privilege bits)`: ring level. 0 = highest (kernel) 3 = lowest (user application)
  - `bit 7 (present bit)`: must be 1 for all valid segments 

## GDTR




## Reference
1. chapter 5 in https://littleosbook.github.io/#hello-cafebabe
2. https://wiki.osdev.org/GDT
