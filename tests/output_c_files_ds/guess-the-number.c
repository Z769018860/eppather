int guess_number(int n, int g, int c) {
    for (;;) {
        if (g != 0) {
            if (g == n) {
                return 0;
            }
            g = 0;
        }
        else {
            c = 0;
        }
    }
    return;
}
