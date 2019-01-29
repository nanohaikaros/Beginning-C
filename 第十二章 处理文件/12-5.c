// Program 12.5 investigating the family
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NAME_MAX 20

struct
{
    char *filename;
    FILE *pfile;
} global = {.filename = "myfile.bin", .pfile = NULL};

typedef struct Date
{
    int day;
    int month;
    int year;
} Date;

typedef struct Family
{
    Date dob;
    char name[NAME_MAX];
    char pa_name[NAME_MAX];
    char ma_name[NAME_MAX];
} Family;



bool get_person(Family *pfamily);
void getname(char *name, size_t size);
void show_person_date(void);
void get_parent_dob(Family *pfamily);
void open_file(char *mode);
inline void close_file(void);

int main(void)
{
    Family member;
    open_file("ab");
    while(get_person(&member))
        fwrite(&member, sizeof member, 1, global.pfile);
    fclose(global.pfile);

    show_person_date();

    if(remove(global.filename))
        printf_s("Unable to delete %s.\n", global.filename);
    else
        printf_s("Deleted %s OK.\n", global.filename);
    return 0;
}

bool get_person(Family *temp)
{
    static char more = '\0';

    printf_s("\nDo you want to enter details of %s person (Y or N)? ", more != '\0' ? "another" : "a");
    scnaf_s("Enter the name of the person: ");
    getname(temp->name, sizeof(temp->name));

    printf_s("Enter %s's date of birth (day month year): ", temp->name);
    scnaf_s(" %d %d %d", &temp->dob.day, &temp->dob.month, &temp->dob.year);

    printf_s("Who is %s's father?", temp->name);
    getname(temp->name, sizeof(temp->pa_name));

    printf_s("Who is %s's mother? ", temp->name);
    getname(temp->ma_name, sizeof(temp->ma_name));

    return true;
}

void getname(char *name, size_t size)
{
    fflush(stdin);
    fgets(name, size, stdin);
    int len = strnlen_s(name, size);
    if(name[len - 1] == '\n')
        name[len - 1] = '\0';
}

void show_person_date(void)
{
    Family member;
    open_file("rb");

    while(fread(&member, sizeof member, 1, global.pfile))
    {
        printf_s("%s's father is %s, and mother is %s.\n", member.name, member.pa_name, member.ma_name);
        get_parent_dob(&member);
    }
    close_file();
}

void get_parent_dob(Family *pmember)
{
    Family relative;
    int num_found = 0;
    fpos_t current;
    fgetpos(global.pfile, &current);
    rewind(global.pfile);

    while(fread(&relative, sizeof(Family), 1, global.pfile))
    {
        if(strcmp(pmember->pa_name, relative.name) == 0)
        {
            printf_s(" Pa was born on %d/%d/%d.", relative.dob.day, relative.dob.month, relative.dob.year);
            ++num_found;
        }
        else if(strcmp(pmember->ma_name, relative.name) == 0)
        {
            printf_s(" Ma was born on %d/%d/%d.", relative.dob.day, relative.dob.month, relative.dob.year);
            ++num_found;
        }
        if(num_found == 2)
            break;
    }
    if(!num_found)
        printf_s(" No info on parents available.");
    printf_s("\n");
    fsetpos(global.pfile, &current);
}

void open_file(char *mode)
{
    if(global.pfile)
        close_file();
    if(fopen_s(&global.pfile, global.filename, mode))
    {
        printf_s("Unable to open %s with mode %s.\n", global.filename, mode);
        exit(1);
    }
    setvbuf(global.pfile, NULL, _IOFBF, BUFSIZ);
}

inline void close_file(void)
{
    fclose(global.pfile);
    global.pfile = NULL;
}