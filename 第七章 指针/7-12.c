// Program 7.12 Extending dynamically allocated memory
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define CAP_INCR 10         // new memory increment

int main(void)
{
    unsigned long long *pPrimes = NULL;     // pointer to primes storage area
    bool found = false;                     // indicates when we find a prime
    unsigned long long limit = 0LL;         // upper limit for primes
    int count = 0;                          // number of primes found

    printf("Enter the upper limit for primes you want to find: ");
    scanf("%llu", &limit);

    // allocate some initial memory to store primes
    size_t capacity = 10;
    pPrimes = calloc(capacity, sizeof(unsigned long long));
    if(!pPrimes)
    {
        printf("Not enough memory. It's the end I'm afraid.\n");
        return 1;
    }

    // we know the first three primes so let's give the program a start
    *pPrimes = 2ULL;            // first prime
    *(pPrimes+1) = 3ULL;        // second prime
    *(pPrimes+2) = 5ULL;        // third prime
    count = 3;                  // number of primes stored

    // find all the primes required starting with the next candidate
    unsigned long long trial = *(pPrimes+2)+2ULL;
    unsigned long long *pTemp = NULL;   // temporary pointer store
    while(trial<=limit)
    {
        // divide by the primes we have. if any divide exactly - it's not prime
        for(int i=1; i<count; ++i)
        {   
            if(!(found=(trial%*(pPrimes+i))))
            break;      // exit if zero remainder
        }

        if(found)
        {
            if(count == capacity)
            {// we need more memory
                capacity += CAP_INCR;
                pTemp = realloc(pPrimes, capacity*sizeof(unsigned long long));
                if(!pTemp)
                {
                    printf("Unfortunately memory reallocation failed.\n");
                    free(pPrimes);
                    pPrimes = NULL;
                    return 2;
                }
                pPrimes = pTemp;
            }
            *(pPrimes+count++) = trial;     // store the new prime & increment count
        }
        trial += 2ULL;
    }

    // display primes 5-up
    printf("%d primes found up to %llu:\n", count, limit);
    for(int i=0; i<count; ++i)
    {
        printf("%12llu", *(pPrimes+i));
        if(!((i+1)%5))
            printf("\n");       // newline after every 5
    }
    printf("\n");               // newline the heap memory
    free(pPrimes);              // release the heap memory...
    pPrimes = NULL;             // ...and reset the pointer
    return 0;
}