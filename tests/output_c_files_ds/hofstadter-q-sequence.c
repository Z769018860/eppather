int func() {
    int q[100001];
    int i;
    int flip;
    q[1] = 1;
    q[2] = 1;
    for (i = 3; i <= 100000; i = i + 1) {
        q[i] = q[i - q[i - 1]] + q[i - q[i - 2]];
    }
    flip = 0;
    for (i = 1; i < 100000; i = i + 1) {
        if (q[i] > q[i + 1]) {
            flip = flip + 1;
        }
    }
    return;
}
