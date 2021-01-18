#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

static inline uint64_t splitmix64_stateless(uint64_t index)
{
    uint64_t z = (index + UINT64_C(0x9E3779B97F4A7C15));
    z = (z ^ (z >> 30)) * UINT64_C(0xBF58476D1CE4E5B9);
    z = (z ^ (z >> 27)) * UINT64_C(0x94D049BB133111EB);
    return z ^ (z >> 31);
}
/*
 * source:
 * https://github.com/lemire/testingRNG/blob/master/source/lehmer64.h
 */
uint64_t lehmer64()
{
    const uint64_t seed = 65521; /* prime */
    static __uint128_t g_lehmer64_state =
        (((__uint128_t)splitmix64_stateless(seed)) << 64) +
        splitmix64_stateless(seed + 1);
    g_lehmer64_state *= 0xda942042e4dd58b5;
    return g_lehmer64_state >> 64;
}

void generateRandom_lehmer64(uint64_t *dst, int n)
{
    assert((n & 1) == 0);
    while (n -= 2) {
        *dst++ = lehmer64();
        *dst++ = lehmer64();
    }
}

void generateBadCase_ForBinaryGCD(uint64_t *dst, int n)
{
    assert((n & 1) == 0);
    while (n -= 2) {
        int bitnum = lehmer64() & 63;
        *dst++ = (1ULL << bitnum) - 1;
        *dst++ = (1ULL << (bitnum - 1));
    }
}

void generateBadCase_ForGCD(uint64_t *dst, int n)
{
    assert((n & 1) == 0);
    static uint64_t F[94] = {0};
    if (F[93] == 0) {
        F[1] = 1;
        for (int i = 2; i < 94; ++i) {
            F[i] = F[i - 1] + F[i - 2];
        }
    }
    while (n -= 2) {
        int idx = lehmer64() % 94;
        *dst++ = F[idx];
        *dst++ = F[idx - 1];
    }
}

void generateGoodCase_ForGCD(uint64_t *dst, int n)
{
    assert((n & 1) == 0);
    while (n -= 2) {
        uint64_t rnd = lehmer64();
        *dst++ = rnd;
        *dst++ = (~0ULL / rnd) * rnd; /* make sure to be rnd's multiplier */
    }
}

void generateGoodCase_ForBinaryGCD(uint64_t *dst, int n)
{
    assert((n & 1) == 0);
    while (n--) {
        /* set maximum 8 bits */
        int setbit_num = lehmer64() & 7 + 1;
        while (setbit_num--) {
            int bit_idx = lehmer64() & 63;
            *dst |= (1ULL << bit_idx);
        }
        dst++;
    }
}

void writeTestdataFile(const char *filepath, uint64_t *dst, int n)
{
    FILE *fp = fopen(filepath, "w");
    assert(fp);

    while (n -= 2) {
        fprintf(fp, "%llu %llu\n", dst[0], dst[1]);
        dst += 2;
    }
}

int main()
{
    int N = (1 << 16); /* 2 * 2^15 */
    uint64_t *dst = (uint64_t *)malloc(N * sizeof(uint64_t));

    void (*testfunc[])(uint64_t *, int) = {
        generateRandom_lehmer64, generateBadCase_ForGCD,
        generateGoodCase_ForGCD, generateBadCase_ForBinaryGCD,
        generateGoodCase_ForBinaryGCD};

    int testfunc_num = sizeof(testfunc) / sizeof(void *);
    for (int i = 0; i < testfunc_num; ++i) {
        testfunc[i](dst, N);
        char filepath[64];
        sprintf(filepath, "./test-data/testdata%d.dat", i);
        writeTestdataFile(filepath, dst, N);
    }
    return 0;
}