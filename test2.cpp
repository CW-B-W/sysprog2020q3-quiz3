#include <stdio.h>

bool isPowerOfFour(int num)
{
    return num > 0 && (num & (num - 1)) == 0 && !(__builtin_ctz(num) & 0x1);
}

int main()
{
    for (int i = 0; i < 1000000; ++i)
        if (isPowerOfFour(i))
            printf("%d\n", i);
    return 0;
}
