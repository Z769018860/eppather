void fft(int real[10], int imag[10], int n) {
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
        ;
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
    return;
}
