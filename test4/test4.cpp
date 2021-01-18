#include <algorithm>
#include <cstdint>
#include <iostream>

using namespace std;

uint64_t gcd64_recursive(uint64_t a, uint64_t b)
{
    return b == 0ULL ? a : gcd64_recursive(b, a % b);
}

uint64_t gcd64_iterative(uint64_t a, uint64_t b)
{
    if (!a || !b)
        return a | b;
    while ((a %= b) && (b %= a))
        ;
    return a | b;
}

uint64_t binarygcd64_recursive(uint64_t u, uint64_t v)
{
    if (!u || !v)
        return u | v;

    if (!((u & 1ULL) || (v & 1ULL))) {
        return 2ULL * binarygcd64_recursive(u >> 1ULL, v >> 1ULL);
    }
    else if (!(u & 1ULL)) {
        return binarygcd64_recursive(u >> 1ULL, v);
    }
    else if (!(v & 1ULL)) {
        return binarygcd64_recursive(u, v >> 1ULL);
    }
    else {
        if (v > u)
            swap(u, v);
        return binarygcd64_recursive(u - v, v);
    }
}

uint64_t binarygcd64_iterative(uint64_t u, uint64_t v)
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

uint64_t binarygcd64_iterative_ctz(uint64_t u, uint64_t v)
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

void readTestDataFile(const char *filepath, uint64_t *dst, int n)
{
    FILE *fp = fopen(filepath, "r");
    assert(fp);

    while (n -= 2) {
        fscanf(fp, "%llu %llu\n", &dst[0], &dst[1]);
        dst += 2;
    }
}

int bench()
{
    uint64_t (*test_func[])(uint64_t, uint64_t) = {
        gcd64_recursive, gcd64_iterative, binarygcd64_recursive,
        binarygcd64_iterative, binarygcd64_iterative_ctz};
    int test_func_num = sizeof(test_func) / sizeof(void *);

    uint64_t *test_data = new uint64_t[1 << (15 + 1)];
    for (int td = 0; td < 5; ++td) {
        char testfilepath[64];
        sprintf(testfilepath, "./test-data/testdata%d.dat", td);
        readTestDataFile(testfilepath, test_data, 1 << 16);

        FILE *f_list[test_func_num];
        for (int f = 0; f < test_func_num; ++f) {
            char filepath[64];
            sprintf(filepath, "./plot-data/test%d-func%d.dat", td, f);
            f_list[f] = fopen(filepath, "w");
            printf("running test%d func%d\n", td, f);
            for (int t = 0; t < 100; ++t) {
                clock_t start = clock();
                for (int tt = 0; tt < (1 << 15); ++tt) {
                    test_func[f](test_data[tt * 2 + 0], test_data[tt * 2 + 1]);
                }
                clock_t end = clock();
                fprintf(f_list[f], "%d %f\n", t,
                        ((double)end - start) / CLOCKS_PER_SEC);
            }
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