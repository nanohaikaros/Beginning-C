// Program 11.8 The operation of a union
#include <stdio.h>

typedef union UDate UDate;
typedef struct Date Date;
typedef struct MixedDate MixedDate;
typedef struct NumericDate NumericDate;

void print_date(const Date* date);

enum Date_Format{numeric, text, mixed};

struct MixedDate
{
    char *day;
    char *date;
    int year;
};

struct NumericDate
{
    int day;
    int month;
    int year;
};

union UDate
{
    char *date_str;
    MixedDate day_date;
    NumericDate nDate;
};

struct Date
{
    enum Date_Format format;
    UDate date;
};

int main(void)
{
    NumericDate yesterday = {11, 11, 2012};
    MixedDate today = {"Monday", "12th Novemver", "2012"};
    char tomorrow[] = "Tues 13th nov 2012";

    UDate udate = {tomorrow};
    Date the_date;
    the_date.date = udate;
    the_date.format = text;
    print_date(&the_date);

    the_date.date.nDate = yesterday;
    the_date.format = numeric;
    print_date(&the_date);

    the_date.date.day_date = today;
    the_date.format = mixed;
    print_date(&the_date);

    return 0;
}

void print_date(const Date* date)
{
    switch(date->format)
    {
        case numeric:
            printf_s("The date is %d/%d/%d.\n", date->date.nDate.day, date->date.nDate.month, date->date.nDate.year);
            break;
        case text:
            printf_s("The date is %s.\n", date->date.date_str);
            break;
        case mixed:
            printf_s("The date is %s %s %s.\n", date->date.day_date.day, date->date.day_date.date, date->date.day_date.year);
            break;

        default:
            printf_s("invalid date format.\n");
    }
}