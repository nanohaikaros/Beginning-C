// Program 9.3 Passing a Pointer to a function
#include <stdio.h>

int sum(int, int);
int product(int, int);
int difference(int, int);
int any_function(int(*pfun)(int, int), int x, int y);

int main(void)
{
    int a = 10;
    int b = 5;
    int result = 0;
    int (*pf)(int, int) = sum;

    result = any_function(pf, a, b);

    printf("result = %2d\n", result);

    result = any_function(product, a, b);

    printf("result = %2d\n", result);

    printf("result = %2d\n", any_function(difference, a, b));
    return 0;
}

int any_function(int(*pfun)(int, int), int x, int y)
{
    return pfun(x, y);
}

int sum(int x, int y)
{
    return x + y;
}

int product(int x, int y)
{
    return x * y;
}

int difference(int x, int y)
{
    return x - y;
}