// Program 11.1 Exercising the horse
#include <stdio.h>

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
    Horse my_horse;

    printf_s("Enter the name of the horse: ");
    scanf_s("%s", my_horse.name, sizeof(my_horse.name));

    printf_s("How old is %s? ", my_horse.name);
    scanf_s("%d", &my_horse.age);

    printf_s("How high is %s ( in hands )? ", my_horse.name);
    scanf_s("%d", &my_horse.height);

    printf_s("Who is %s's father? ", my_horse.name);
    scanf_s("%s", my_horse.father, sizeof(my_horse.father));

    printf_s("Who is %s's mother? ", my_horse.name);
    scanf_s("%s", my_horse.mother, sizeof(my_horse.mother));

    printf_s("%s is %d years old, %d hands high,", my_horse.name, my_horse.age, my_horse.height);
    printf_s(" and has %s and %s as parents.\n", my_horse.father, my_horse.mother);

    return 0;
}