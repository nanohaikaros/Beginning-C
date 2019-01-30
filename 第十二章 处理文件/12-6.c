// Program 12.6 Writing a binary file with an update mode
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 50

int main(void)
{
    const char *filename = "mpeople.bin";
    char name[MAXLEN];
    size_t length = 0;
    int age = 0;
    char answer = 'y';
    FILE *pfile = NULL;
    if(fopen_s(&pfile, filename, "wb+"))
    {
        printf_s("Failed to create file %s.\n", filename);
        exit(1);
    }

    do
    {
        fflush(stdin);
        printf_s("Enter a name less than %d characters: ", MAXLEN);
        gets_s(name, sizeof(name));

        printf_s("Enter the age of %s: ", name);
        scanf_s(" %d", &age);

        length = strnlen_s(name, sizeof(name));
        fwrite(&length, sizeof(length), 1, pfile);
        fwrite(name, sizeof(char), length, pfile);
        fwrite(&age, sizeof(age), 1, pfile);

        printf_s("Do you want to enter another(y or n)? ");
        scanf_s("\n%c", &answer, sizeof(answer));
    } while (tolower(answer) == 'y');

    fclose(pfile);
    listfile(filename);
    return 0; 
}

void listfile(const char *filename)
{
    size_t length = 0;
    char name[MAXLEN];
    int age = 0;
    char format[20];
    FILE *pfile = NULL;

    sprintf_s(format, sizeof(format), "%%-%ds Age:%%4d\n", MAXLEN);

    if(fopen_s(&pfile, filename, "rb"))
    {
        printf_s("Failed to open file %s to read it.\n", filename);
        exit(1);
    }
    printf_s("\nThe folks recorded in the %s file are:\n", filename);

    while(fread(&length, sizeof(length), 1, pfile) == 1)
    {
        if(length + 1 > MAXLEN)
        {
            printf_s("Name too long.\n");
            exit(1);
        }
        fread(name, sizeof(char), length, pfile);
        name[length] = '\0';
        fread(&age, sizeof(age), 1, pfile);
        printf_s(format, name, age);
    }
    fclose(pfile);
}