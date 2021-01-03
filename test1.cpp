#include <stdio.h>
#include <stdint.h>

int asr_i(signed int m, unsigned int n)
{
    const int logical = (((int) -1) >> 1) > 0;
    unsigned int fixu = -(logical & (m < 0));
    int fix = *(int *) &fixu;
    return (m >> n) | (fix ^ (fix >> n));
}

int main()
{
    int32_t   a =  100;
    int32_t   b = -100;
    uint32_t ub = -100;


    printf("0x%08X\n", a >> 2);
    printf("0x%08X\n", asr_i(a, 2));
    printf("0x%08X\n", b >> 2);
    printf("0x%08X\n", asr_i(b, 2));
    printf("0x%08X\n", ub >> 2);
    printf("0x%08X\n", asr_i(ub, 2));
    return 0;
}