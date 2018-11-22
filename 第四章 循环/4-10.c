// Program 4.10 Sums of successive integer sequences
#include <stdio.h>

int main(void)
{
    unsigned long sum = 0UL;            // Stores the sum of integers
    unsigned int count = 0;             // Number of sums to be calculated

    // Prompt for, and read the iput count
    printf("\nEnter the number of integers you want to sum: ");
    scanf(" %u", &count);

    for (unsigned int i = 1; i <= count; ++i)
    {
        sum = 0UL;                      // Initialize sum for the inner loop

        // Calculate sum of integers from 1 to i
        for (unsigned int j = 1; j <= i; ++j)
            sum += j;
        printf("\n%u\t%5lu", i, sum);   // Output sum of 1 to i
    }
    printf("\n");
    return 0;
}