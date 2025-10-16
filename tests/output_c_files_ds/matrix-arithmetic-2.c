void det(int* in, int n) {
    int m[18][18];
    for (int i = 0; i < n; i = i + 1) {
        for (int j = 0; j < n; j = j + 1) {
            m[i][j] = in[i * n + j];
        }
    }

    int sign = 1;
    for (int i = 0; i < n; i = i + 1) {
        int max = i;
        for (int row = i; row < n; row = row + 1) {
            if ((m[row][i] > 0 ? m[row][i] : -m[row][i]) > (m[max][i] > 0 ? m[max][i] : -m[max][i])) {
                max = row;
            }
        }

        if (max != i) {
            sign = -sign;
            for (int col = 0; col < n; col = col + 1) {
                int tmp = m[i][col];
                m[i][col] = m[max][col];
                m[max][col] = tmp;
            }
        }

        if (m[i][i] == 0) {
            return;
        }

        for (int row = i + 1; row < n; row = row + 1) {
            int r = m[row][i] / m[i][i];
            if (r == 0) {
                continue;
            }

            for (int col = i; col < n; col = col + 1) {
                m[row][col] = m[row][col] - m[i][col] * r;
            }
        }
    }

    int p = 1;
    for (int i = 0; i < n; i = i + 1) {
        p = p * m[i][i];
    }
    p = p * sign;
    return;
}
