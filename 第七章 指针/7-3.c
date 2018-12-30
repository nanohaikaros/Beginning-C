// Program 7.3 using pointer arguments to scanf_s
#define __STDC_WANT_LIB_EXT__ 1
#include <stdio.h>

int main(void)
{
    int value = 0;
    int *pvalue = &value;       // set pointer to refer to value

    printf("Input an integer: ");
    scanf_s(" %d", pvalue);     // read into value via the pointer

    printf("You entered %d.\n", value);     // output the value entered
    return 0;
}