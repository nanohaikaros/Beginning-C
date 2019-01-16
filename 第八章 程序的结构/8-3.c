// Program 8.3 Calculating an average using functions
#include <stdio.h>
#define MAX_COUNT 50

double Sum(double x[], size_t n)
{
    double sum = 0.0;
    for(size_t i = 0; i < n; ++i)
        sum += x[i];

    return sum;
}

double Average(double x[], size_t n)
{
    return Sum(x, n)/n;
}

size_t GetData(double *data, size_t max_count)
{
    size_t nValues = 0;
    printf("How many values do you want to enter (Maximum %u)? ", max_count);
    scanf("%u", &nValues);
    if(nValues > max_count)
    {
        printf("Maximum count exceeded. %u items will be read.", max_count);
        nValues = max_count;
    }
    for(size_t i = 0; i < nValues; ++i)
        scanf("%lf", &data[i]);

    return nValues;
}

int main(void)
{
    double samples[MAX_COUNT] = {0.0};
    size_t sampleCount = GetData(samples, MAX_COUNT);
    double average = Average(samples, sampleCount);
    printf("The average of the values you entered is: %.2lf\n", average);

    return 0;
}