void solve_trycell_show(int x[81], int pos, int row, int col, int i, int j, int used) {
    if (pos == 81) {
        for (i = 0; i < 9; i = i + 1) {
            for (j = 0; j < 9; j = j + 1) {
                int val = x[i * 9 + j];
            }
        }
        return;
    }
    if (x[pos] != 0) {
        solve_trycell_show(x, pos + 1, 0, 0, 0, 0, 0);
        return;
    }
    row = pos / 9;
    col = pos % 9;
    used = 0;
    for (i = 0; i < 9; i = i + 1) {
        used = used | (1 << (x[i * 9 + col] - 1));
    }
    for (j = 0; j < 9; j = j + 1) {
        used = used | (1 << (x[row * 9 + j] - 1));
    }
    row = (row / 3) * 3;
    col = (col / 3) * 3;
    for (i = row; i < row + 3; i = i + 1) {
        for (j = col; j < col + 3; j = j + 1) {
            used = used | (1 << (x[i * 9 + j] - 1));
        }
    }
    for (x[pos] = 1; x[pos] <= 9; x[pos] = x[pos] + 1) {
        if ((used & 1) == 0) {
            solve_trycell_show(x, pos + 1, 0, 0, 0, 0, 0);
        }
        used = used >> 1;
    }
    x[pos] = 0;
    return;
}

void solve(const char s[81]) {
    int x[81];
    int i;
    for (i = 0; i < 81; i = i + 1) {
        x[i] = (s[i] >= '1' && s[i] <= '9') ? (s[i] - '0') : 0;
    }
    solve_trycell_show(x, 0, 0, 0, 0, 0, 0);
    return;
}
