// Program 10.2 Characters in the format control string
#include <stdio.h>

int main(void)
{
    int i = 0;
    int j = 0;
    int value_count = 0;
    float fp1 = 0.0f;
    printf("Enter: fp1 = 3.14159 i = 7 8\n");

    printf("\nInput:");
    value_count = scanf_s("fp1 = 5f i = %d %d", &fp1, &i, &j);
    printf("\nOutput:\n");
    printf("Count of values read = %d\n", value_count);
    printf("fp1 = %f\ti = %d\tj = %d\n", fp1, i ,j);
    return 0;
}