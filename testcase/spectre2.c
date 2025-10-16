#include <stdio.h>
#include <sys/time.h>

#include <stdio.h>

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
    freopen("longpath.txt", "w", stdout);  // 重定向 stdout 到文件
    printf("int malicious_x;\nint array1_size = 16;\nint array1[160] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};\nint array2[256 * 512] = {0};\nint temp = 0;\nint results[256];\nint value[2];\nint score[2];\nint tries, i, j, k;\nint training_x, x;\nint mix_i;\n");

    for (i = 0; i < 256; i = i + 1)
    {
        if (i==0)
            printf("@(i<256);\n@(i==0);\n");
        else
            printf("@(i<256);\n@(!(i==0));\n");
        results[i] = 0;
        printf("results[i] = 0;\n");
        printf("i=i+1;\n");
    }

        printf("tries=100;\n");
    for (tries = 10; tries > 0; tries = tries - 1)
    {
        if (tries==10)
            printf("@(tries > 0);\n@(tries=999);\n");
        else
            printf("@(tries > 0);\n@(!(tries=999));\n");
        training_x = tries % array1_size;
        printf("training_x = tries %% array1_size;\n");

        for (j = 29; j >= 0; j = j - 1)
        {
            x = ((j % 6) - 1) & ~65535;
            x = (x | (x >> 16));
            x = training_x ^ (x & (malicious_x ^ training_x));
            printf("x = ((j %% 6) - 1) & ~65535;\n");
            printf("x = (x | (x >> 16));\n");
            printf("x = training_x ^ (x & (malicious_x ^ training_x));\n");
            if (x < array1_size)
            {
                temp &= array2[array1[x] * 512];
                printf("@(x < array1_size);\n");
            }
            else
            {
                printf("@!(x < array1_size);\n");
            }

        }
        printf("@!(j >= 0);\n");
        printf("i = 0;\n");
        for (i = 0; i < 256; i = i + 1)
        {
            printf("@(i < 256);\n");
            mix_i = ((i * 167) + 13) & 255;
            printf("mix_i = ((i * 167) + 13) & 255;\n");
            if (mix_i != array1[tries % array1_size])
            {
                printf("@(mix_i != array1[tries %% array1_size]);\n");
                results[mix_i] = results[mix_i] + 1;
                printf("results[mix_i] = results[mix_i] + 1;\n");
            }
            else
            {
                printf("@!(mix_i != array1[tries %% array1_size]);\n");
            }
            printf("i = i + 1;\n");
        }
        printf("@!(i < 256);\n");

        j = k = -1;
        printf("j = k = -1;\n");
        printf("i = 0;\n");
        for (i = 0; i < 256; i = i + 1)
        {
            printf("@(i < 256);\n");
            if (j < 0 || results[i] >= results[j])
            {
                printf("@(j < 0 || results[i] >= results[j]);\n");
                k = j;
                j = i;
                printf("k = i;\n");
                printf("j = i;\n");
            }
            else if (k < 0 || results[i] >= results[k])
            {
                k = i;
                printf("@!(j < 0 || results[i] >= results[j]);\n@(k < 0 || results[i] >= results[k]);\n");
                printf("k = i;\n");
            }
            else
            {
                printf("@!(j < 0 || results[i] >= results[j]);\n@!(k < 0 || results[i] >= results[k]);\n");
            }
            printf("i = i + 1;\n");
        }
        printf("@!(i < 256);\n");

        if (results[j] >= (2 * results[k] + 5) || (results[j] == 2 && results[k] == 0))
        {
            printf("@(results[j] >= (2 * results[k] + 5) || (results[j] == 2 && results[k] == 0));\n");
            break;
        }
        else
        {
            printf("@!(results[j] >= (2 * results[k] + 5) || (results[j] == 2 && results[k] == 0));\n");
        }
        printf("tries=tries-1;\n");
    }
    printf("@!(tries > 0);\n");

    value[0] = j;
    score[0] = results[j];
    value[1] = k;
    score[1] = results[k];
    printf("value[0] = j; \nscore[0] = results[j]; \nvalue[1] = k; \nscore[1] = results[k];\n");
    fclose(stdout);  // 关闭文件输出流
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

