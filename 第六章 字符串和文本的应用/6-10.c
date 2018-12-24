// Program 6.10 Analyzing text
#define __STDC_WANT_LIB_EXT__ 1 // Make optional versions of functions available
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define TEXT_LEN 10000          // Maximum length of text
#define BUF_SIZE 100            // Input buffer size
#define MAX_WORDS 500           // Maximum number of different words
#define WORD_LEN 12             // Maximum word length

int main(void)
{
    char delimiters[] = " \n\".,;:!?)(";    // word delimiters
    char text[TEXT_LEN] = "";               // stores the complete text
    char buf[BUF_SIZE];                     // stores one input line
    char words[MAX_WORDS][WORD_LEN];        // stores words from the text
    char nword[MAX_WORDS] = {0};            // number of word occurrences
    char word_count = 0;                    // number of words stored

    printf("Enter text on an arbitrary number of lines.");
    pritnf("\nEnter an empty line to end input:\n");

    // read an arbitrary number of lines of text
    while(true)
    {
        // an empty string containing just a newline
        // signals end of input
        fgets(buf, BUF_SIZE, stdin);
        if(buf[0] == '\n')
            break;

        // check if we have space for latest input

        if(strcat_s(text, TEXT_LEN, buf))
        {
            printf("Maximum capacity for text exceeded. Terminating program.\n");
            return 1;
        }
    }

    // the code to find the words in the text array...

    // the code to output the words...

    return 0;
}