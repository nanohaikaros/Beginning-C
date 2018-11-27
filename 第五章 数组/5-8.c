// Program 5.8 tic-Tac-Toe
#include <stdio.h>

int main(void)
{
    int player = 0;         // Current player number -1 or 2
    int winner = 0;         // The winning player number
    int choice = 0;         // Chosen square
    unsigned int row = 0;   // Row index for a square
    unsigned int column = 0;// Column index for a square

    char board[3][3] = {    // The board
        {'1', '2', '3'},    // Initial values are characters '1' to '9'
        {'4', '5', '6'},    // used to select a vacant square
        {'7', '8', '9'}     // for a player's turn
    };

    // The main game loop. The game continues for up to 9 tuens
    // as long as there is no winner
    for(unsigned int i = 0; i < 9 && winner == 0; ++i)
    {
        // Display the board
        printf("\n");
        printf(" %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
        printf("---+---+---\n");
        printf(" %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
        printf("---+---+---\n");
        printf(" %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
        
        player = i%2 + 1;       // Select player

        // Get valid player square swlwction
        do 
        {
            printf("Player %d, please enter a valid square number "
                    "for where you want to place your %c: ",
                    player, (player == 1) ? 'X' : 'O');
            scanf("%d", &choice);

            row = --choice/3;           // Get row index of square
            column = choice % 3;        // Get column index of square
        } while(choice < 0 || choice > 8 || board[row][column] > '9');

        // Insert player symbol
        board[row][column] = (player == 1) ? 'X' : 'O';

        /* code to check for a winner */
    }
    /* code to output the result */

    return 0;
}