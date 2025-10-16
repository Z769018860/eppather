int cooling(int t, int temp) {
    int result;
    result = -7 * (temp - 2000) / 100;
    return result;
}

void ivp_euler_analytic() {
    int t;
    int y;
    int step;
    int end_t;
    int temp;
    for (t = 0; t <= 1000; t = t + 100) {
        temp = 2000 + 8000 * (100 - 7 * t / 100) / 100;
    }
    for (t = 0; t <= 1000; t = t + 100) {
        temp = 2000 + 8000 * (100 - 7 * t / 100) / 100;
    }
    return;
}

void ivp_euler(int step, int end_t) {
    int t;
    int y;
    y = 10000;
    for (t = 0; t <= end_t; t = t + step) {
        if (t % 100 == 0) {
            y = y;
        }
        y = y + step * cooling(t, y) / 100;
    }
    return;
}
