#include <stdint.h>
#include <stdio.h>

#define ASR(m, n)                                                              \
    do {                                                                       \
        const intx_t logical = (((intx_t)-1) >> 1) > 0;                        \
        uintx_t fixu = -(logical & (m < 0));                                   \
        intx_t fix = *(intx_t *)&fixu;                                         \
        return (m >> n) | (fix ^ (fix >> n));                                  \
    } while (0);

int8_t asr_8(int8_t m, uint8_t n){
#define intx_t int8_t
#define uintx_t uint8_t
    ASR(m, n)
#undef intx_t
#undef uintx_t
}

int16_t asr_16(int16_t m, uint16_t n){
#define intx_t int16_t
#define uintx_t uint16_t
    ASR(m, n)
#undef intx_t
#undef uintx_t
}

int32_t asr_32(int32_t m, uint32_t n)
{
#define intx_t int32_t
#define uintx_t uint32_t
    ASR(m, n)
#undef intx_t
#undef uintx_t
}

#undef ASR

int main()
{
    int32_t a = 100;
    int32_t b = -100;
    uint32_t ub = -100;

    printf("0x%08X\n", a >> 2);
    printf("0x%08X\n", asr_32(a, 2));
    printf("0x%08X\n", b >> 2);
    printf("0x%08X\n", asr_32(b, 2));
    printf("0x%08X\n", ub >> 2);
    printf("0x%08X\n", asr_32(ub, 2));
    return 0;
}