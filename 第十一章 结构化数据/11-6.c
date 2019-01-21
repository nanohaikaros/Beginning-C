// Program 11.6 Basics of a familly tree
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Date Date;
typedef struct Family Family;

Family *get_person(void);
void show_prople(bool forwards, Family *pfirst, Family *plast);
void release_memory(Family *pfirst);

struct Date
{
    int day;
    int month;
    int year;
};

struct Family
{
    Date dob;
    char name[20];
    char father[20];
    char mother[20];
    Family *next;
    Family *previous;
};

int main(void)
{
    Family *first = NULL;
    Family *current = NULL;
    Family *last = NULL;
    char more = '\0';

    while(true)
    {
        printf_s("\nDo you want to enter details of a%s person (Y or N)?", first != NULL ? "nother" : "");

        scanf_s(" %c", &more, sizeof(more));
        if(tolower(more) == 'n')
            break;
        
        current = get_person();

        if(first == NULL)
            first = current;
        else
        {
            last->next = current;
            current->previous = last;
        }
        last = current;
    }

    show_prople(true, first, last);
    release_memory(first);
    first = last = NULL;
    
    return 0;
}

Family *get_person(void)
{
    Family *temp = (Family*)malloc(sizeof(Family));

    printf_s("\nEnter the name of the person: ");
    scanf_s("%s", temp->name, sizeof(temp->name));

    printf_s("\nEnter %s's date of birth (day month year): ", temp->name);
    scanf_s("%d %d %d", &temp->dob.day, &temp->dob.month, &temp->dob.year);

    printf_s("\nWho is %s's fahter? ", temp->name);
    scanf_s("%s", temp->father, sizeof(temp->father));

    printf_s("\nWho is %s's mother? ", temp->name);
    scanf_s("%s", temp->mother, sizeof(temp->mother));

    temp->next = temp->previous = NULL;

    return temp;
}

void show_people(bool forwards, Family *pfirst, Family *plast)
{
    printf_s("\n");
    for(Family *pcurrent = forwards ? pfirst : plast; pcurrent != NULL; pcurrent = forwards ? pcurrent->next : pcurrent->previous)
    {
        printf_s("%s was born %d/%d/%d and has %s and %s as parents.\n", pcurrent->name, pcurrent->dob.day, pcurrent->dob.month, pcurrent->dob.year, pcurrent->father, pcurrent->mother);
    }
}

void release_memory(Family *pfirst)
{
    Family *pcurrent = pfirst;
    Family *temp = NULL;
    while(pcurrent)
    {
        temp = pcurrent;
        pcurrent = pcurrent->next;
        free(temp);
    }
}

void release_memory(Family *pfirst)
{
    Family *pcurrent = pfirst;
    Family *temp = NULL;
    while(pcurrent)
    {
        temp = pcurrent;
        pcurrent = pcurrent->next;
        free(temp);
    }
}
