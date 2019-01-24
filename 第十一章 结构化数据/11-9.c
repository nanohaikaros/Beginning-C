// Program 11.9 Generating a Bar chart
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define PAGE_HEIGHT 41
#define PAGE_WIDTH 75

typedef unsigned int uint;
typedef struct Bar Bar;

typedef struct Bar
{
    double value;
    Bar *pNext;
};

Bar *create_bar_list(void);
Bar *new_bar(void);
void bar_chart(Bar *pFirst, uint page_width, uint page_height, char *title);
void free_barlist_memory(Bar *pFirst);
char *chart_string(uint space, uint bar_width, char ch);
void draw_x_axis(uint length);

int main(void)
{
    Bar *pFirst = NULL;
    char title[80];

    printf_s("Enter the chart title: ");
    gets_s(title, sizeof(title));
    pFirst = create_bar_list();
    bar_chart(pFirst, PAGE_WIDTH, PAGE_HEIGHT, title);
    free_barlist_memory(pFirst);
    return 0;
}

void bar_chart(Bar *pFirst, uint page_width, uint page_height, char *title)
{
    Bar *pLast = pFirst;
    double max = pFirst->value;
    double min = pFirst->value;
    double vert_step = 0.0;
    uint bar_count = 1;
    uint bar_width = 0;
    uint space = 2;
    char *column = NULL;
    char *blank = NULL;
    double position = 0.0;
    bool axis = false;

    while(pLast = pLast->pNext)
    {
        ++bar_count;
        max = (max < pLast->value) ? pLast->value : max;
        min = (min > pLast->value) ? pLast->value : min;
    }

    if(max < 0.0) max = 0.0;
    if(min > 0.0) min = 0.0;
    vert_step = (max - min)/page_height;

    if((bar_width = page_width/bar_count - space) < 1)
    {
        printf_s("\nPage width too narrow.\n");
        exit(1);
    }

    if(!(column = chart_string(space, bar_width, '#')))
    {
        printf_s("\nFailed to allocate memory in bar_chart() - terminating progarm.\n");
        exit(1);
    }

    if(!(blank = chart_string(space, bar_width, ' ')))
    {
        printf_s("\nFailed to allocate memory in bar_chart() - terminating program.\n");
        exit(1);
    }

    printf_s("\n^ %s\n", title);
    position = max;

    for(uint i = 0; i < page_height; ++i)
    {
        if(position <= 0.0 && !axis)
        {
            draw_x_axis(bar_count*(bar_width + space));
            axis = true;
        }

        printf_s("|");
        pLast = pFirst;

        for(uint bars = 1; bars <= bar_count; ++bars)
        {
            printf_s("%s", position <= pLast->value && position > 0.0 || position >= pLast->value && position <= 0.0 ? column : blank);
            pLast = pLast->pNext;
        }
        printf_s("\n");
        position -= vert_step;
    }
    if(!axis)
        draw_x_axis(bar_count*(bar_width + space));
    else
        printf_s("v\n");

    free(blank);
    free(column);
}

void draw_x_axis(uint length)
{
    printf_s("+");
    for(uint x = 0; x < length; ++x)
        printf_s("-");
    printf_s(">\n");
}

char *chart_string(uint space, uint bar_width, char ch)
{
    char *str = malloc(bar_width + space + 1);
    if(str)
    {
        uint i = 0;
        for(; i < space; ++i)
            str[i] = ' ';
        
        for(; i < space + bar_width; ++i)
            str[i] = ch;
        
        str[i] = '\0';
    }
    return str;
}

Bar* create_bar_list(void)
{
    Bar *pFirst = NULL;
    Bar *pBar = NULL;
    Bar *pCurrent = NULL;
    while(pBar = new_bar())
    {
        if(pCurrent)
        {
            pCurrent->pNext = pBar;
            pCurrent = pBar;
        }
        else
            pFirst = pCurrent = pBar;
    }
    return pFirst;
}

Bar *new_bar(void)
{
    static char value[80];
    printf_s("Enter the value of the Bar, or Enter quit to end: ");
    gets_s(value, sizeof(value));
    if(strcmp(value, "quit") == 0)
        return NULL;

    Bar *pBar = malloc(sizeof(Bar));
    if(!pBar)
    {
        printf_s("Oops! Couldn't allocate memory for a bar.\n");
        exit(2);
    }
    pBar->value = atof(value);
    pBar->pNext = NULL;
    return pBar;
}

void free_barlist_memory(Bar *pBar)
{
    Bar* pTemp = NULL;
    while(pBar)
    {
        pTemp = pBar->pNext;
        free(pBar);
        pBar = pTemp;
    }
}