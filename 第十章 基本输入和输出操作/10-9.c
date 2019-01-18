// Program 10.9 Variations on a single integer
#include <stdio.h>

int main(void)
{
    int k = 678;

    printf_s("%%d %%o %%x %%X\n");
    printf_s("%%d %%o %%x %%X\n", k, k, k, k);
    printf_s("\n|%%8d |%%-8d |%%+8d |%%08d |%%-+8d |\n");
    printf_s("|%8d |%-8d |%+8d |%08d |%-+8d |\n", k, k, k, k, k);
    return 0;
}