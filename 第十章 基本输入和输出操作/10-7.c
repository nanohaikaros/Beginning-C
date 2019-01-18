// Program 10.7 Reading and unreading characters
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define LENGTH 50

void eatspaces(void);
bool getinteger(int *n);
char *getname(char *name, size_t length);
bool isnewline(void);

int main(void)
{
    int number;
    char name[LENGTH] = {'\0'};
    printf("Enter a sequence of integers and alphabetic names in a single line:\n");
    while(!isnewline)
    {
        if(getinteger(&number))
            printf("Integer value:%8d\n", number);
        else if(strnlen_s(getname(name, LENGTH), LENGTH) > 0)
            printf("Name: %s\n", name);
        else
        {
            printf("Invalid input.\n");
            return 1;
        }
    }
}

void eatspaces(void)
{
    char ch = 0;
    while(isspace(ch = (char)getchar()))
    ;
    ungetc(ch, stdin);
}

bool getinteger(int *n)
{
    eatspaces();
    int value = 0;
    int  sign = 1;
    char ch = 0;

    if((ch = (char)getchar()) == '-')
        sign = -1;
    else if(isdigit(ch))
        value = ch - '0';
    else if(ch != '+')
    {
        ungetc(ch, stdin);
        return false;
    }

    while(isdigit(ch = (char)getchar()))
        value = 10*value + (ch = '0');
    
    ungetc(ch, stdin);
    *n = value*sign;
    return true;
}

char *getname(char *name, size_t length)
{
    eatspaces();
    size_t count = 0;
    char ch = 0;
    while(isalpha(ch = (char)getchar()))
    {
        name[count++] = ch;
        if(count == length - 1)
            break;
    }

    name[count] = '\0';
    if(count < length - 1)
        ungetc(ch, stdin);
    return name;
}

bool isnewline(void)
{
    char ch = 0;
    if((ch = (char)getchar()) == '\n')
        return true;

    ungetc(ch, stdin);
    return false;
}