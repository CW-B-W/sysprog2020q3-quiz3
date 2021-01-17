#include <algorithm>
#include <cstdint>
#include <iostream>

using namespace std;

uint64_t gcd64_modop(uint64_t u, uint64_t v)
{
    while ((u %= v) && (v %= u))
        ;
    return u | v;
}

uint64_t gcd64(uint64_t u, uint64_t v)
{
    if (!u || !v)
        return u | v;
    int shift;
    for (shift = 0; !((u | v) & 1); shift++) {
        u /= 2, v /= 2;
    }
    while (!(u & 1))
        u /= 2;
    do {
        while (!(v & 1))
            v /= 2;
        if (u < v) {
            v -= u;
        }
        else {
            uint64_t t = u - v;
            u = v;
            v = t;
        }
    } while (v);
    return u << shift;
}

uint64_t gcd64_ctz(uint64_t u, uint64_t v)
{
    if (!u || !v)
        return u | v;

    int shift = __builtin_ctzl(u | v);
    u >>= shift;
    v >>= shift;

    u >>= __builtin_ctzl(u);

    do {
        v >>= __builtin_ctzl(v);

        if (u < v) {
            v -= u;
        }
        else {
            uint64_t t = u - v;
            u = v;
            v = t;
        }
    } while (v);
    return u << shift;
}

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

int bench()
{
    uint64_t *test_data = new uint64_t[1 << (16 + 1)];
    for (int i = 0; i < (1 << 16); ++i) {
        test_data[i * 2 + 0] = lehmer64();
        test_data[i * 2 + 1] = lehmer64();
    }

    uint64_t (*test_func[])(uint64_t, uint64_t) = {gcd64_modop, gcd64,
                                                   gcd64_ctz};
    FILE *f_list[sizeof(test_func) / sizeof(bool (*)(int))];
    for (long unsigned f = 0; f < sizeof(test_func) / sizeof(bool (*)(int));
         ++f) {
        char filepath[32];
        sprintf(filepath, "./func%lu.dat", f);
        f_list[f] = fopen(filepath, "w");
        for (int t = 0; t < 100; ++t) {
            clock_t start = clock();
            for (int tt = 0; tt < (1 << 16); ++tt) {
                test_func[f](test_data[tt * 2 + 0], test_data[tt * 2 + 1]);
            }
            clock_t end = clock();
            fprintf(f_list[f], "%d %f\n", t,
                    ((double)end - start) / CLOCKS_PER_SEC);
        }
    }
    delete[] test_data;
    return 0;
}

int main()
{
    bench();
    return 0;
}