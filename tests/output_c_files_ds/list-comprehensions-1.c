int* func(int f, int t, int* e) {
    int i;
    int nx[1];
    for (i = f + 1; i <= t; i = i + 1) {
        nx[0] = i;
        e = nx;
    }
    return;
}
