// Prgoram 13.1 Debugging using preprocessing directives
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define random(NumValues) ((int)(((double)(rand())*(NumValues))/(RAND_MAX+1.0)))

#define iterations 6
#define test
#define testf
#define repeatable

int sum(int, int);
int product(int, int);
int difference(int, int);

int main(void)
{
    int funsel = 0;
    int a = 10, b = 5;
    int result = 0;

    int (*pfun[])(int, int) = {sum, product, difference};

#ifdef repeatable
    srand(1);
#else
    srand((unsigned int)time(NULL));
#endif

    int element_count = sizeof(pfun)/sizeof(pfun[0]);
    for(int i = 0; i < iterations; ++i)
    {
        funsel = random(element_count);
        if(funsel > element_count - 1)
        {
            printf_s("Invalid array index = %d\n", funsel);
            exit(1);
        }

#ifdef test
    printf_s("Random index = %d\n", funsel);
#endif
    result = pfun[funsel](a, b);

    printf_s("result = %d\n", result);
    }

    return 0;
}

int sum(int x, int y)
{
#ifdef testf
    printf_s("Function sum called args %s and %d.\n", x, y);
#endif
    return x + y;
}

int product(int x, int y)
{
#ifdef testf
    printf_s("Function product called args %s and %d", x, y);
#endif
    return x * y;
}

int difference(int x, int y)
{
#ifdef testf
    printf_s("Function difference called args %d and %d", x, y);
#endif
    return x - y;
}