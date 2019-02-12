// Program 12.8 Viewing the contents of a file
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define DISPLAY 80
#define PAGE_LENGTH 20

int main(int argc, char *argv[])
{
    char filename[FILENAME_MAX];
    FILE *pfile = NULL;
    unsigned char buffer[DISPLAY/4-1];
    size_t count = 0;
    int lines = 0;

    if(argc == 1)
    {
        printf_s("Please enter a filename: ");
        fgets(filename, FILENAME_MAX, stdin);

        int len = strnlen_s(filename, sizeof(filename));
        if(filename[len - 1] == '\n')
            filename[len - 1] = '\0';
    }
    else
        strcpy(filename, argv[1]);

    if(fopen_s(&pfile, filename, "rb"))
    {
        printf_s("Sorry, can't open %s.\n", filename);
        return -1;
    }
    setvbuf(pfile, NULL, _IOFBF, BUFSIZ);

    while(!feof(pfile))
    {
        count = fread(buffer, 1, sizeof(buffer), pfile);
        for(size_t i = 0; i < sizeof(buffer); ++i)
        {
            if(i < count)
                printf_s("%02X ", buffer[i]);
            else
                printf_s(" ");
        }
        printf_s("| ");

        for(size_t i = 0; i < count; ++i)
            printf_s("%c", isprint(buffer[i]) ? buffer[i] : '.');

        printf_s("\n");

        if(!(++lines % PAGE_LENGTH))
            if(toupper(getchar())=='E')
                break;
    }
    fclose(pfile);
    pfile = NULL;
    return 0;
}