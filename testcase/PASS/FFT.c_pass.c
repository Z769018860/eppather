#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define MAXSIZE 500000

// FFT 函数：对长度为 n 的数据进行离散傅里叶变换（整数实现，使用缩放因子）
void fft(int real[MAXSIZE], int imag[MAXSIZE], int n) {
int path_len = 0;
int mems = 0;
int cond_count = 0;
clock_t start, end;
start = clock();
printf("Path: \n");
printf("int real[MAXSIZE];\n");
printf("int imag[MAXSIZE];\n");
printf("int n;\n");
printf("int i;\n");
printf("int j;\n");
printf("int k;\n");
printf("int m;\n");
printf("int len;\n");
printf("int half_len;\n");
printf("int w_real;\n");
printf("int w_imag;\n");
printf("int u_real;\n");
printf("int u_imag;\n");
printf("int t_real;\n");
printf("int t_imag;\n");
printf("int SCALE_FACTOR;\n");
printf("int PI;\n");


    int i, j, k, m;
    int len, half_len, w_real, w_imag, u_real, u_imag, t_real, t_imag;
    int SCALE_FACTOR = 1000;
    int PI = 314159265;  

    printf("j = 0;\n");
    j = 0;
    
    {
      int __first_iter_flag_160 = 1;
    for (i = 1; i < n; i = i + 1) {
    if(__first_iter_flag_160) { 
    printf("i = 1;\n"); 
    __first_iter_flag_160 = 0; 
    }
    cond_count = cond_count + 1;
    printf("@(i < n)\n");
    path_len = path_len + 1;
    
        int bit = n >> 1;
        while (j >= bit) {
        cond_count = cond_count + 1;
        printf("@(j >= bit)\n");
        path_len = path_len + 1;
        
            printf("j = j - bit;\n");
            j = j - bit;
            
            printf("bit = bit >> 1;\n");
            bit = bit >> 1;
            
        }
        printf("j = j + bit;\n");
        j = j + bit;
        

        if (i < j) {
        cond_count = cond_count + 1;
        printf("@(i < j)\n");
        path_len = path_len + 1;
        
            int temp_real = real[i];
            printf("real[i] = real[j];\n");
            real[i] = real[j];
            mems = mems + 2;
            
            printf("real[j] = temp_real;\n");
            real[j] = temp_real;
            mems = mems + 1;
            

            int temp_imag = imag[i];
            printf("imag[i] = imag[j];\n");
            imag[i] = imag[j];
            mems = mems + 2;
            
            printf("imag[j] = temp_imag;\n");
            imag[j] = temp_imag;
            mems = mems + 1;
            
        }
    printf("i = i + 1;\n");
}
}


    {
      int __first_iter_flag_161 = 1;
    for (len = 2; len <= n; len = len << 1) {
    if(__first_iter_flag_161) { 
    printf("len = 2;\n"); 
    __first_iter_flag_161 = 0; 
    }
    cond_count = cond_count + 1;
    printf("@(len <= n)\n");
    path_len = path_len + 1;
    
        printf("half_len = len >> 1;\n");
        half_len = len >> 1;
        
        printf("w_real = SCALE_FACTOR;\n");
        w_real = SCALE_FACTOR;
        
        printf("w_imag = 0;\n");
        w_imag = 0;
        
        int theta = SCALE_FACTOR * (int)(-2 * PI / len); 

        int w_m_real = (int)(cos(2 * PI / len) * SCALE_FACTOR);
        int w_m_imag = (int)(-sin(2 * PI / len) * SCALE_FACTOR);

        {
          int __first_iter_flag_162 = 1;
        for (m = 0; m < half_len; m = m + 1) {
        if(__first_iter_flag_162) { 
        printf("m = 0;\n"); 
        __first_iter_flag_162 = 0; 
        }
        cond_count = cond_count + 1;
        printf("@(m < half_len)\n");
        path_len = path_len + 1;
        
            {
              int __first_iter_flag_163 = 1;
            for (i = m; i < n; i = i + len) {
            if(__first_iter_flag_163) { 
            printf("i = m;\n"); 
            __first_iter_flag_163 = 0; 
            }
            cond_count = cond_count + 1;
            printf("@(i < n)\n");
            path_len = path_len + 1;
            
                printf("j = i + half_len;\n");
                j = i + half_len;
                

                printf("t_real = (w_real * real[j] - w_imag * imag[j]) / SCALE_FACTOR;\n");
                t_real = (w_real * real[j] - w_imag * imag[j]) / SCALE_FACTOR;
                mems = mems + 2;
                
                printf("t_imag = (w_real * imag[j] + w_imag * real[j]) / SCALE_FACTOR;\n");
                t_imag = (w_real * imag[j] + w_imag * real[j]) / SCALE_FACTOR;
                mems = mems + 2;
                

                printf("u_real = real[i];\n");
                u_real = real[i];
                mems = mems + 1;
                
                printf("u_imag = imag[i];\n");
                u_imag = imag[i];
                mems = mems + 1;
                

                printf("real[i] = u_real + t_real;\n");
                real[i] = u_real + t_real;
                mems = mems + 1;
                
                printf("imag[i] = u_imag + t_imag;\n");
                imag[i] = u_imag + t_imag;
                mems = mems + 1;
                

                printf("real[j] = u_real - t_real;\n");
                real[j] = u_real - t_real;
                mems = mems + 1;
                
                printf("imag[j] = u_imag - t_imag;\n");
                imag[j] = u_imag - t_imag;
                mems = mems + 1;
                
            printf("i = i + len;\n");
}
}


            int temp_w_real = (w_real * w_m_real - w_imag * w_m_imag) / SCALE_FACTOR;
            int temp_w_imag = (w_real * w_m_imag + w_imag * w_m_real) / SCALE_FACTOR;

            printf("w_real = temp_w_real;\n");
            w_real = temp_w_real;
            
            printf("w_imag = temp_w_imag;\n");
            w_imag = temp_w_imag;
            
        printf("m = m + 1;\n");
}
}

    printf("len = len << 1;\n");
}
}

    printf("end = clock();\n");
    end = clock();
    
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_taken);
    printf("\nEND\nTotal path length: %d\n", path_len);
    printf("Total memory accesses: %d\n", mems);
    printf("Total conditional statements: %d\n", cond_count);
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
