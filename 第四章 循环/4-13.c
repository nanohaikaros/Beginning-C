// Program 4.13 Simple Simon
#include <stdio.h>              // For input and output
#include <ctype.h>              // For toupper() function
#include <stdbool.h>            // For bool, true, false
#include <stdlib.h>             // For rand() and srand()
#include <time.h>               // For time() funcrion

int main(void)
{
    char another_game = 'Y';    // Records if another game is to be played
    const unsigned int DELAY = 1;   // Display period in seconds
    bool correct = true;            //  true for correct sequence, false otherwise
    unsigned int tries = 0;         // Number of successful entries for sequence length
    unsigned int digits = 0;        // Number of digits in a sequence
    time_t seed = 0;                // Seed value for random number sequence
    unsigned int number = 0;        // Stores an input digit
    time_t wait_start = 0;          // Stores current time

    /* More variable declarations for the program */

    // Describe how the game is played
    printf("\nTo play Simple Simon, ");
    printf("watch the secreen for a sequence of digits.");
    printf("\nWatch carefully, as the digits are only dispalyed for %u second%s ", DELAY, DELAY > 1 ? "s!" : "!");
    printf("\nThe computer will remove them, and then prompt you ");
    printf("to enter the same sequence.");
    printf("\nWhen you do, you must put spaces between the digits.\n");
    printf("\nGood Luck!\nPress Enter to play\n");
    scanf("%c", &another_game);

    // Game loop - one outer loop iteration is a complets game
    do 
    {
        // Initialize game
        correct = true;         // Indicates correct sequence entered
        tries = 0;              // Initialize count of successful tries
        digits = 2;             // Initial length of digit sequence
        // Other code to initialize the game
        // Inner loop continues as long as sequences are entered correctly
        while(correct)
        {
            ++tries;        //  A new attempt
            wait_start = clock();   // record start time for sequence

            // Generate a sequence of digits and display them
            srand(time(&seed)); // Initialize the random sequence
            for(unsigned int i = 1; i<=digits; ++i)
                printf("%d ", rand()%10);   // Output a random digit

            for( ; clock()-wait_start<DELAY*CLOCKS_PER_SEC ; ); // Wait DEALY seconds

            // Now overwrite the digit sequence
            printf("\r");           // Go to beginning of the line
            for (unsigned int i = 1; i <= digits; i++)
                printf(" ");        // Output two spaces

            if(tries == 1)          // Only output message for 1st try
                printf("\nNow you enter the sequence - don't forget the spaces\n");
            else
                printf("\r");       // Back to the beginning of the line

            srand(seed);        // Reinitialize the random sequence
            for(unsigned int i = 1; i<=digits; ++i)     
            // Read the input sequance & check against the original
            {
                scanf("%u", &number);       // Read a digit
                if(number != rand()%10)     // Compare with generated digit
                {
                    correct = false;        // incorrect entry
                    break;                  // No need to check fureher...
                }
            }
            // On every thied successful try, increase the sequence length
            if(correct && ((tries % 3) == 0))
                ++digits;
            printf("%s\n", correct ? "Correct!" : "Wrong!");
        }

        // Output the score when a game is finished

        // Check if a new game is required
        printf("\nDo you want to play again (y/n)? ");
        scanf("%c", &another_game);
    } while (toupper(another_game) == 'Y');

    return 0;
}