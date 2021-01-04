#include <algorithm>
#include <chrono> // std::chrono::system_clock
#include <cstdio>
#include <cstring>
#include <ctime>
#include <random> // std::default_random_engine

bool isPowerOfFour(int num)
{
    return num > 0 && (num & (num - 1)) == 0 && !(__builtin_ctz(num) & 0x1);
}

bool isPowerOfFour_LessBranch(int num)
{
    return (num > 0) && ((num & (num - 1)) == 0) & !(__builtin_ctz(num) & 0x1);
}

bool isPowerOfFour_Branchless(int num)
{
    return ((num & (num - 1)) == 0) & !(__builtin_ctz(num | (1 << 31)) & 0x1);
}

bool isPowerOfFour_Naive(int num)
{
    int n = 1;
    while (n) {
        if (n == num)
            return true;
        n *= 4;
    }
    return false;
}

int bench()
{
    bool (*test_func[])(int) = {isPowerOfFour, isPowerOfFour_LessBranch,
                                isPowerOfFour_Branchless, isPowerOfFour_Naive};
    FILE *f_list[sizeof(test_func) / sizeof(bool (*)(int))];
    for (long unsigned f = 0; f < sizeof(test_func) / sizeof(bool (*)(int));
         ++f) {
        char filepath[32];
        sprintf(filepath, "./func%lu.dat", f);
        f_list[f] = fopen(filepath, "w");
        for (int t = 0; t < 100; ++t) {
            clock_t start = clock();
            for (int i = 0; i < (1 << 20); ++i) {
                test_func[f](i);
            }
            clock_t end = clock();
            fprintf(f_list[f], "%d %f\n", t,
                    ((double)end - start) / CLOCKS_PER_SEC);
        }
    }
    return 0;
}

int bench_branch()
{
    // int test_data[(1 << 21)];
    int *test_data = (int *)calloc((1 << 20), sizeof(int));
    // memset(test_data, 0, sizeof(test_data));
    for (int i = 0; i < (1 << 19); ++i)
        test_data[i] = i;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(test_data, test_data + (1 << 20),
                 std::default_random_engine(seed));

    bool (*test_func[])(int) = {isPowerOfFour, isPowerOfFour_LessBranch,
                                isPowerOfFour_Branchless, isPowerOfFour_Naive};
    FILE *f_list[sizeof(test_func) / sizeof(bool (*)(int))];
    for (long unsigned f = 0; f < sizeof(test_func) / sizeof(bool (*)(int));
         ++f) {
        char filepath[32];
        sprintf(filepath, "./func%lu.dat", f);
        f_list[f] = fopen(filepath, "w");
        for (int t = 0; t < 100; ++t) {
            clock_t start = clock();
            for (int i = 0; i < (1 << 20); ++i) {
                test_func[f](test_data[i]);
            }
            clock_t end = clock();
            fprintf(f_list[f], "%d %f\n", t,
                    ((double)end - start) / CLOCKS_PER_SEC);
        }
    }
    free(test_data);
    return 0;
}

int main()
{
    //bench();
    bench_branch();
    return 0;
}
