// Program 10.4 Reading haxadecimal and octal values
#include <stdio.h>

int main(void)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int n = 0;

    printf("Enter three integer values:");
    n = scanf_s(" %d %x %o", &i, &j, &k);

    printf("\nOutput:\n");
    printf("%d values read.\n", n);
    printf("i = %d j = %d k = %d\n", i, j, k);
    return 0;
}