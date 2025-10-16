int foo(int filename) {
    int foo[5];
    int new_times[2][5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        foo[i] = 0;
    }
    for (i = 0; i < 2; i = i + 1) {
        for (int j = 0; j < 5; j = j + 1) {
            new_times[i][j] = 0;
        }
    }
    if (filename < 0) {
        return;
    }
    for (i = 0; i < 5; i = i + 1) {
        new_times[0][i] = foo[i];
    }
    if (filename < 0) {
        return;
    }
    return;
}
