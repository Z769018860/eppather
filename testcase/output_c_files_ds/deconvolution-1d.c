void deconv(double g[], int lg, double f[], int lf, double out[]) {
    int ns;
    int n;
    int i;
    int j;
    double real_g2[32];
    double imag_g2[32];
    double real_f2[32];
    double imag_f2[32];
    double real_h[32];
    double imag_h[32];
    double tmp_real;
    double tmp_imag;
    double angle;
    double cos_val;
    double sin_val;
    int step;
    int k;
    int m;
    
    ns = 1;
    while (ns < lg) {
        ns = ns * 2;
    }
    while (ns < lf) {
        ns = ns * 2;
    }
    
    for (i = 0; i < 32; i = i + 1) {
        real_g2[i] = 0.0;
        imag_g2[i] = 0.0;
        real_f2[i] = 0.0;
        imag_f2[i] = 0.0;
    }
    
    for (i = 0; i < lg; i = i + 1) {
        real_g2[i] = g[i];
    }
    for (i = 0; i < lf; i = i + 1) {
        real_f2[i] = f[i];
    }
    
    n = ns;
    for (step = 1; step < n; step = step * 2) {
        for (i = 0; i < n; i = i + step * 2) {
            for (j = 0; j < step; j = j + 1) {
                angle = -3.141592653589793 * (i + j) / n;
                cos_val = 1.0;
                sin_val = 0.0;
                for (k = 1; k <= 10; k = k + 1) {
                    tmp_real = cos_val;
                    tmp_imag = sin_val;
                    cos_val = tmp_real * angle - tmp_imag * angle;
                    sin_val = tmp_real * angle + tmp_imag * angle;
                }
                tmp_real = real_g2[i + j + step] * cos_val - imag_g2[i + j + step] * sin_val;
                tmp_imag = real_g2[i + j + step] * sin_val + imag_g2[i + j + step] * cos_val;
                real_h[i / 2 + j] = real_g2[i + j] + tmp_real;
                imag_h[i / 2 + j] = imag_g2[i + j] + tmp_imag;
                real_h[(i + n) / 2 + j] = real_g2[i + j] - tmp_real;
                imag_h[(i + n) / 2 + j] = imag_g2[i + j] - tmp_imag;
            }
        }
        for (i = 0; i < n; i = i + 1) {
            real_g2[i] = real_h[i];
            imag_g2[i] = imag_h[i];
        }
    }
    
    n = ns;
    for (step = 1; step < n; step = step * 2) {
        for (i = 0; i < n; i = i + step * 2) {
            for (j = 0; j < step; j = j + 1) {
                angle = -3.141592653589793 * (i + j) / n;
                cos_val = 1.0;
                sin_val = 0.0;
                for (k = 1; k <= 10; k = k + 1) {
                    tmp_real = cos_val;
                    tmp_imag = sin_val;
                    cos_val = tmp_real * angle - tmp_imag * angle;
                    sin_val = tmp_real * angle + tmp_imag * angle;
                }
                tmp_real = real_f2[i + j + step] * cos_val - imag_f2[i + j + step] * sin_val;
                tmp_imag = real_f2[i + j + step] * sin_val + imag_f2[i + j + step] * cos_val;
                real_h[i / 2 + j] = real_f2[i + j] + tmp_real;
                imag_h[i / 2 + j] = imag_f2[i + j] + tmp_imag;
                real_h[(i + n) / 2 + j] = real_f2[i + j] - tmp_real;
                imag_h[(i + n) / 2 + j] = imag_f2[i + j] - tmp_imag;
            }
        }
        for (i = 0; i < n; i = i + 1) {
            real_f2[i] = real_h[i];
            imag_f2[i] = imag_h[i];
        }
    }
    
    for (i = 0; i < ns; i = i + 1) {
        tmp_real = real_g2[i] * real_f2[i] + imag_g2[i] * imag_f2[i];
        tmp_imag = imag_g2[i] * real_f2[i] - real_g2[i] * imag_f2[i];
        real_h[i] = tmp_real / (real_f2[i] * real_f2[i] + imag_f2[i] * imag_f2[i]);
        imag_h[i] = tmp_imag / (real_f2[i] * real_f2[i] + imag_f2[i] * imag_f2[i]);
    }
    
    n = ns;
    for (step = 1; step < n; step = step * 2) {
        for (i = 0; i < n; i = i + step * 2) {
            for (j = 0; j < step; j = j + 1) {
                angle = -3.141592653589793 * (i + j) / n;
                cos_val = 1.0;
                sin_val = 0.0;
                for (k = 1; k <= 10; k = k + 1) {
                    tmp_real = cos_val;
                    tmp_imag = sin_val;
                    cos_val = tmp_real * angle - tmp_imag * angle;
                    sin_val = tmp_real * angle + tmp_imag * angle;
                }
                tmp_real = real_h[i + j + step] * cos_val - imag_h[i + j + step] * sin_val;
                tmp_imag = real_h[i + j + step] * sin_val + imag_h[i + j + step] * cos_val;
                real_g2[i / 2 + j] = real_h[i + j] + tmp_real;
                imag_g2[i / 2 + j] = imag_h[i + j] + tmp_imag;
                real_g2[(i + n) / 2 + j] = real_h[i + j] - tmp_real;
                imag_g2[(i + n) / 2 + j] = imag_h[i + j] - tmp_imag;
            }
        }
        for (i = 0; i < n; i = i + 1) {
            real_h[i] = real_g2[i];
            imag_h[i] = imag_g2[i];
        }
    }
    
    for (i = lf - lg; i <= 0; i = i + 1) {
        m = (i + ns) % ns;
        out[-i] = real_h[m] / 32.0;
    }
    
    return;
}
