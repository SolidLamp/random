#include <stdint.h>
#include <stdlib.h>

#include "lmc.h"

int main(void);

int main(void)
{
    uint16_t arr[99] = {0};
    arr[0] = 901;
    arr[1] = 318;
    arr[2] = 901;
    arr[3] = 319;
    arr[4] = 321;
    arr[5] = 901;
    arr[6] = 218;
    arr[7] = 218;
    arr[8] = 320;
    arr[9] = 519;
    arr[10] = 121;
    arr[11] = 319;
    arr[12] = 520;
    arr[13] = 218;
    arr[14] = 320;
    arr[15] = 809;
    arr[16] = 519;
    arr[17] = 902;
    run_cpu(arr, sizeof(arr)/sizeof(arr[0]));
    return 0;
}