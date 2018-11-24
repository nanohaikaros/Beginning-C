// Program 4.13 Simple Simon
#include <stdio.h>              // For input and output
#include <ctype.h>              // For toupper() function
#include <stdbool.h>            // For bool, true, false

int main(void)
{
    char another_game = 'Y';    // Records if another game is to be played
    const unsigned int DELAY = 1;   // Display period in seconds
    bool correct = true;            //  true for correct sequence, false otherwise

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
        correct = true;         // Indicates correct sequence entered
        // Other code to initialize the game
        // Inner loop continues as long as sequences are entered correctly
        while(correct)
        {
            // Statements to play the game
        }

        // Output the score when a game is finished

        // Check if a new game is required
        printf("\nDo you want to play again (y/n)? ");
        scanf("%c", &another_game);
    } while (toupper(another_game) == 'Y');

    return 0;
}