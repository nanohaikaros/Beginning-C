// Program 9.9 REVERSI An Othello type hame
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#define SIZE 6

const char comp_c = '@';
const char player_c = 'O';

void display(char board[][SIZE]);
void reset_board(char board[][SIZE]);
int valid_moves(char board[][SIZE], bool moves[][SIZE],  char player);
int player_counters(char board[][SIZE], char player);
void make_move(char board[][SIZE], size_t row, size_t col, char player);
void computer_move(char board[][SIZE], bool moves[][SIZE], char player);
int best_move(char board[][SIZE], bool moves[][SIZE], char player);
int get_score(char board[][SIZE], char player);

int main(void)
{
    char board[SIZE][SIZE] = {0};
    bool moves[SIZE][SIZE] = { false };
    int no_of_moves = 0;
    int invalid_moves = 0;
    char again = 0;
    char y = 0;
    size_t x = 0;

    bool next_player = true;

    printf("\nREVERSI\n\n");
    printf("You can go first on the first game, then we will take turns.\n");
    printf(" You will be shite - (%c)\n I will be black - (%c).\n", player_c, comp_c);
    printf("Select a square for your move by typing a digit for the row\n "
            "and a letter for the column with no spaces between.\n");
    printf("\nGood luck! Press Enter to start.\n");
    sscanf("%c", &again, sizeof(again));
    fflush(stdin);

    do{
        reset_board(board);

        next_player = !next_player;
        no_of_moves = 4;

        do
        {
            display(board);
            if(true == (next_player = !next_player))
            {
                if(valid_moves(board, moves, player_c))
                {
                    for(;;)
                    {
                        printf("Please enter your move (row column - no space): ");
                        scanf(" %d%c", &x, &y, sizeof(y));
                        fflush(stdin);

                        y = tolower(y) - 'a';
                        --x;
                        if(y < 0 || y >= SIZE || x >= SIZE || !moves[x][y])
                        {
                            printf("Not a valid move, try again.\n");
                            continue;
                        }

                        make_move(board, x, y, player_c);
                        ++no_of_moves;
                        break;
                    }
                }
                else
                {
                    if(++invalid_moves < 2)
                    {
                        printf("\nyou have to pass, press return");
                        sscanf("%c", &again, sizeof(again));
                        fflush(stdin);
                    }
                    else
                        printf("\nNeither of us can go, so the game is over.\n");   
                }
            }
            else
            {
                if(valid_moves(board, moves, comp_c))
                {
                    invalid_moves = 0;
                    computer_move(board, moves, comp_c);
                    ++no_of_moves;
                }
                else
                {
                    if(++invalid_moves < 2)
                        printf("\nI have to pass, your go\n");
                    else
                        printf("\nNeither of us can go, so the game is over.\n");
                }
            }
        } while(no_of_moves < SIZE*SIZE && invalid_moves < 2);

        display(board);
        printf("The final score is:\n");

        printf("Computer %d\n User %d\n\n", player_counters(board, comp_c), player_counters(board, player_c));
        printf("Do you want to play again (y/n): ");
        sscanf(" %c", &again, sizeof(again));
        fflush(stdin);
    } while(tolower(again) == 'y');

    printf("\nGoodbye!\n");
    

    return 0;
}

void reset_board(char board[][SIZE])
{
    for(size_t row = 0; row < SIZE; ++row)
        for(size_t col = 0; col < SIZE; ++col)
            board[row][col] = ' ';

    size_t mid = SIZE/2;
    board[mid - 1][mid - 1] = board[mid][mid] = player_c;
    board[mid - 1][mid] = board[mid][mid - 1] = comp_c;
}

void display(char board[][SIZE])
{
    char col_lable = 'a';
    printf("\n ");
    for(size_t col = 0; col < SIZE; ++col)
        printf(" %c", (char)(col_lable + col));
    printf("\n");

    for(size_t row = 0; row < SIZE; ++row)
    {
        printf(" +");
        for(size_t col = 0; col < SIZE; ++col)
            printf("---+");
        printf("\n%2zd|", row + 1);
        for(size_t col = 0; col < SIZE; ++col)
            printf(" %c |", board[row][col]);
        printf("\n");
    }

    printf(" +");
    for(size_t col = 0; col < SIZE; ++col)
        printf("---+");
    printf("\n");
}

