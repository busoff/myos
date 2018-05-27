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

## Implicit rule
Implicit rule is applied when no explicit rules are applied to the target. It serves as a fallback rule.

Normally, an implicit rule uses pattern match `%`. An example 

```makefile
objects/%.o: %.c
	mkdir -p $(dir $@)
	${CC} ${C_FLAGS} -o $@ -c $<
```
`objects/%.o`: All files of postfix `.o` in `objects` folder are recursively matches.  and the `%` will denotes the missing part of the exact filepath. e.g. take an example of `object/arm/idt.o`, the `%` = `/arm/idt`.

## String Substitution
syntax: $(patsubst pattern,replacement,text)  
Finds whitespace-separated words in `text` that match `pattern` and replaces them with `replacement`. The `pattern` and `replacement` can employ pattern matching.
```makefile
# it replace all *.c with *.o in $(C_SRC)
$(patsubst %.c, objects/%.o, $(C_SRC))
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
ASM_SRC := arch/boot.S

OBJECTS :=  $(patsubst %.c, objects/%.o, $(C_SRC))
OBJECTS += $(patsubst %.S, objects/%.o, $(ASM_SRC))
```


## Reference
- https://www.gnu.org/software/make/manual/make.html