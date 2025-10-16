void rewritten_func(int k) {
    int i[5] = {0};
    int j[5] = {0};
    int r[5] = {0};
    int x[5] = {0};
    int y[5] = {-16};
    int k_copy[5] = {0};
    char chars[17] = " .:-;!/>)|&IH%*#";

    for (; y[0] < 15; y[0] = y[0] + 1) {
        for (x[0] = 0; x[0] < 84; x[0] = x[0] + 1) {
            for (i[0] = 0, r[0] = 0, k_copy[0] = 0; ; k_copy[0] = k_copy[0] + 1) {
                j[0] = r[0] * r[0] - i[0] * i[0] - 2 + x[0] / 25;
                i[0] = 2 * r[0] * i[0] + y[0] / 10;
                if (j[0] * j[0] + i[0] * i[0] >= 11 || k_copy[0] >= 111) {
                    break;
                }
                r[0] = j[0];
            }
        }
    }
    return;
}
