// Program 7.13 Extending dynamically allocated memory for strings
#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define BUF_LEN 100         // input buffer size
#define INIT_STR_EXT 50     // initial space for prose
#define WORDS_INCR 5        // words capacity increment

int main(void)
{
    char delimiters[] = " \n\".,;:!?)(";    // prose delimiters
    char buf[BUF_LEN];                  // buffer for a line of keyboard input
    size_t str_size = INIT_STR_EXT;     // current memory to store prose
    char* pStr = malloc(str_size);      // pointer to prose to be tokenized
    *pStr = '\0';                       // set 1st character to null

    printf("Enter some prose with up to %d characters per line.\nTerminate input by entering an empty line:\n", BUF_LEN);

    // read multiple lines of prose from the keyboard
    while(true)
    {
        fgets(buf, BUF_LEN, stdin);     // read a line of input
        if(buf[0] == '\n')              // an empty line ends input
            break;

        if(strnlen_s(pStr, str_size)+strnlen_s(buf, BUF_LEN)+1>str_size)
        {
            str_size = strnlen_s(pStr, str_size)+strnlen_s(buf, BUF_LEN)+1;
            pStr = realloc(pStr, str_size);
        }

        if(strcat_s(pStr, str_size, buf))   // concatenate the line with Pstr
        {
            printf("Something's wrong. String concatenation failed.\n");
            return 1;
        }
    }

    // find and list all the words in the prose

    size_t maxWords = 10;       // current maximum word count
    int word_count = 0;         // current word count
    size_t word_length = 0;     // current word length
    char** pWords = calloc(maxWords, sizeof(char*));    // stores pointers to the words
    int* pnWord = calloc(maxWords, sizeof(int));    // stores count for each word

    size_t str_len = strnlen(pStr, str_size);   // length used by strtok_s()
    char* ptr = NULL;       // pointer used by strtok_s()
    char* pWord = strtok_s(pStr, &str_len, delimiters, &ptr);   // find 1st word

    if(!pWord)
    {
        printf("No words found. Ending program.\n");
        return 1;
    }

    bool new_word = true;       // false for an existing word
    while(pWord)
    {
        // check for existing word
        for(int i=0; i<word_count; ++i)
        {
            if(strcmp(*(pWords+1), pWord) == 0)
            {
                ++*(pnWord+i);
                new_word = false;
                break;
            }
        }

        if(new_word)        // check for new word
        {
            // check for suffocient memory
            if(word_count == maxWords)
            {
                // get more space for pointers to words
                maxWords += WORDS_INCR;
                pWords = realloc(pWords, maxWords*sizeof(char*));

                // get more space for word counts
                pnWord = realloc(pnWord, maxWords*sizeof(int));
            }

            // found a new word so get memory for it and copy it there
            word_length = ptr - pWord;      // length of new word
            *(pWords+word_count) = malloc(word_length); // allocate memory for word
            strcpy_s(*(pWords+word_count), word_length, pWord); // copy to array
            *(pnWord+word_count++) = 1; // set new word count
        }
        else
            new_word = true;    // reset new word flag
        
        pWord = strtok_s(NULL, &str_len, delimiters, &ptr);   // find subsequent word

        // output the words and counts

        for(int i=0; i<word_count; ++i)
        {
            printf(" %-13s %3d", *(pWords+i), *(pnWord+i));
            if((i+1)%4 == 0)
                printf("\n");
        }
        printf("\n");

        // free the memory for words
        for(int i=0; i<word_count; ++i)
        {
            free(*(pWords+i));      // free memory for word
            *(pWords+i) = NULL;     // reset the pointer
        }
    }

    free(pWords);       // free memory for pointers to words
    pWords = NULL;
    free(pnWord);       // free memory for word count
    pnWord = NULL;
    free(pStr);         // free memory for peose
    pStr = NULL;
    return 0;
    
}