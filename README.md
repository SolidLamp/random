# An assortment of random, unrelated programs that are unlikely to amount to any serious project, but may be useful to someone

## gcbmk
Language: Python

A basic bin-packing algorithm with a database of the GameCube's library and the number of blocks each game uses to save.

Usage:
```shell
$ python3 ./main.py
```

## lmc
Language: C99 + Python

An implementation of the Little Man Computer instruction set. The C program handles the emulator, with an assembler written in Python.

Usage:
```shell
$ gcc main.c lmc.c -o out
$ ./out
```

## EntropySort
Language: C99

An absurd sorting algorithm which randomly changes the contents of the array until it is sorted.

Usage:
```shell
$ gcc -Wall sort.c -o out
$ ./out
```
