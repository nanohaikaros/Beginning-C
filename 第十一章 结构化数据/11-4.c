// Program 11.4 Daisy chaining the horses
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct Horse Horse;

struct Horse
{
    int age;
    int height;
    char name[20];
    char father[20];
    char mother[20];
    Horse *next;
};

int main(void)
{
    Horse *first = NULL;
    Horse *current = NULL;
    Horse *previous = NULL;

    char test = '\0';

    for(;;)
    {
        printf_s("Do you want to enter details of a%s horse (Y or N)?", first != NULL?"nother":"");
        scanf_s(" %c", &test, sizeof(test));
        if(tolower(test) == '\n')
            break;

        current = (Horse*)malloc(sizeof(Horse));
        if(first == NULL)
            first = current;

        if(previous != NULL)
            previous->next = current;

        printf_s("Enter the name of the horse: ");
        scanf_s("%s", current->name, sizeof(current->name));

        printf_s("How old is %s? ", current->name);
        scanf_s("%d", &current->age);

        printf_s("How high is %s (in hands)?", current->name);
        scanf_s("%d", &current->height);

        printf_s("Who is %s's father? ", current->name);
        scanf_s("%s", current->father, sizeof(current->father));

        printf_s("Who is %s's mother? ", current->name);
        scanf_s("%s", current->mother, sizeof(current->mother));

        current->next = NULL;
        previous = current;
    }

    printf_s("\n");
    current = first;
    while(current != NULL)
    {
        printf_s("%s is %d years old, %d hands high,", current->name, current->age, current->height);
        printf_s(" and has %s and %s as parents.\n", current->father, current->mother);
        previous = current;
        current = current->next;
        free(previous);
        previous = NULL;
    }
    first = NULL;
    return 0;
}