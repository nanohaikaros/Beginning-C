// Program 7.11 A dynamic prime example
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void)
{
    unsigned long long *pPrimers = NULL;    // ponter to primes storage area
    unsigned long long trial = 0;           // integer to be tested
    bool found = false;                     // indicates when we find a prime
    int total = 0;                          // number of primes required
    int count = 0;                          // number of primes found

    printf("How many primes would you like - you'll get at least 4? ");
    scanf("%d", &total);      // total is how many we need to find
    total = total < 4 ? 4 : total;      // make sure it is at least 4

    // allocate sufficient memory to store the number of primes required
    pPrimers = (unsigned long long*)malloc(total*sizeof(unsigned long long));
    if(!pPrimers)
    {
        printf("Not enough memory. It's the end I'm afraid.\n");
        return 1;
    }

    // we know the first three primes so let's give the program a start
    *pPrimers = 2ULL;           // first prime
    *(pPrimers+1) = 3ULL;       // second prime
    *(pPrimers+2) = 5ULL;       // third prime
    count = 3;                  // number of primes stored
    trial = 5ULL;               // set to the last prime we have

    // find all the primes required
    while(count<total)
    {
        trial += 2ULL;          // next value for checking

        // divide by the primes we have. if any divide exactly - it's not prime
        for(int i=1; i<count; ++i)
        {
            if(!(found=(trial%*(pPrimers+i))))
            break;          // exit if zero remainder
        }

        if(found)           // we got one - if found is true
            *(pPrimers+count++) = trial;    // store it and increment count
    }

    // display primes 5-up
    for(int i=0; i<total; ++i)
    {
        printf("%12llu", *(pPrimers+i));
        if(!((i+1)%5))
            printf("\n");       // newline after every 5
    }
    printf("\n");               // newline for any stragglers

    free(pPrimers);             // release the heap memory...
    pPrimers = NULL;            // ...and reset the pointer
    return 0;
}