int in_circle(int x[5], int y[5]) {
    if ((x[0] * x[0] + y[0] * y[0]) < 1) {
        return 1;
    } else {
        return 0;
    }
}

void monte_carlo(int samples[5], int result[5]) {
    int count[5];
    count[0] = 0;
    int i;
    int x[5];
    int y[5];
    
    for (i = 0; i < 5; i = i + 1) {
        x[0] = 0;
        y[0] = 0;
        if (in_circle(x, y)) {
            count[0] = count[0] + 1;
        }
    }
    
    result[0] = 4 * count[0] / samples[0];
    return;
}
