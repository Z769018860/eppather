void fft(int buf_real[], int buf_imag[], int n) {
    int inputMemory_real[100];
    int inputMemory_imag[100];
    int outputMemory_real[100];
    int outputMemory_imag[100];
    
    for (int i = 0; i < n; i = i + 1) {
        inputMemory_real[i] = buf_real[i];
        inputMemory_imag[i] = buf_imag[i];
    }
    
    for (int i = 0; i < n; i = i + 1) {
        outputMemory_real[i] = 0;
        outputMemory_imag[i] = 0;
    }
    
    for (int k = 0; k < n; k = k + 1) {
        for (int m = 0; m < n; m = m + 1) {
            int angle = -2 * 3 * k * m / n;
            int c = 1;
            int s = 0;
            outputMemory_real[k] = outputMemory_real[k] + inputMemory_real[m] * c - inputMemory_imag[m] * s;
            outputMemory_imag[k] = outputMemory_imag[k] + inputMemory_real[m] * s + inputMemory_imag[m] * c;
        }
    }
    
    for (int i = 0; i < n; i = i + 1) {
        buf_real[i] = outputMemory_real[i];
        buf_imag[i] = outputMemory_imag[i];
    }
    
    return;
}
