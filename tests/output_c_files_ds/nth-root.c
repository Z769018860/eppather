int root_pow(int x, int e) {
    int r = 1;
    for (int i = 0; i < e; i = i + 1) {
        r = r * x;
    }
    return r;
}

void root(int n, int x, int r_arr[1]) {
    int d;
    int r = 1;
    if (x == 0) {
        r_arr[0] = 0;
        return;
    }
    if (n < 1 || (x < 0 && (n & 1) == 0)) {
        r_arr[0] = 0;
        return;
    }
    for (;;) {
        d = (x / root_pow(r, n - 1) - r) / n;
        r = r + d;
        if (!(d >= 10 || d <= -10)) {
            break;
        }
    }
    r_arr[0] = r;
    return;
}
