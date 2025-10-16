int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; i = i + 1) {
        result = result * i;
    }
    return result;
}

double log_approx(double x) {
    double term = x - 1;
    double sum = term;
    for (int i = 2; i < 10; i = i + 1) {
        term = term * (1 - x) * (i - 1) / i;
        sum = sum + term;
    }
    return sum;
}

double pow_approx(double base, int exponent) {
    double result = 1;
    for (int i = 0; i < exponent; i = i + 1) {
        result = result * base;
    }
    return result;
}

void h(int n) {
    int a_fact = factorial(n);
    double log_2 = log_approx(2);
    double log_pow = pow_approx(log_2, n + 1);
    double a = (double)a_fact / log_pow;
    a = a / 2;
    double b = a - (int)a;
    int cmp1 = (b > 0.1) ? 1 : -1;
    int cmp2 = (b < 0.9) ? 1 : -1;
    int flag = (cmp1 * cmp2 > 0) ? 1 : 0;
    return;
}
