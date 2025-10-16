void computus(int year, int servois, int out[5], int out_size) {
    int a[5]; a[0] = year % 19;
    int k[5]; k[0] = year / 100;
    int p[5]; p[0] = (13 + 8 * k[0]) / 25;
    int q[5]; q[0] = k[0] / 4;
    int M[5]; M[0] = (15 - p[0] + k[0] - q[0]) % 30;
    int d[5]; d[0] = (19 * a[0] + M[0]) % 30;

    if (servois != 0) {
        out[0] = (21 + d[0]) % 31;
        return;
    }

    int N[5]; N[0] = (4 + k[0] - q[0]) % 7;
    int b[5]; b[0] = year % 4;
    int c[5]; c[0] = year % 7;
    int e[5]; e[0] = (2 * b[0] + 4 * c[0] + 6 * d[0] + N[0]) % 7;

    if ((d[0] == 29 && e[0] == 6) || (d[0] == 28 && e[0] == 6 && a[0] > 10)) {
        e[0] = -1;
    }

    if ((22 + d[0] + e[0]) > 31) {
        out[0] = d[0] + e[0] - 9;
    } else {
        out[0] = 22 + d[0] + e[0];
    }

    return;
}
