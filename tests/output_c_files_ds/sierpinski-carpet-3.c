void sierpinski(char base[2187][2187], int xbegin, int xend, int ybegin, int yend, int iterations) {
    if (iterations == 0) {
        return;
    }
    {
        int len = xend - xbegin + 1;
        int unit = len / 3;
        for (int i = xbegin + unit; i < xbegin + 2 * unit; i = i + 1) {
            for (int j = ybegin + unit; j < ybegin + 2 * unit; j = j + 1) {
                base[j][i] = ' ';
            }
        }
    }
    if (iterations == 1) {
        return;
    }
    for (int i = 0; i < 3; i = i + 1) {
        for (int j = 0; j < 3; j = j + 1) {
            int length = xend - xbegin + 1;
            int unit = length / 3;
            int new_xbegin = xbegin + i * unit;
            int new_xend = xbegin + (i + 1) * unit - 1;
            int new_ybegin = ybegin + j * unit;
            int new_yend = ybegin + (j + 1) * unit - 1;
            sierpinski(base, new_xbegin, new_xend, new_ybegin, new_yend, iterations - 1);
        }
    }
    return;
}
