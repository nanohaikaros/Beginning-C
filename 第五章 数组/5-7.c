//  Program 5.7 Averaging a variable number of grades
#include <stdio.h>

int main(void)
{
    size_t nGrades = 0;         // Number of grades
    printf("Enter the number of grades: ");
    scanf("%d", &nGrades);
    int grades[nGrades];        // Array storing nGrades values
    long sum = 0L;              // Sum of the numbers
    float average = 0.0f;       // Average of the numbers
    printf("\nEnter the %d grades:\n", nGrades);   // prompt for the input

    // Read the ten numbers to be averaged
    for(size_t i = 0; i < nGrades; ++i)
    {
        printf("%2d> ", i+1);
        scanf("%d", &grades[i]);    // Read a grade
        sum += grades[i];           // Add it to sum
    }
    printf("The grades you entered are:\n");
    for(size_t i = 0; i < nGrades; ++i)
    {
        printf("Grade[%2d] == %3d ", i+1, grades[i]);

        if((i+1) % 5 == 0)          // After 5 values
            printf("\n");           // Go to a new line
    }

    average = (float)sum/nGrades;   // Calculate the average

    printf("\nAverage of the %d grades entered is: %.2f\n", nGrades, average);
}