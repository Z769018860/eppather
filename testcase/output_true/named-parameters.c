void FTest2(int x[5], int y[5], int z[5]) {
    for (int i = 0; i < 5; i = i + 1) {
        x[i] = x[0];
        y[i] = y[0];
        z[i] = z[0];
    }
    return;
}
