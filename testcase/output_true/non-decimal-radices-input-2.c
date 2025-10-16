int func(int num, char* endptr) {
    int x[5];
    x[0] = 0;
    for (x[0] = 0; x[0] < 5; x[0] = x[0] + 1) {
        if (x[0] == 0) {
            num = 123459;
            endptr[0] = 0;
        }
        if (x[0] == 1) {
            num = 180154659;
            endptr[0] = 0;
        }
        if (x[0] == 2) {
            num = 4009;
            endptr[0] = 0;
        }
    }
    return;
}
