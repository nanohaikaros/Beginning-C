// Program 11.2 Ecercising the horses
#include <stdio.h>
#include <ctype.h>

typedef struct Horse Horse;

struct Horse 
{
    int age;
    int height;
    char name[20];
    char father[20];
    char mother[20];
};

int main(void)
{
    Horse my_horses[50];
    int hcount = 0;
    char test = '\0';

    for(hcount = 0; hcount < sizeof(my_horses)/sizeof(Horse); ++hcount)
    {
        printf_s("Do you want to enter details of a%s horse (Y or N)?", hcount?"nother":"");

        scanf_s(" %c", &test, sizeof(test));
        if(tolower(test) == 'n')
            break;

        printf_s("Enter the name of the horse: ");
        scanf_s("%s", my_horses[hcount].name, sizeof(my_horses[hcount].name));

        printf_s("How old is %s?", my_horses[hcount].name);
        scanf_s("%d", &my_horses[hcount].age);

        printf_s("How high is %s ( in hands ) ?", my_horses[hcount].name);
        scanf_s("%d", &my_horses[hcount].height);

        printf_s("Who is %s's father?", my_horses[hcount].name);
        scanf_s("%s", my_horses[hcount].father, sizeof(my_horses[hcount].father));

        printf_s("Who is %s's mother?", my_horses[hcount].name);
        scanf_s("%s", my_horses[hcount].mother, sizeof(my_horses[hcount].mother));
    }

    printf_s("\n");
    for(int i = 0; i < hcount; ++i)
    {
        printf_s("%s is %d years old, %d hands high,", my_horses[i].name, my_horses[i].age, my_horses[i].height);
        printf_s(" and has %s and %s as parents.\n", my_horses[i].father, my_horses[i].mother);
    }

    return 0;
}
