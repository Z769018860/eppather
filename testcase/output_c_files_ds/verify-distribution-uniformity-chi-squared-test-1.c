double func(double t, double aa1) {
    double result = 1.0;
    int i;
    for (i = 0; i < aa1; i = i + 1) {
        result = result * t;
    }
    double temp = 0.0 - t;
    double exp_val = 1.0;
    double term = 1.0;
    for (i = 1; i < 20; i = i + 1) {
        term = term * temp / i;
        exp_val = exp_val + term;
    }
    return result * exp_val;
}

double Gamma_Spouge(double z) {
    int k;
    double cspace[12];
    double coefs[12];
    double accum;
    double a = 12.0;
    double k1_factrl = 1.0;
    double pi = 3.14159265358979323846;
    double sqrt_val = 1.0;
    double temp = 2.0 * pi;
    for (k = 0; k < 100; k = k + 1) {
        sqrt_val = (sqrt_val + temp / sqrt_val) / 2.0;
    }
    coefs[0] = sqrt_val;
    for (k = 1; k < 12; k = k + 1) {
        double exp_val = 1.0;
        double term = 1.0;
        double arg = a - k;
        for (int i = 1; i < 20; i = i + 1) {
            term = term * arg / i;
            exp_val = exp_val + term;
        }
        double pow_val = 1.0;
        for (int i = 0; i < k - 0.5; i = i + 1) {
            pow_val = pow_val * arg;
        }
        coefs[k] = exp_val * pow_val / k1_factrl;
        k1_factrl = k1_factrl * (-k);
    }
    accum = coefs[0];
    for (k = 1; k < 12; k = k + 1) {
        accum = accum + coefs[k] / (z + k);
    }
    double exp_val = 1.0;
    double term = 1.0;
    double arg = 0.0 - (z + a);
    for (k = 1; k < 20; k = k + 1) {
        term = term * arg / k;
        exp_val = exp_val + term;
    }
    double pow_val = 1.0;
    for (k = 0; k < z + 0.5; k = k + 1) {
        pow_val = pow_val * (z + a);
    }
    accum = accum * exp_val * pow_val;
    return accum / z;
}

double Simpson3_8(double a, double b, int N, double aa1) {
    int j;
    double l1;
    double h = (b - a) / N;
    double h1 = h / 3.0;
    double sum = func(a, aa1) + func(b, aa1);
    for (j = 3 * N - 1; j > 0; j = j - 1) {
        l1 = (j % 3) ? 3.0 : 2.0;
        sum = sum + l1 * func(a + h1 * j, aa1);
    }
    return h * sum / 8.0;
}

double GammaIncomplete_Q(double a, double x) {
    double y = a - 1.0;
    double aa1 = a - 1.0;
    double f0_y = func(y, aa1);
    double x_minus_y = x - y;
    while ((f0_y * x_minus_y > 2.0e-8) && (y < x)) {
        y = y + 0.4;
        f0_y = func(y, aa1);
        x_minus_y = x - y;
    }
    if (y > x) {
        y = x;
    }
    double h = 1.5e-2;
    int N = y / h;
    double simpson = Simpson3_8(0.0, y, N, aa1);
    double gamma = Gamma_Spouge(a);
    return 1.0 - simpson / gamma;
}
