// Program 8.4 The functional approach to string sorting 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define BUF_LEN 256
#define INIT_NSTR 2
#define NSTR_INCR 2

char* str_in();
void str_sort(const char**, size_t);
void swap(const char**, const char**);
void str_out(const char* const*, size_t);
void free_memory(char**, size_t);

int main(void)
{
    size_t pS_size = INIT_NSTR;
    char **pS = calloc(pS_size, sizeof(char*));
    if(!pS)
    {
        printf("Failed to allocate memory for string pointers.\n");
        exit(1);
    }

    char **pTemp = NULL;

    size_t str_count = 0;
    char *pStr = NULL;
    printf("Enter one srting pre line. Press Enter to end:\n");
    while((pStr = str_in()) != NULL)
    {
        if(str_count == pS_size)
        {
            pS_size += NSTR_INCR;
            if(!(pTemp = realloc(pS, pS_size*sizeof(char*))))
            {
                printf("Memory allocation for array of strings failed.\n");
                return 2;
            }
            pS = pTemp;
        }
        pS[str_count++] = pStr;
    }

    str_sort(pS, str_count);
    str_out(pS, str_count);
    free_memory(pS, str_count);
    return 0;
}

char* str_in(void)
{
    char buf[BUF_LEN];
    if(!gets_s(buf, BUF_LEN))
    {
        printf("\nError reading string.\n");
        return NULL;
    }

    if(buf[0] == '\0')
        return NULL;

    size_t str_len = strnlen(buf, BUF_LEN);
    char *pString = malloc(str_len);

    if(!pString)
    {
        printf("Memory allocation failure.\n");
        return NULL;
    }

    strcpy_s(pString, str_len, buf);
    return pString;
}

void str_sort(const char **p, size_t n)
{
    bool sorted = false;
    while(!sorted)
    {
        sorted = true;
        for(int i = 0; i < n-1; ++i)
        {
            if(strcmp(p[i], p[i+1]) > 0)
            {
                sorted = false;
                swap(&p[i], &p[i+1]);
            }
        }
    }
}

void swap(const char** p1, const char ** p2)
{
    const char *pT = *p1;
    *p1 = *p2;
    *p2 = pT;
}

void str_out(const char* const* pStr, size_t n)
{
    printf("The sorted strings are:\n");
    for(size_t i = 0; i < n; ++i)
        printf("%s\n", pStr[i]);
}

void free_memory(char **pS, size_t n)
{
    for(size_t i = 0; i < n; ++n)
    {
        free(pS[i]);
        pS[i] = NULL;
    }
    free(pS);
    pS = NULL;
}