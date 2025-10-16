void fft(int buf_real[5], int buf_imag[5], int out_real[5], int out_imag[5], int n, int step) {
    if (step < n) {
        fft(out_real, out_imag, buf_real, buf_imag, n, step * 2);
        int step1 = step;
        int out_real1[5];
        int out_imag1[5];
        for (int i = 0; i < 5; i = i + 1) {
            if (i < step) {
                out_real1[i] = out_real[i + step1];
                out_imag1[i] = out_imag[i + step1];
            } else {
                out_real1[i] = 0;
                out_imag1[i] = 0;
            }
        }
        fft(out_real1, out_imag1, buf_real, buf_imag, n, step * 2);

        for (int i = 0; i < 5; i = i + 1) {
            if (i < n && i % (2 * step) == 0) {
                int pi = 3;
                int angle = -pi * i / n;
                int cos_val = 1;
                int sin_val = 0;
                int t_real = cos_val * out_real[i + step] - sin_val * out_imag[i + step];
                int t_imag = sin_val * out_real[i + step] + cos_val * out_imag[i + step];
                buf_real[i / 2] = out_real[i] + t_real;
                buf_imag[i / 2] = out_imag[i] + t_imag;
                buf_real[(i + n) / 2] = out_real[i] - t_real;
                buf_imag[(i + n) / 2] = out_imag[i] - t_imag;
            }
        }
    }
    return;
}
