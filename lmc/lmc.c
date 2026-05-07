#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "lmc.h"

typedef struct {
    uint16_t arr[99];
    int16_t acc;
    uint8_t pc;
    uint8_t ir;
    uint8_t ar;
} Memory;

static void print_arr(Memory* mem);
static Memory memory_init(void);
static uint16_t get_next_instruction(Memory* mem);
static void decode(Memory* mem, int16_t i);
static void handle_opcode(Memory* mem, uint8_t opcode);
static void add(Memory* mem, uint8_t operand);
static void sub(Memory* mem, uint8_t operand);
static void store(Memory* mem, uint8_t operand);
static void load(Memory* mem, uint8_t operand);
static void branch(Memory* mem, uint8_t operand);
static void branch_if_zero(Memory* mem, uint8_t operand);
static void branch_if_positive(Memory* mem, uint8_t operand);
static void io(Memory* mem, uint8_t operand);
static void illegal(Memory* mem);

void run_cpu(uint16_t instructions[], int input_len)
{
    Memory mem = memory_init();
    input_len = input_len > 99 ? 99 : input_len;
    for (int i = 0; i < input_len; i++) {
        mem.arr[i] = instructions[i];
    }
    print_arr(&mem);
    printf("\n");
    int arr_len = sizeof(mem.arr) / sizeof(mem.arr[0]);
    for (int i = 0; i < arr_len; i++) {
        decode(&mem, get_next_instruction(&mem));
        /* printf("Current instruction:  %d", pc); */
        handle_opcode(&mem, mem.ir);
    }
}

static Memory memory_init(void)
{
    Memory mem = { { 0 }, 0, 0, 0, 0 };
    return mem;
}

static void print_arr(Memory* mem)
{
    int arr_len = sizeof(mem->arr) / sizeof(mem->arr[0]);
    for (int i = 0; i < arr_len; i++) {
        printf("%d|", mem->arr[i]);
    }
}

static uint16_t get_next_instruction(Memory* mem)
{
    return mem->arr[mem->pc++];
}

static void decode(Memory* mem, int16_t instruction)
{
    mem->ir = instruction / 100;
    mem->ar = instruction - (mem->ir * 100);
}

static void handle_opcode(Memory* mem, uint8_t opcode)
{
    switch (opcode) {
    case 0:
        printf("Halt.\n");
        exit(0);
        break;
    case 1:
        add(mem, mem->ar);
        break;
    case 2:
        sub(mem, mem->ar);
        break;
    case 3:
        store(mem, mem->ar);
        break;
    case 5:
        load(mem, mem->ar);
        break;
    case 6:
        branch(mem, mem->ar);
        break;
    case 7:
        branch_if_zero(mem, mem->ar);
        break;
    case 8:
        branch_if_positive(mem, mem->ar);
        break;
    case 9:
        io(mem, mem->ar);
        break;
    default:
        illegal(mem);
        break;
    }
}

static void add(Memory* mem, uint8_t operand)
{
    uint16_t to_add = mem->arr[operand];
    printf("Add %d to accumulator\n", to_add);
    mem->acc += to_add;
}

static void sub(Memory* mem, uint8_t operand)
{
    uint16_t to_sub = mem->arr[operand];
    printf("Subtract %d from accumulator\n", to_sub);
    mem->acc -= to_sub;
}

static void store(Memory* mem, uint8_t operand)
{
    printf("Store value of accumulator at %d\n", operand);
    mem->arr[operand] = mem->acc;
}

static void load(Memory* mem, uint8_t operand)
{
    printf("Load value of %d to accumulator\n", operand);
    mem->acc = mem->arr[operand];
}

static void branch(Memory* mem, uint8_t operand)
{
    printf("Branch to %d\n", operand);
    mem->pc = operand;
}

static void branch_if_zero(Memory* mem, uint8_t operand)
{
    if (mem->acc == 0)
        branch(mem, operand);
}

static void branch_if_positive(Memory* mem, uint8_t operand)
{
    if (mem->acc >= 0)
        branch(mem, operand);
}

static void io(Memory* mem, uint8_t operand)
{
    switch (operand) {
    case 1:
        printf("Get user input\n");
        int input;
        scanf("%d", &input);
        mem->acc = (uint16_t)input;
        break;
    case 2:
        printf("Output value of accumulator\n");
        printf("%d\n", mem->acc);
        break;
    default:
        illegal(mem);
        break;
    }
}

static void illegal(Memory* mem)
{
    printf("Illegal instruction encountered: %d", mem->arr[mem->pc]);
    exit(1);
}
