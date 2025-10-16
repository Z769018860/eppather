void eop_add(int a[5][5], int b[5][5], int c[5][5], int w, int h) {
    int i;
    int j;
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    return;
}

void eop_sub(int a[5][5], int b[5][5], int c[5][5], int w, int h) {
    int i;
    int j;
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            c[i][j] = a[i][j] - b[i][j];
        }
    }
    return;
}

void eop_mul(int a[5][5], int b[5][5], int c[5][5], int w, int h) {
    int i;
    int j;
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            c[i][j] = a[i][j] * b[i][j];
        }
    }
    return;
}

void eop_div(int a[5][5], int b[5][5], int c[5][5], int w, int h) {
    int i;
    int j;
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            c[i][j] = a[i][j] / b[i][j];
        }
    }
    return;
}

void eop_s_mul(int a[5][5], int s, int b[5][5], int w, int h) {
    int i;
    int j;
    int x;
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            x = a[i][j];
            b[i][j] = x * s;
        }
    }
    return;
}

void eop_s_div(int a[5][5], int s, int b[5][5], int w, int h) {
    int i;
    int j;
    int x;
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            x = a[i][j];
            b[i][j] = x / s;
        }
    }
    return;
}

void eop_s_add(int a[5][5], int s, int b[5][5], int w, int h) {
    int i;
    int j;
    int x;
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            x = a[i][j];
            b[i][j] = x + s;
        }
    }
    return;
}

void eop_s_sub(int a[5][5], int s, int b[5][5], int w, int h) {
    int i;
    int j;
    int x;
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            x = a[i][j];
            b[i][j] = x - s;
        }
    }
    return;
}

void eop_s_pow(int a[5][5], int s, int b[5][5], int w, int h) {
    int i;
    int j;
    int x;
    int r;
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            x = a[i][j];
            r = 1;
            for (int k = 0; k < s; k = k + 1) {
                r = r * x;
            }
            b[i][j] = r;
        }
    }
    return;
}
