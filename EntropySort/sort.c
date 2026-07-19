#include <limits.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int main(void);
void printbytes(uint32_t* arr, int size);
void spam_term(uint32_t* arr, int size);
void entropy_sort(uint32_t* arr, int size);
int sorted_check(uint32_t* arr, int size);
void shoot_comsic_rays(uint32_t* arr, int size);
void shoot_cosmic_ray(uint32_t* arr, int size);
int choose_bit(uint32_t* arr, int size);

int sorted_check(uint32_t* arr, int size)
{
    int sorted = 1;
    for (int i = 1; i < size; ++i) {
        uint32_t current_value = *(arr + i);
        uint32_t last_value = *(arr + i - 1);
        if (last_value > current_value) {
            sorted = 0;
        }
    }
    return sorted;
}

int choose_bit(uint32_t* arr, int size)
{
    int chosen_bit;
    int len = size * sizeof(uint32_t) * CHAR_BIT;
    chosen_bit = rand() % (len + 1);
    return(chosen_bit);
}

void shoot_cosmic_ray(uint32_t* arr, int size)
{
    int chosen_bit = choose_bit(arr, size);
    int chosen_index = chosen_bit / CHAR_BIT / sizeof(uint32_t);
    int shift = chosen_bit - (chosen_index * CHAR_BIT * sizeof(uint32_t));

    if (rand() % 10000 != 8) {
        return;
    }

    uint32_t* work_area = arr + chosen_index;
    *work_area ^= (1 << shift);
}

void shoot_cosmic_rays(uint32_t* arr, int size)
{
    srand(time(NULL));
    int i;
    for (i = 0; i < 5000; ++i) {
        shoot_cosmic_ray(arr, size);
    }
}

void entropy_sort(uint32_t* arr, int size)
{
    while (sorted_check(arr, size) == 0) {
        shoot_cosmic_rays(arr, size);
    }
}

void spam_term(uint32_t* arr, int size)
{
    while (sorted_check(arr, size) == 0) {
        printbytes(arr, size);
        shoot_cosmic_rays(arr, size);
    }
}

void printbytes(uint32_t* arr, int size)
{
    for (int i = 0; i < size; ++i) {
        printf("%u\n", *(arr + i));
    }
}

int main(void)
{
    uint32_t arr[] = { 3, 1, 3 };
    // First successful sort: { 134743043, 1350565890, 2147488259 }
    int size = sizeof(arr) / sizeof(uint32_t);
    printbytes(arr, size);
    entropy_sort(arr, size);
    printbytes(arr, size);
    return(0);
}

