#include <stdio.h>
#include <time.h>

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
                                isPowerOfFour_Naive, isPowerOfFour_Branchless};
    FILE *f_list[sizeof(test_func) / sizeof(bool (*)(int))];
    for (long unsigned f = 0; f < sizeof(test_func) / sizeof(bool (*)(int));
         ++f) {
        char filepath[32];
        sprintf(filepath, "./func%lu.dat", f);
        f_list[f] = fopen(filepath, "w");
        for (int t = 0; t < 1000; ++t) {
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

int main()
{
    bench();
    return 0;
}
