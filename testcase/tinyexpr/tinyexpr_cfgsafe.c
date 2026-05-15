#include <stdio.h>

static double fac(double a) {
    if (a < 0.0) return 0.0;
    double r = 1.0;
    int i = 1;
    while (i <= (int)a) {
        r = r * i;
        i = i + 1;
    }
    return r;
}

static double ncr(double n, double r) {
    if (r < 0.0 || n < r) return 0.0;
    return fac(n) / (fac(r) * fac(n - r));
}

static double npr(double n, double r) {
    if (r < 0.0 || n < r) return 0.0;
    return fac(n) / fac(n - r);
}

int main(void) {
    double a = ncr(5, 2);
    double b = npr(5, 2);
    if (a > b) {
        printf("%f\n", a);
    } else {
        printf("%f\n", b);
    }
    return 0;
}
