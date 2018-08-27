// Program 2.7 Division with float values
#include <stdio.h>

int main(void)
{
    float plank_length = 10.0f;     // In feet
    float piece_clunt = 4.0f;       // Number of equal pieces
    float piece_length = 0.0f;      // Length of a piecr in feet

    piece_length = plank_length/piece_clunt;
    printf("A plank %.2f feet long can be cut into %.0f pieces %.2f feet long.\n", plank_length, piece_clunt, piece_length);

    return 0;
}