void fft(int buf_real[], int buf_imag[], int out_real[], int out_imag[], int n, int step) {
    if (step < n) {
        fft(out_real, out_imag, buf_real, buf_imag, n, step * 2);
        fft(out_real + step, out_imag + step, buf_real + step, buf_imag + step, n, step * 2);
        
        for (int i = 0; i < n; i = i + 2 * step) {
            int angle = -314 * i / n;
            int cos_val = 1000;
            int sin_val = 0;
            
            int temp_real = (out_real[i + step] * cos_val - out_imag[i + step] * sin_val) / 1000;
            int temp_imag = (out_real[i + step] * sin_val + out_imag[i + step] * cos_val) / 1000;
            
            buf_real[i / 2] = out_real[i] + temp_real;
            buf_imag[i / 2] = out_imag[i] + temp_imag;
            buf_real[(i + n) / 2] = out_real[i] - temp_real;
            buf_imag[(i + n) / 2] = out_imag[i] - temp_imag;
        }
    }
    return;
}
