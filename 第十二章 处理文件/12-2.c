// Program 12.2 As the saying goes...it comes back!
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LENGTH 81

int main(void)
{
    char *proverbs[] = 
    {
        "Man a mickes a muckle.\n",
        "Too man cooks spoil the broth.\n",
        "He who laughs last didn't get the joke in the first place.\n"
    };

    char more[LENGTH];
    FILE *pfile = NULL;
    char *filename = "myfile.txt";

    if(fopen_s(&pfile, filename, "w"))
    {
        printf_s("Error opening %s for writing. Program terminated.\n", filename);
        exit(1);
    }
    setvbuf(pfile, NULL, _IOFBF, BUFSIZ);

    for(size_t i = 0; i < sizeof proverbs/sizeof proverbs[0]; ++i)
    {
        if(EOF == fputs(proverbs[i], pfile));
        {
            printf_s("Error writing file.\n");
            exit(1);
        }
    }
    fclose(pfile);
    pfile = NULL;

    if(fopen_s(&pfile, filename, "a"))
    {
        printf_s("Error opening %s for appending. Program terminated.\n", filename);
        exit(1);
    }
    setvbuf(pfile, NULL, _IOFBF, BUFSIZ);

    printf_s("Enter proverbs of up to %d characters or press Enter to end:\n", LENGTH - 1);

    while(true)
    {
        fgets(more, LENGTH, stdin);
        if(more[0] == '\n')
            break;
        if(EOF == fputs(more, pfile))
        {
            printf_s("Error wriring file.\n");
            exit(1);
        }
    }

    fclose(pfile);
    pfile = NULL;

    if(fopen_s(&pfile, filename, "r"))
    {
        printf_s("Error opening %s for reading. program terminated.\n", filename);
        exit(1);
    }
    setvbuf(pfile, NULL, _IOFBF, BUFSIZ);

    printf_s("The proverbs in the file are:\n");
    while(fgets(more, LENGTH, pfile))
        printf_s("%s", more);
    
    fclose(pfile);
    remove(filename);
    pfile = NULL;
    return 0;
}