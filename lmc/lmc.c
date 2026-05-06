#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "lmc.h"

void print_arr(void);
static uint16_t get_next_instruction(void);
static void decode(int16_t i);
static void handle_opcode(uint8_t opcode);
static void add(uint8_t operand);
static void sub(uint8_t operand);
static void store(uint8_t operand);
static void load(uint8_t operand);
static void branch(uint8_t operand);
static void branch_if_zero(uint8_t operand);
static void branch_if_positive(uint8_t operand);
static void io(uint8_t operand);
static void illegal(void);

static uint16_t arr[99] = {0};
static int16_t acc = 0;
static uint8_t pc = 0;
static uint8_t ir = 0;
static uint8_t ar = 0;

void run_cpu(uint16_t instructions[], int input_len)
{
    input_len = input_len > 99 ? 99 : input_len;
    for (int i = 0; i < input_len; i++) {
        arr[i] = instructions[i];
    }
    print_arr();
    printf("\n");
    int arr_len = sizeof(arr)/sizeof(arr[0]);
    for (int i = 0; i < arr_len; i++) {
        decode(get_next_instruction());
        /* printf("Current instruction:  %d", pc); */
        handle_opcode(ir);
    }
}

void print_arr(void) 
{
    int arr_len = sizeof(arr)/sizeof(arr[0]);
    for (int i = 0; i < arr_len; i++) {
        printf("%d|", arr[i]);
    }
}

static uint16_t get_next_instruction(void) 
{
    return arr[pc++];
}

static void decode(int16_t instruction)
{
    ir = instruction / 100;
    ar = instruction - (ir * 100);
}

static void handle_opcode(uint8_t opcode)
{
    switch (opcode) {
        case 0:
            printf("Halt.\n");
            exit(0);
            break;
        case 1:
            add(ar);
            break;
        case 2:
            sub(ar);
            break;
        case 3:
            store(ar);
            break;
        case 5:
            load(ar);
            break;
        case 6:
            branch(ar);
            break;
        case 7:
            branch_if_zero(ar);
            break;
        case 8:
            branch_if_positive(ar);
            break;
        case 9:
            io(ar);
            break;
        default:
            illegal();
            break;
    }
}

static void add(uint8_t operand)
{
    uint16_t to_add = arr[operand];
    printf("Add %d to accumulator\n", to_add);
    acc += to_add;
}

static void sub(uint8_t operand)
{
    uint16_t to_sub = arr[operand];
    printf("Subtract %d from accumulator\n", to_sub);
    acc -= to_sub;
}

static void store(uint8_t operand)
{
    printf("Store value of accumulator at %d\n", operand);
    arr[operand] = acc;
}

static void load(uint8_t operand)
{
    printf("Load value of %d to accumulator\n", operand);
    acc = arr[operand];
}

static void branch(uint8_t operand)
{
    printf("Branch to %d\n", operand);
    pc = operand;
}

static void branch_if_zero(uint8_t operand)
{
    if (acc == 0)
        branch(operand);
}

static void branch_if_positive(uint8_t operand)
{
    if (acc >= 0)
        branch(operand);
}

static void io(uint8_t operand)
{
    switch (operand) {
        case 1:
            printf("Get user input\n");
            int input;
            scanf("%d", &input);
            acc = (uint16_t)input;
            break;
        case 2:
            printf("Output value of accumulator\n");
            printf("%d\n", acc);
            break;
        default:
            illegal();
            break;
    }
}

static void illegal(void)
{
    printf("Illegal instruction encountered: %d", arr[pc]);
    exit(1);
}