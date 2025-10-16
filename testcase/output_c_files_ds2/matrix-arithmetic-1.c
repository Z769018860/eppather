int det_in(int in[5][5], int n, int perm, int m[5][5]) {
    if (n == 1) {
        return in[0][0];
    }
    int sum[5];
    sum[0] = 0;
    int n1 = n - 1;
    for (int i = 0; i < n1; i = i + 1) {
        for (int j = 0; j < n1; j = j + 1) {
            m[i][j] = in[i + 1][j + 1];
        }
    }
    int sgn[5];
    sgn[0] = 1;
    for (int i = 0; i <= n1; i = i + 1) {
        int temp[5][5];
        for (int k = 0; k < 5; k = k + 1) {
            for (int l = 0; l < 5; l = l + 1) {
                temp[k][l] = m[k][l];
            }
        }
        sum[0] = sum[0] + sgn[0] * (in[i][0] * det_in(temp, n1, perm, temp));
        if (i == n1) {
            break;
        }
        for (int j = 0; j < n1; j = j + 1) {
            m[i][j] = in[i][j + 1];
        }
        if (perm == 0) {
            sgn[0] = -sgn[0];
        }
    }
    return sum[0];
}

int det(int in[5][5], int n, int perm) {
    int m[5][5];
    for (int i = 0; i < n; i = i + 1) {
        for (int j = 0; j < n; j = j + 1) {
            m[i][j] = in[i][j];
        }
    }
    return det_in(m, n, perm, m);
}

void main() {
    return;
}
