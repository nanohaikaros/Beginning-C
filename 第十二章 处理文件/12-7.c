// Program 12.7 Writing, reading and updating a binary file
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXLEN 50

const char *filename = "my-people.bin";

typedef struct Record
{
    char name[MAXLEN];
    int age;
} Record;

void list_file(void);
void update_file(void);
Record *get_person(Record *precord);
void get_name(char *pname, size_t size);
void write_file(const char *mode);
void write_record(const Record *precord, FILE *pfile);
Record *read_record(Record *precord, FILE *pfile);
int find_record(Record *precord, FILE *pfile);
void duplicate_file(const Record *pnewrecord, int index, FILE *pfile);

int main(void)
{
    char answer = 'q';
    while(true)
    {
        printf_s("Choose from the following options:\n"
                " To list the file contents enter   L\n"
                " To create a new file enter        C\n"
                " To add new records enter          A\n"
                " To update existing records enter  U\n"
                " To delete the file enter          D\n"
                " To end the program enter          Q\n : ");
        scanf_s("\n%c", &answer, sizeof(answer));
        switch (toupper(answer))
        {
            case 'L':
                list_file();
                break;
            case 'C':
                write_file("wb+");
                printf_s("\nFile creation complete.\n");
                break;
            case 'A':
                write_file("ab+");
                printf_s("\nFile append complete.\n");
                break;
            case 'U':
                update_file();
                break;
            case 'D':
                printf_s("Are you sure you want to delete %s (y or n)? ", filename);
                scanf_s("\n%c", &answer, sizeof(answer));
                if(tolower(answer) == 'y')
                    remove(filename);
                break;
            case 'Q':
                printf_s("Ending the program.\n", filename);
                exit(0);
            default:
                printf_s("Invalid selection. Try again.\n");
                break;
        }
    }
    return 0;
}

Record *get_person(Record *precord)
{
    printf_s("Enter a name less than %d characters: ", MAXLEN);
    get_name(precord->name, MAXLEN);
    printf_s("Enter the age of %s: ", precord->name);
    scanf_s(" %d", &precord->age);
    return precord;
}

void get_name(char *pname, size_t size)
{
    fflush(stdin);
    fgets(pname, size, stdin);
    size_t len = strnlen_s(pname, size);
    if(pname[len - 1] == '\n')
        pname[len - 1] = '\0';
}

void write_record(const Record *precord, FILE *pfile)
{
    size_t length = strnlen_s(precord->name, sizeof(precord->name));
    fwrite(&length, sizeof(length), 1, pfile);
    fwrite(precord->name, sizeof(char), length, pfile);
    fwrite(&precord->age, sizeof(precord->age), 1, pfile);
}

Record *read_record(Record *precord, FILE *pfile)
{
    size_t length = 0;
    fread(&length, sizeof(length), 1, pfile);
    if(feof(pfile))
        return NULL;
    
    fread(precord->name, sizeof(char), length, pfile);
    precord->name[length] = '\0';
    fread(&precord->age, sizeof(precord->age), 1, pfile);

    return precord;
}

void write_file(const char *mode)
{
    char answer = 'y';

    FILE *pfile = NULL;
    if(fopen_s(&pfile, filename, mode))
    {
        fprintf_s(stderr, "File open failed.\n");
        exit(1);
    }

    do
    {
        Record record;
        write_record(get_person(&record), pfile);

        printf_s("Do you want to enter another(y or n)? ");
        scanf_s(" %c", &answer, sizeof(answer));
        fflush(stdin);
    } while (tolower(answer) == 'y');
    fclose(pfile);
}

void list_file(void)
{
    char format[18];
    sprintf_s(format, sizeof(format), "%%-%ds Age:%%4d\n", MAXLEN);

    FILE *pfile = NULL;
    if(fopen_s(&pfile, filename, "rb"))
    {
        fprintf_s(stderr, "Unable to open %s. Verify it exists.\n", filename);
        return ;
    }

    Record record;
    printf_s("The folks recorded in the %s file are:\n", filename);

    while(read_record(&record, pfile))
        printf_s(format, record.name, record.age);
    
    printf_s("\n");
    fclose(pfile);
}

void update_file(void)
{
    FILE *pfile = NULL;
    if(fopen_s(&pfile, filename, "rb+"))
    {
        fprintf_s(stderr, " File open for updating records failed."
                        " Maybe file does not exist.\n");
        return ;
    }

    Record record;
    int index = find_record(&record, pfile);
    if(index < 0)
    {
        printf_s("Record not found.\n");
        fclose(pfile);
        pfile = NULL;
        return ;
    }

    printf_s("%s is aged %d.\n", record.name, record.age);
    Record newrecord;
    printf_s("You can now enter the new name and age for %s.\n", record.name);
    get_person(&newrecord);

    if(strnlen_s(record.name, sizeof(record.name)) == strnlen_s(newrecord.name, sizeof(record.name)))
    {
        fseek(pfile, -(long)(sizeof(size_t) + strnlen_s(record.name, sizeof(record.name)) + sizeof(record.age)), SEEK_CUR);
        write_record(&newrecord, pfile);
        fflush(pfile);
        fclose(pfile);
        pfile = NULL;
    }
    else
        duplicate_file(&newrecord, index, pfile);
    printf_s("File update complete.\n");
}

void duplicate_file(const Record *pnewrecord, int index, FILE *pfile)
{
    char tempname[L_tmpnam];
    if(tmpnam_s(tempnam, sizeof(tempnam)))
    {
        fprintf_s(stderr, "Temporary file name creation failed.\n");
        exit(1);
    }
    FILE *ptempfile = NULL;
    if(fopen_s(&ptempfile, tempnam, "wb+"))
    {
        fprintf_s(stderr, "Temporary file creatiion failed.\n");
        exit(1);
    }

    rewind(pfile);
    Record record;
    for(int i = 0; i < index; ++i)
        write_record(read_record(&record, pfile), ptempfile);

    write_record(pnewrecord, ptempfile);
    read_record(&record, pfile);

    while(read_record(&record, pfile))
        write_record(&record, ptempfile);

    fclose(pfile);
    fclose(ptempfile);

    if(remove(filename))
    {
        fprintf_s(stderr, "Failed to remove the old file.\n");
        exit(1);
    }

    if(rename(tempnam, filename))
    {
        fprintf_s(stderr, "Renaming the file copy failed.\n");
        exit(1);
    }
}

int find_record(Record* precord, FILE* pfile)
{
    char name[MAXLEN];
    printf_s("Enter the name for the record you wish to find: ");
    get_name(name, MAXLEN);

    rewind(pfile);
    int index = 0;

    while(true)
    {
        if(!read_record(precord, pfile))
            return -1;
        
        if(!strcmp(name, precord->name))
            break;
        ++index;
    }
    return index;
}