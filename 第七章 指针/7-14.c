// Program 7.14 using array notation with pointers to sort strings
#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUF_LEN 100         // length of input buffer
#define COUNT 5             // initial number of strings

int main(void)
{
    char buf[BUF_LEN];      // input buffer
    size_t str_count = 0;   // current string count
    size_t capacity = COUNT;// current maximum number of strings
    char **pS = calloc(capacity, sizeof(char*));    // pointers to strings
    char** psTemp = NULL;   // temporary pointer to pointer to char
    char* pTemp = NULL;     // temporary pointer to char
    size_t str_len = 0;     // length of a string
    bool sorted = false;    // indicated when strings are sorted

    printf("Enter strings to be sorted, one per line. Press Enter to end:\n");

    // read in all the strings
    char *ptr = NULL;
    while(true)
    {
        ptr = fgets(buf, BUF_LEN, stdin);
        if(!ptr)            // check for read error
        {
            printf("Error reading string.\n");
            free(pS);
            pS = NULL;
            return 1;
        }

        if(*ptr == '\n') break;     // empty line check
        if(str_count == capacity)
        {
            capacity += capacity/4;     // increase capacity by 25%

            if(!(psTemp = realloc(pS, capacity)))
                return 1;
            
            pS = psTemp;
        }

        str_len = strnlen_s(buf, BUF_LEN)+1;
        if(!(pS[str_count] = malloc(str_len)))
            return 2;

        strcpy_s(pS[str_count++], str_len, buf);
    }

    // sort the strings in ascending order
    while(!sorted)
    {
        sorted = true;
        for(size_t i=0; i<str_count-1; ++i)
        {
            if(strcmp(pS[i], pS[i+1])>0)
            {
                sorted = false;     // we were out of order so...
                pTemp = pS[i];      // swap pointers pS[i]...
                pS[i] = pS[i+1];    // and...
                pS[i+1] = pTemp;    // pS[i+1]
            }
        }
    }

    // output the sorted strings
    printf("Your input sorted in ascending sequence is:\n\n");
    for(size_t i=0; i<str_count; ++i)
    {
        printf("%s", pS[i]);
        free(pS[i]);                // release memory for the word
        pS[i] = NULL;               // reset the pointer
    }
    free(pS);           // release the memory for pointers
    pS = NULL;          // reset the pointer
    return 0;
}