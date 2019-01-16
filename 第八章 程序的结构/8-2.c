// Program 8.2 More scope in this example
#include <stdio.h>

int main(void)
{
    int count = 0;
    do
    {
        int count = 0;
        ++count;
        printf("count = %d\n", count);
    } while(++count <= 5);

    printf("count = %d\n", count);
    return 0;
}