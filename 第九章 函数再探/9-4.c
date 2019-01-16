// Progarm 9.4 Static versus automatic variables
#include <stdio.h>

void test1(void);
void test2(void);

int main(void)
{
    for(int i = 0; i < 5; ++i)
    {
        test1();
        test2();
    }
    return 0;
}

void test1(void)
{
    int count = 0;
    printf("test1 count = %d\n", ++count);
}

void test2(void)
{
    static int count = 0;
    printf("test2 count = %d\n", ++count);
}