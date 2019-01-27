// Program 12.3 Messing about with formatted file I/O
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    long num1 = 234567L;
    long num2 = 345123L;
    long num3 = 789234L;

    long num4 = 0L;
    long num5 = 0L;
    long num6 = 0L;

    float fnum = 0.0f;
    int ival[6] = {0};
    FILE *pfile = NULL;
    char *filename = "myfile.txt";

    if(fopen_s(&pfile, filename, "w"))
    {
        printf_s("Error opening %s for writing. Program terminated.\n", filename);
        exit(1);
    }
    setbuf(pfile, NULL);

    fprintf_s(pfile, "%6ld%6ld%6ld", num1, num2, num3);
    fclose(pfile);
    printf_s(" %6ld %6ld %6ld\n", num1, num2, num3);

    if(fopen_s(&pfile, filename, "r"))
    {
        printf_s("Error opening %s for reading. Program terminated.\n", filename);
        exit(1);
    }
    setbuf(pfile, NULL);

    fscanf_s_l(pfile, "%6ld%6ld%6ld", &num4, &num5, &num6);
    printf_s(" %6ld %6ld %6ld\n", num4, num5, num6);

    rewind(pfile);
    fscanf_s_l(pfile, "%2d%3d%3d%3d%2d%2d%3f", &ival[0], &ival[1], &ival[2], &ival[3], &ival[4], &ival[5], &fnum);
    fclose(pfile);
    remove(filename);

    printf_s("\n");
    for(size_t i = 0; i < sizeof(ival)/sizeof(ival[0]); ++i)
        printf_s("%sival[%zd] = %d", i == 4 ? "\n\t" : "\t", i, ival[i]);
    printf_s("\nfnum = %f\n", fnum);
    return 0;
}