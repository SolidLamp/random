- Running example program - compile the lmc.c and main.c.

```shell
$ gcc main.c lmc.c -o out
$ ./out
```

- Compiling LMC CPU

```shell
$ gcc -c -Wall -Werror -fpic lmc.c
$ gcc -shared -o lmc.so lmc.o
```

- Running LMC assembler + CPU
    - Compile LMC CPU .so
    - Write code in program.asm
    - Run assembler.py

```shell
$ python3 ./assembler.py

```
