#include <stdio.h>
#include <time.h>

const char *thread_state_to_string(int thread_state, char *buf, int buf_size,
                                   int *pathlength, int *mems) {
    int repeat_inner = 10000000;  // 🔸 内部重复执行次数，放大函数时间
    for (int r = 0; r < repeat_inner; r = r + 1) {

        *pathlength = *pathlength + 1;
        int off = 0;
        *pathlength = *pathlength + 1;

        int bit_array[8] = {1,2,4,8,16,32,64,128};
        int len_array[8] = {1,1,1,1,1,1,1,1};
        char str_array[8] = {'A','B','C','D','E','F','G','H'};

        *pathlength = *pathlength + 1;
        if (buf == 0 || buf_size == 0) return "";

        *pathlength = *pathlength + 1;
        int bsize = buf_size - 1;

        int index = 0;
        *pathlength = *pathlength + 1;
        int state = thread_state;
        while (state != 0) {
            *pathlength = *pathlength + 1;
            int bit = bit_array[index];
            *mems = *mems + 1;

            *pathlength = *pathlength + 1;
            if ((state & bit) == 0) {
                index = index + 1;
                *pathlength = *pathlength + 1;
                continue;
            }

            buf[off] = str_array[index];
            *mems = *mems + 2;
            off = off + len_array[index];
            *mems = *mems + 1;
            *pathlength = *pathlength + 3;

            state = state & (~bit);
            *pathlength = *pathlength + 1;

            *pathlength = *pathlength + 1;
            if (state != 0) {
                buf[off] = '+';
                *mems = *mems + 1;
                off = off + 1;
                *pathlength = *pathlength + 2;
            }

            index = index + 1;
            *pathlength = *pathlength + 1;
        }

        buf[off] = '\0';
        *mems = *mems + 1;
        *pathlength = *pathlength + 1;
    }

    return buf;
}

int main() {
    int inputs[] = {1, 2, 4, 8, 16, 32, 64, 128, 255, 254, 253, 252, 251, 250, 249, 248};
    int n = sizeof(inputs) / sizeof(inputs[0]);
    char buffer[64];

    for (int i = 0; i < n; i = i + 1) {
        int pathlength = 0;
        int mems = 0;
        clock_t start = clock();

        const char *result = thread_state_to_string(inputs[i], buffer, 64,
                                                    &pathlength, &mems);

        clock_t end = clock();
        double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

        printf("Input=%d | Result=%s | Path=%d | MEMS=%d | Time=%f s\n",
               inputs[i], result, pathlength, mems, elapsed_time);
    }

    return 0;
}
