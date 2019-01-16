// Program 9.6 Calculating factorials using recursion
#include <stdio.h>

unsigned long long factorial(unsigned long long);

int main(void)
{
    unsigned long long number = 0LL;
    printf("Enter an integer value: ");
    scanf("%llu", &number);
    printf("The factorial of %llu is %llu\n", number, factorial(number));
    return 0;
}

unsigned long long factorial(unsigned long long n)
{
    if(n < 2LL)
        return n;

    return n*factorial(n - 1LL);
}