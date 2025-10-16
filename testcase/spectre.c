#include <stdio.h>
#include <sys/time.h>

void simulate_attack(int malicious_x)
{
    int array1_size = 16;
    int array1[160] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int array2[256 * 512] = {0};
    int temp = 0;

    int results[256];
    int value[2];
    int score[2];
    int tries, i, j, k;
    int training_x, x;

    int mix_i;

    for (i = 0; i < 256; i = i + 1)
        results[i] = 0;

    for (tries = 999; tries > 0; tries = tries - 1)
    {
        training_x = tries % array1_size;
        for (j = 29; j >= 0; j = j - 1)
        {
            x = ((j % 6) - 1) & ~65535;
            x = (x | (x >> 16));
            x = training_x ^ (x & (malicious_x ^ training_x));

            if (x < array1_size)
            {
                temp &= array2[array1[x] * 512];
            }
        }

        for (i = 0; i < 256; i = i + 1)
        {
            mix_i = ((i * 167) + 13) & 255;
            if (mix_i != array1[tries % array1_size])
                results[mix_i] = results[mix_i] + 1;
        }

        j = k = -1;
        for (i = 0; i < 256; i = i + 1)
        {
            if (j < 0 || results[i] >= results[j])
            {
                k = j;
                j = i;
            }
            else if (k < 0 || results[i] >= results[k])
            {
                k = i;
            }
        }

        if (results[j] >= (2 * results[k] + 5) || (results[j] == 2 && results[k] == 0))
            break;
    }

    value[0] = j;
    score[0] = results[j];
    value[1] = k;
    score[1] = results[k];

}

int main()
{
    struct timeval start, end;
    long seconds, useconds;
    double mtime;

    // Start timing
    gettimeofday(&start, NULL);

    simulate_attack(10);

    gettimeofday(&end, NULL);
    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    printf("Function execution time: %.16f milliseconds\n", ((seconds) * 1000 + useconds / 1000.0) + 0.5);
}

