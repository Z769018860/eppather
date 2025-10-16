void foo_func(int n) {
    int foos[5][5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        int j;
        for (j = 0; j < 5; j = j + 1) {
            foos[i][j] = 0;
        }
    }
    return;
}
