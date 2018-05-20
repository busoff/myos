# makefile

## Variable
 
```makefile
# Variables defined with ‘=’ are recursively expanded variables
VAR = "xx"

# Variables defined with ‘:=’ or ‘::=’ are simply expanded variables
VAR := "xx"

# append a variable
VAR += "yy"

```

## Tricks
### Print a variable

1. add a rule to makefile   
```makefile
print-%  : ; @echo $* = $($*)
```

2. run on shell and replace `<variable-name>` with the actual name
```sh
make print-<variable-name>
```


### Get a object file list out of source file list
```makefile
C_SRC := arch/gdt.c  stdlib/kstdlib.c main.c
ASSEMBLY_SRC := arch/boot.S

OBJECTS :=  $(patsubst %.c, objects/%.o, $(C_SRC))
OBJECTS += $(patsubst %.S, objects/%.o, $(ASSEMBLY_SRC))
```