int valid_moves(char board[][SIZE], bool moves[][SIZE], char player)
{
    int rowdelta = 0;
    int coldelta = 0;
    int x = 0;
    int y = 0;
    int no_of_moves = 0;

    char opponent = (player == player_c) ? comp_c : player_c;

    for(size_t row = 0; row < SIZE; ++row)
        for(size_t col = 0; col < SIZE; ++row)
            moves[row][col] = false;

    for(size_t row = 0; row < SIZE; ++row)
    {
        for(size_t col = 0; col < SIZE; ++col)
        {
            if(board[row][col] != ' ')
                continue;

            for(rowdelta = -1; rowdelta <= 1; ++rowdelta)
            {
                for(coldelta = -1; coldelta <= 1; ++coldelta)
                {
                    if((row == 0 && rowdelta == -1) || row + rowdelta >= SIZE || (col == 0 && coldelta == -1) || col + coldelta >= SIZE || (rowdelta == 0 && coldelta == 0))
                        continue;
                    
                    if(board[row + rowdelta][col + coldelta] == opponent)
                    {
                        x = row + rowdelta;
                        y = col + coldelta;
                        for(;;)
                        {
                            x += rowdelta;
                            y += coldelta;

                            if(x < 0 || x >= SIZE || y < 0 || y >= SIZE || board[x][y] == ' ')
                                break;

                            if(board[x][y] == player)
                            {
                                moves[row][col] = true;
                                no_of_moves++;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    return no_of_moves;
}

int player_counters(char board[][SIZE], char player)
{
    int count = 0;
    for(size_t row = 0; row < SIZE; ++row)
        for(size_t col = 0; col < SIZE; ++col)
            if(board[row][col] == player)
                ++count;

    return count;
}

void make_move(char board[][SIZE], size_t row, size_t col, char player)
{
    int rowdelta = 0;
    int coldelta = 0;
    size_t x = 0;
    size_t y = 0;

    char opponent = (player == player_c) ? comp_c : player_c;

    board[row][col] = player;

    for(rowdelta = -1; rowdelta <= 1; ++rowdelta)
    {
        for(coldelta = -1; coldelta <= 1; ++coldelta)
        {
            if((row == 0 && rowdelta == -1) || row + rowdelta >= SIZE || (col == 0 && coldelta == -1) || col + coldelta >= SIZE || (rowdelta == 0 && coldelta == 0))
                continue;
            if(board[row + rowdelta][col + coldelta] == opponent)
            {
                x = row + rowdelta;
                y = col + coldelta;

                for(;;)
                {
                    x += rowdelta;
                    y += coldelta;
                    if(x >= SIZE || y >= SIZE || board[x][y] == ' ')
                        break;
                    if(board[x][y] == player)
                    {
                        while(board[x -= rowdelta][ y -= coldelta] == opponent)
                            board[x][y] = player;
                        break;
                    }
                }
            }
        }
    }
}

int get_score(char board[][SIZE], char player)
{
    return player_counters(board, player) - player_counters(board, (player == player_c) ? comp_c : player_c);
}

int best_move(char board[][SIZE], bool moves[][SIZE], char player)
{
    char new_board[SIZE][SIZE] = {0};
    int score = 0;
    int new_score = 0;

    for(size_t row = 0; row < SIZE; ++row)
    {
        for(size_t col = 0; col < SIZE; ++col)
        {
            if(!moves[row][col])
                continue;

            memcpy(new_board, board, sizeof(new_board));
            make_move(new_board, row, col, player);
            new_score = get_score(new_board, player);

            if(score < new_score)
                score = new_score;
        }
    }
    return score;
}

void computer_move(char board[][SIZE], bool moves[][SIZE], char player)
{
    size_t best_row = 0;
    size_t best_col = 0;
    int new_score = 0;
    int score = SIZE*SIZE;
    char temp_board[SIZE][SIZE];
    bool temp_moves[SIZE][SIZE];

    char opponent = (player == player_c) ? comp_c : player_c;

    for(size_t row = 0; row < SIZE; ++row)
    {
        for(size_t col = 0; col < SIZE; ++col)
        {
            if(!moves[row][col])
                continue;

            memcpy_s(temp_board, SIZE*SIZE, board, SIZE*SIZE);

            make_move(temp_board, row, col, player);

            valid_moves(temp_board, temp_moves, opponent);

            new_score = best_move(temp_board, temp_moves, opponent);

            if(new_score < score)
            {
                score = new_score;
                best_row = row;
                best_col = col;
            }
        }
    }
    make_move(board, best_row, best_col, player);
}