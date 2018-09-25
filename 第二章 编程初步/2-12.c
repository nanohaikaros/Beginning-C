// Program 2.12 Finding the size of a type
#include <stdio.h>

int main(void)
{
    printf("Varibles of type char occupy %u bytes\n", sizeof(char));
    printf("Varibles of type short occupy %u bytes\n", sizeof(short));
    printf("Varibles of type int occupy %u bytes\n", sizeof(int));
    printf("Varibles of type long occupy %u bytes\n", sizeof(long));
    printf("Varibles of type long long occupy %u bytes\n", sizeof(long long));
    printf("Varibles of type float occupy %u bytes\n", sizeof(float));
    printf("Varibles of type double occupy %u bytes\n", sizeof(double));
    printf("Varibles of type long double occupy %u bytes\n", sizeof(long double));
    return 0;
}
