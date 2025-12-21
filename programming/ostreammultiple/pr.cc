#include <stdio.h>

int main()
{
#if 1
    printf("hi");
    printf("there\n");
#elif 1
    printf("0 hi there\n");
    printf("1 hi there\n");
    printf("2 hi there\n");
    printf("3 hi there\n");
    printf("4 hi there\n");
    printf("5 hi there\n");
#else
    puts("0 hi there\n1 hi there\n2 hi there\n3 hi there\n4 hi there\n5 hi there");
#endif

    return 0;
}
