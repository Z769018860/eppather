#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592653589793
#define SCALE_FACTOR 1000  // 用于将浮点数转化为整数以便进行精确计算

void fft(int real[], int imag[], int n) {
    int i, j, k, m;
    int len, half_len, w_real, w_imag, u_real, u_imag, t_real, t_imag;

    // 位反转置换
    j = 0;
    for (i = 1; i < n; ++i) {
        int bit = n >> 1;
        while (j >= bit) {
            j -= bit;
            bit >>= 1;
        }
        j += bit;

        if (i < j) {
            // 交换实部和虚部
            int temp_real = real[i];
            real[i] = real[j];
            real[j] = temp_real;

            int temp_imag = imag[i];
            imag[i] = imag[j];
            imag[j] = temp_imag;
        }
    }

    // 蝴蝶运算
    for (len = 2; len <= n; len <<= 1) {
        half_len = len >> 1;
        w_real = SCALE_FACTOR;
        w_imag = 0;
        int theta = SCALE_FACTOR * (int)(-2 * PI / len);

        int w_m_real = (int)(cos(2 * PI / len) * SCALE_FACTOR);
        int w_m_imag = (int)(-sin(2 * PI / len) * SCALE_FACTOR);

        for (m = 0; m < half_len; ++m) {
            for (i = m; i < n; i += len) {
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
}

int main() {
    // 输入信号的实部和虚部（虚部初始化为 0）
    int real[] = {1000, 2000, 3000, 4000, 0, 0, 0, 0};
    int imag[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int n = sizeof(real) / sizeof(real[0]);

    // 执行 FFT
    fft(real, imag, n);

    // 输出 FFT 结果
    printf("FFT Result:\n");
    for (int i = 0; i < n; ++i) {
        printf("Index %d: Real = %d, Imag = %d\n", i, real[i], imag[i]);
    }

    return 0;
}
