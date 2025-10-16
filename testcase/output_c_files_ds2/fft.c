void fft_dft_cooley_tukey_bit_reverse_iterative_approx(int n, int x_real[5], int x_imag[5], int y_real[5], int y_imag[5], int z_real[5], int z_imag[5]) {
    int tmp_real[5];
    int tmp_imag[5];
    int i;
    int j;
    int k;
    int stride;
    int count;
    int a;
    int n1;
    int v_real;
    int v_imag;
    int w_real;
    int w_imag;
    int t_real;
    int t_imag;
    
    for (i = 0; i < 5; i = i + 1) {
        tmp_real[i] = 0;
        tmp_imag[i] = 0;
        for (j = 0; j < 5; j = j + 1) {
            t_real = x_real[j];
            t_imag = x_imag[j];
            tmp_real[i] = tmp_real[i] + t_real;
            tmp_imag[i] = tmp_imag[i] + t_imag;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        x_real[i] = tmp_real[i];
        x_imag[i] = tmp_imag[i];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        n1 = i;
        a = i;
        count = 2;
        
        n1 = n1 / 2;
        while (n1 > 0) {
            a = (a * 2) | (n1 & 1);
            count = count - 1;
            n1 = n1 / 2;
        }
        n1 = (a * count) & 3;
        
        if (n1 > i) {
            t_real = x_real[i];
            t_imag = x_imag[i];
            x_real[i] = x_real[n1];
            x_imag[i] = x_imag[n1];
            x_real[n1] = t_real;
            x_imag[n1] = t_imag;
        }
    }
    
    for (i = 1; i <= 2; i = i + 1) {
        stride = 4;
        w_real = 1;
        w_imag = 0;
        for (j = 0; j < 5; j = j + stride) {
            v_real = 1;
            v_imag = 0;
            for (k = 0; k < 2; k = k + 1) {
                t_real = x_real[k + j];
                t_imag = x_imag[k + j];
                x_real[k + j + 2] = x_real[k + j] - v_real * x_real[k + j + 2] + v_imag * x_imag[k + j + 2];
                x_imag[k + j + 2] = x_imag[k + j] - v_real * x_imag[k + j + 2] - v_imag * x_real[k + j + 2];
                x_real[k + j] = x_real[k + j] - (x_real[k + j + 2] - x_real[k + j]);
                x_imag[k + j] = x_imag[k + j] - (x_imag[k + j + 2] - x_imag[k + j]);
                t_real = v_real;
                v_real = v_real * w_real - v_imag * w_imag;
                v_imag = t_real * w_imag + v_imag * w_real;
            }
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (x_real[i] - y_real[i] > 1 || x_imag[i] - y_imag[i] > 1) {
            return;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (x_real[i] - z_real[i] > 1 || x_imag[i] - z_imag[i] > 1) {
            return;
        }
    }
    
    return;
}
