// program 10.1 Exercising formatted input
#include <stdio.h>
#define SIZE 20

void try_input(char *prompt, char *format);

int main(void)
{
    try_input("Enter as input: -2.35 15 25 ready2go\n",
            "%f %d %d %[abcdefghijklmnopqrstuvwxyz] %*ld %s%n");
    
    
    try_input("\nEnter the same input again: ",
            "%4f %4d %d %*d %[abcdefghijklmnopqrstuvwxyz] %ld %[^o]%n");

    try_input("\nEnter as input: -2.3A 15 25 ready2go\n",
            "%4f %4d %d %*d %[abcdefghijklmnopqrstuvwxyz] %*ld %[^o]%n");

    return 0;
}

void try_input(char* prompt, char *format)
{
    int value_count = 0;
    float fp1 = 0.0f;
    int i = 0;
    int j = 0;
    char word1[SIZE] = " ";
    char word2[SIZE] = " ";
    int byte_count = 0;
    printf(prompt);
    value_count = scanf_s(format, &fp1, &i, &j, word1, sizeof(word1), word2, sizeof(word2), &byte_count);
    fflush(stdin);
    printf("The input format string for scanf_s() is:\n \"%s\"\n", format);
    printf("Count of bytes read = %d\n", byte_count);
    printf("Count of values read = %d\n", value_count);
    printf("fp1 = %f i = %d j = %d\n", fp1, i , j);
    printf("word1 = %s word2 = %s\n", word1, word2);
}