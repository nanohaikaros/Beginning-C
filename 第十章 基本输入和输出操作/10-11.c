// Program 10.11 Outputting character data
#include <stdio.h>
#include <limits.h>
#include <ctype.h>

int main(void)
{
    int count = 0;

    printf_s("The printfable characters are the following: \n");

    for(int code = 0; code <= CHAR_MAX; ++code)
    {
        char ch = (char)code;
        if(isprint(ch))
        {
            if(count++ % 32 == 0)
                printf_s("\n");
            printf_s(" %c", ch);
        }
    }
    printf_s("\n");
    return 0;
}