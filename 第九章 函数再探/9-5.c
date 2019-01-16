// Program 9.5 Global variables
#include <stdio.h>

int count = 0;

void test1(void);
void test2(void);

int main(void)
{
    int count = 0;

    for(; count < 5; ++count)
    {
        test1();
        test2();
    }

    return 0;
}

void test1(void)
{
    printf("test1 count = %d\n", ++count);
}

void test2(void)
{
    static int count;
    printf("test2 count = %d\n", ++count);
}
