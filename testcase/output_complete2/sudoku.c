void trycell(int x[81], int pos, int used, int row, int col, int i, int j, int k, int l, int m, int n) {
    row = pos / 9;
    col = pos % 9;
    used = 0;

    if (pos == 81) {
        return;
    }
    if (x[pos] != 0) {
        trycell(x, pos + 1, used, row, col, i, j, k, l, m, n);
        return;
    }

    for (i = 0; i < 9; i = i + 1) {
        used = used | (1 << (x[i * 9 + col] - 1));
    }

    for (j = 0; j < 9; j = j + 1) {
        used = used | (1 << (x[row * 9 + j] - 1));
    }

    row = row / 3 * 3;
    col = col / 3 * 3;
    for (k = row; k < row + 3; k = k + 1) {
        for (l = col; l < col + 3; l = l + 1) {
            used = used | (1 << (x[k * 9 + l] - 1));
        }
    }

    for (x[pos] = 1; x[pos] <= 9; x[pos] = x[pos] + 1) {
        if ((used & 1) == 0) {
            trycell(x, pos + 1, used, row, col, i, j, k, l, m, n);
        }
        used = used >> 1;
    }

    x[pos] = 0;
    return;
}
