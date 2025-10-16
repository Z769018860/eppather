#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define MAXSIZE 500000

// FFT 函数：对长度为 n 的数据进行离散傅里叶变换（整数实现，使用缩放因子）
void fft(int real[MAXSIZE], int imag[MAXSIZE], int n) {
clock_t start, end;
start = clock();
    int i, j, k, m;
    int len, half_len, w_real, w_imag, u_real, u_imag, t_real, t_imag;
    int SCALE_FACTOR = 1000;
    int PI = 314159265;  

    j = 0;
    for (i = 1; i < n; i = i + 1) {
        int bit = n >> 1;
        while (j >= bit) {
            j = j - bit;
            bit = bit >> 1;
        }
        j = j + bit;

        if (i < j) {
            int temp_real = real[i];
            real[i] = real[j];
            real[j] = temp_real;

            int temp_imag = imag[i];
            imag[i] = imag[j];
            imag[j] = temp_imag;
        }
    }

    for (len = 2; len <= n; len = len << 1) {
        half_len = len >> 1;
        w_real = SCALE_FACTOR;
        w_imag = 0;
        int theta = SCALE_FACTOR * (int)(-2 * PI / len); 

        int w_m_real = (int)(cos(2 * PI / len) * SCALE_FACTOR);
        int w_m_imag = (int)(-sin(2 * PI / len) * SCALE_FACTOR);

        for (m = 0; m < half_len; m = m + 1) {
            for (i = m; i < n; i = i + len) {
                j = i + half_len;

                t_real = (w_real * real[j] - w_imag * imag[j]) / SCALE_FACTOR;
                t_imag = (w_real * imag[j] + w_imag * real[j]) / SCALE_FACTOR;

                u_real = real[i];
                u_imag = imag[i];

                real[i] = u_real + t_real;
                imag[i] = u_imag + t_imag;

                real[j] = u_real - t_real;
                imag[j] = u_imag - t_imag;
            }

            int temp_w_real = (w_real * w_m_real - w_imag * w_m_imag) / SCALE_FACTOR;
            int temp_w_imag = (w_real * w_m_imag + w_imag * w_m_real) / SCALE_FACTOR;

            w_real = temp_w_real;
            w_imag = temp_w_imag;
        }
    }
    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_taken);
    return;
}

int main() {
    int n;
    int real[MAXSIZE] = {0};
    int imag[MAXSIZE] = {0};
    scanf("%d", &n);
    if(n <= 0 || n > MAXSIZE) {
        printf("输入的点数不合法！\n");
        return 1;
    }
    // 这里简单检测 n 是否为 2 的幂
    int temp = n;
    while(temp % 2 == 0 && temp > 1)
        temp = temp / 2;
    if(temp != 1) {
        printf("n 必须是2的幂！\n");
        return 1;
    }

    // 根据 n 生成固定的输入数据
    // 这里构造一个周期信号：实部为 1000*cos(2πi/n)，虚部为 1000*sin(2πi/n)
    for (int i = 0; i < n; i = i + 1) {
        real[i] = (int)(1000 * cos(2 * M_PI * i / n));
        imag[i] = (int)(1000 * sin(2 * M_PI * i / n));
    }

    // 输出输入数据
    printf("\nFFT 输入数据：\n");
    for (int i = 0; i < n; i = i + 1) {
        printf("Index %d: Real = %d, Imag = %d\n", i, real[i], imag[i]);
    }
    // 调用 FFT 函数
    fft(real, imag, n);

    // 打印 FFT 结果
    printf("\nFFT输出结果：\n");
    for (int i = 0; i < n; i = i + 1) {
        printf("Index %d: Real = %d, Imag = %d\n", i, real[i], imag[i]);
    }

    return 0;
}
