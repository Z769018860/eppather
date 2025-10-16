int cooling(int t[5], int temp[5]) {
    temp[0] = -7 * (temp[0] - 20) / 100;
    return temp[0];
}

void ivp_euler(int f(int[5], int[5]), int y[5], int step[5], int end_t[5]) {
    int t[5];
    t[0] = 0;
    int i;
    for (i = 0; i < 5; i = i + 1) {
        if (t[0] % 10 == 0) {
            y[0] = y[0];
        }
        y[0] = y[0] + step[0] * f(t, y);
        t[0] = t[0] + step[0];
        if (t[0] > end_t[0]) {
            break;
        }
    }
    return;
}

void analytic() {
    int t[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        t[0] = i * 10;
        y[0] = 20 + 80 * (1 - 7 * t[0] / 1000);
    }
    return;
}
