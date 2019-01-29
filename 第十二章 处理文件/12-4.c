// Program 12.4 A prime example using binary files
#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define PER_LINE 8
#define MEM_PRIMES 10*PER_LINE

bool is_prime(unsigned long long N);
void list_primes(void);
int check(unsigned long long buffer[], size_t count, unsigned long long N);
void list_array(void);
void write_file(void);

struct
{
    char *filename;
    FILE *pfile;
    unsigned long long primes[MEM_PRIMES];
    size_t count;
} global = {.filename = "myfile.bin",
            .pfile = NULL,
            .primes = {2ULL, 3ULL, 5ULL},
            .count = 3
};

int main(void)
{
    unsigned long long trial = global.primes[global.count - 1];
    size_t num_primes = 3UL;
    size_t total = 0UL;

    printf_s("How many primes would you like?");
    scanf_s("%zd", &total);

    while(num_primes < total)
    {
        trial += 2ULL;
        if(is_prime(trial))
        {
            global.primes[global.count++] = trial;
            ++num_primes;
            if(global.count == MEM_PRIMES)
                write_file();
        }
    }

    if(global.pfile && global.count > 0)
        write_file();

    list_primes();
    if(global.pfile)
    {
        if(remove(global.filename))
            printf_s("\nFailed to delete %s\n", global.filename);
        else 
            printf_s("\nFile %s deleted.\n", global.filename);
    }
    return 0;
}

bool is_prime(unsigned long long n)
{
    unsigned long long buffer[MEM_PRIMES];
    size_t count = 0;
    int k = 0;

    if(global.pfile)
    {
        if(fopen_s(&global.pfile, global.filename, "rb"))
        {
            printf_s("Unable to open %s to read.\n", global.filename);
            exit(1);
        }
        setvbuf(global.pfile, NULL, _IOFBF, BUFSIZ);
        while(!feof(global.pfile))
        {
            count = fread(buffer, sizeof(buffer[0]), MEM_PRIMES, global.pfile);
            if(k = check(buffer, count, n) == 1)
            {
                fclose(global.pfile);
                return true;
            }
        }
        fclose(global.pfile);
    }
    return 1 == check(global.primes, global.count, n);
}

int check(unsigned long long buffer[], size_t count, unsigned long long n)
{
    unsigned long long root_N = (unsigned long long)(1.0 + sqrt(n));

    for(size_t i = 0; i < count; ++i)
    {
        if(n % buffer[i] == 0ULL)
            return 0;
        
        if(buffer[i] > root_N)
            return 1;
    }
    return -1;
}

void write_file(void)
{
    if(fopen_s(&global.pfile, global.filename, "ab"))
    {
        printf_s("Unable to open %s to append\n", global.filename);
        exit(1);
    }
    setvbuf(global.pfile, NULL, _IOFBF, BUFSIZ);
    fwrite(global.primes, sizeof(unsigned long long), global.count, global.pfile);
    fclose(global.pfile);
    global.count = 0;
}

void list_primes(void)
{
    if(global.pfile)
    {
        if(fopen_s(&global.pfile, global.filename, "rb"))
        {
            printf_s("\nUnable to open %s to read primes for output\n", global.filename);
            exit(1);
        }
        setvbuf(global.pfile, NULL, _IOFBF, BUFSIZ);
        while(!feof(global.pfile))
        {
            global.count = fread(global.primes, sizeof(unsigned long long), MEM_PRIMES, global.pfile);
            list_array();
        }
        printf_s("\n");
        fclose(global.pfile);
    }
    else
        list_array();    
}

void list_array(void)
{
    for(size_t j = 0; j < global.count; ++j)
    {
        printf_s("%10llu", global.primes[j]);
        if(((j + 1) % PER_LINE) == 0)
            printf_s("\n");
    }
}