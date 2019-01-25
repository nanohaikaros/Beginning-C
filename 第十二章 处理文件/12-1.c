// Program 12.1 Writing a file a character at a time
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 81

int main(void)
{
    char mystr[LENGTH];
    int mychar = 0;
    FILE *pfile = NULL;
    char *filename = "myfile.text";

    printf("Enter an interesting string of up to %d characters:\n", LENGTH - 1);

    if(!fgets(mystr, LENGTH, stdin))
    {
        printf_s("Input from keyboard failed.\n");
        exit(1);
    }

    if(fopen_s(&pfile, filename, "w"))
    {
        printf_s("Error opening %s for writing. Program terminated.\n", filename);
        exit(1);
    }

    setvbuf(pfile, NULL, _IOFBF, BUFSIZ);

    for(int i = strnlen_s(mystr, LENGTH) - 1; i >= 0; --i)
        fputc(mystr[i], pfile);

    fclose(pfile);

    if(fopen_s(&pfile, filename, "r"))
    {
        printf_s("Error opening %s for reading. Program teminated.", filename);
        exit(1);
    }
    setvbuf(pfile, NULL, _IOFBF, BUFSIZ);

    printf_s("the data read from the file is:\n");
    while((mychar = fgetc(pfile)) != EOF)
        putchar(mychar);
    putchar('\n');

    fclose(pfile);
    pfile = NULL;
    remove(filename);
    return 0;
}