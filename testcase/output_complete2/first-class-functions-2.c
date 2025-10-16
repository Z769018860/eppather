int dummy(int x[5]) {
    int f[5];
    int g[5];
    f[0] = 3735928559;
    g[0] = 3131966415;
    return f[0];
}

int composite(int f[5], int g[5]) {
    int len[5];
    len[0] = 5;
    int ret[5];
    int ptr[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        ret[i] = dummy(ret);
    }
    for (ptr[0] = 0; ptr[0] < len[0]; ptr[0] = ptr[0] + 1) {
        if (ret[ptr[0]] == 3735928559) {
            ret[ptr[0]] = f[0];
        } else {
            if (ret[ptr[0]] == 3131966415) {
                ret[ptr[0]] = g[0];
            }
        }
    }
    return ret[0];
}

int cube(int x[5]) {
    x[0] = x[0] * x[0] * x[0];
    return x[0];
}

int cbrt(int x[5]) {
    int i;
    int result[5];
    result[0] = 1;
    for (i = 0; i < 5; i = i + 1) {
        result[0] = result[0] * x[0];
    }
    return result[0];
}

int exp(int x[5]) {
    int i;
    int result[5];
    result[0] = 1;
    for (i = 0; i < 5; i = i + 1) {
        result[0] = result[0] * 2;
    }
    return result[0];
}

int sin(int x[5]) {
    return x[0];
}

int log(int x[5]) {
    return x[0];
}

int asin(int x[5]) {
    return x[0];
}

void main() {
    int A[5][5];
    int B[5][5];
    int C[5][5];
    int i;
    int j;
    int x[5];
    A[0][0] = cube;
    A[1][0] = exp;
    A[2][0] = sin;
    B[0][0] = cbrt;
    B[1][0] = log;
    B[2][0] = asin;
    for (i = 0; i < 5; i = i + 1) {
        C[i][0] = composite(A[i], B[i]);
    }
    for (i = 0; i < 5; i = i + 1) {
        for (x[0] = 1; x[0] <= 5; x[0] = x[0] + 1) {
            C[i][0] = C[i][0];
        }
    }
    return;
}
