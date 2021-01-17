#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>

using namespace std;

size_t naive(const uint64_t *bitmap, size_t bitmapsize, uint32_t *out)
{
    size_t pos = 0;
    for (size_t k = 0; k < bitmapsize; ++k) {
        uint64_t bitset = bitmap[k];
        size_t p = k * 64;
        for (int i = 0; i < 64; i++) {
            if ((bitset >> i) & 0x1)
                out[pos++] = p + i;
        }
    }
    return pos;
}

size_t improved(const uint64_t *bitmap, size_t bitmapsize, uint32_t *out)
{
    size_t pos = 0;
    uint64_t bitset;
    for (size_t k = 0; k < bitmapsize; ++k) {
        bitset = bitmap[k];
        while (bitset != 0) {
            uint64_t t = bitset & -bitset;
            int r = __builtin_ctzll(bitset);
            out[pos++] = k * 64 + r;
            bitset ^= t;
        }
    }
    return pos;
}

size_t improved_guaneec(const uint64_t *bitmap, size_t bitmapsize,
                        uint32_t *out)
{
    size_t pos = 0;
    uint64_t bitset;
    for (size_t k = 0; k < bitmapsize; ++k) {
        bitset = bitmap[k];
        int n = __builtin_popcountll(bitset);
        while (n--) {
            uint64_t t = bitset & -bitset;
            int r = __builtin_ctzll(bitset);
            out[pos++] = k * 64 + r;
            bitset ^= t;
        }
    }
    return pos;
}

size_t improved_more(const uint64_t *bitmap, size_t bitmapsize, uint32_t *out)
{
    size_t pos = 0;
    uint64_t bitset;
    for (size_t k = 0; k < bitmapsize; ++k) {
        bitset = bitmap[k];
        if (__builtin_popcountll(bitset) > 32) {
            bitset = ~bitset;
            int idx = 0;
            if (bitset == 0) {
                for (int i = 0; i < 64; ++i)
                    out[pos++] = k * 64 + i;
                continue;
            }
            while (bitset != 0) {
                uint64_t t = bitset & -bitset;
                int r = __builtin_ctzll(bitset);
                for (int i = idx; i < r; ++i)
                    out[pos++] = k * 64 + i;
                idx = r + 1;
                bitset ^= t;
            }
        }
        else {
            while (bitset != 0) {
                uint64_t t = bitset & -bitset;
                int r = __builtin_ctzll(bitset);
                out[pos++] = k * 64 + r;
                bitset ^= t;
            }
        }
    }
    return pos;
}

/*
 * Generate a bitmap with periodic pattern
 * If patternsize > bitmapsize, the resulting bitmap
 * will be a truncated pattern
 * Args:
 *     bitmap: The destination of generated bitmap
 *     bitmapsize: size of bitmap
 *     pattern: The pattern for the resulting bitmap
 *     patternsize: size of pattern
 */
void generate_periodic_bitmap(uint64_t *bitmap, const size_t bitmapsize,
                              const uint64_t *pattern, const size_t patternsize)
{
    if (patternsize == 1) {
        for (size_t t = 0; t < (bitmapsize / patternsize); ++t) {
            *(bitmap++) = *pattern;
        }
    }
    else {
        int remainsize = bitmapsize;
        for (size_t t = 0; t < (bitmapsize / patternsize); ++t) {
            memcpy(bitmap, pattern, sizeof(uint64_t) * patternsize);
            bitmap += sizeof(uint64_t) * patternsize;
            remainsize -= patternsize;
        }
        if (remainsize)
            memcpy(bitmap, pattern, sizeof(uint64_t) * remainsize);
    }
}

void bench_dataset(const uint64_t *testdata, size_t testdata_size,
                   const char *w_filepath)
{
    uint32_t *tmp = new uint32_t[testdata_size * 64];
    size_t (*test_func[])(const uint64_t *, size_t, uint32_t *) = {
        naive, improved, improved_more, improved_guaneec};

    size_t L = sizeof(test_func) / sizeof(bool (*)(int));

    FILE *fp = fopen(w_filepath, "w");
    double res[100][L];

    for (size_t f = 0; f < L; ++f) {
        if (test_func[0](testdata, testdata_size, tmp) !=
            test_func[f](testdata, testdata_size, tmp)) {
            printf("Unmatched output size: %016lX %ld: %lu, %lu\n", *testdata,
                   f, test_func[0](testdata, testdata_size, tmp),
                   test_func[f](testdata, testdata_size, tmp));
        }
    }

    for (size_t f = 0; f < L; ++f) {
        for (int t = 0; t < 100; ++t) {
            clock_t start = clock();
            test_func[f](testdata, testdata_size, tmp);
            clock_t end = clock();
            res[t][f] = ((double)end - start) / CLOCKS_PER_SEC;
        }
    }

    for (size_t t = 0; t < 100; ++t) {
        fprintf(fp, "%lu ", t);
        for (size_t f = 0; f < L; ++f) {
            fprintf(fp, "%f ", res[t][f]);
        }
        fprintf(fp, "\n");
    }

    delete[] tmp;
}

void bench()
{
    const size_t bitmapsize = 16384;
    uint64_t *bitmap = new uint64_t[bitmapsize]; /* 2^20 bits */
    // uint64_t pattern_list[][1] = {{0x0000000000000000}, {0x0000000000000001},
    //                               {0x0000000000000003}, {0x0000FFFF0000FFFF},
    //                               {0x13579BDF13579BDF}, {0xF0F0F0F0F0F0F0F0},
    //                               {0xFFF0FFF0FFF0FFF0},
    //                               {0xFFFFFFFFFFFFFFFF}};
    uint64_t pattern_list[][1] = {{0x0000000000000000},
                                  {0x0000000000000001},
                                  {0x13579BDF2468ACE0},
                                  {0x7FFFFFFFFFFFFFFF},
                                  {0xFFFFFFFFFFFFFFFF}};
    size_t pattern_list_size = sizeof(pattern_list) / sizeof(uint64_t);

    for (size_t i = 0; i < pattern_list_size; ++i) {
        generate_periodic_bitmap(bitmap, bitmapsize, pattern_list[i], 1);
        char filepath[64];
        sprintf(filepath, "./plot-data/0x%016lX.dat", pattern_list[i][0]);
        bench_dataset(bitmap, bitmapsize, filepath);
    }
    delete[] bitmap;
}

int main()
{
    bench();
    return 0;
}