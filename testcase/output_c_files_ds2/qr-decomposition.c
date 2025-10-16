int householder(int m_m, int m_n, int in_0_0, int in_0_1, int in_0_2, int in_1_0, int in_1_1, int in_1_2, int in_2_0, int in_2_1, int in_2_2, int in_3_0, int in_3_1, int in_3_2, int in_4_0, int in_4_1, int in_4_2) {
    int x[5][5];
    int e[5][5];
    int q[5][5][5];
    int z[5][5];
    int z1[5][5];
    int R[5][5];
    int Q[5][5];
    int k;
    int i;
    int j;
    int c;
    int a;
    int sum;
    int t;

    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            z[i][j] = 0;
            z1[i][j] = 0;
            R[i][j] = 0;
            Q[i][j] = 0;
            for (k = 0; k < 5; k = k + 1) {
                q[i][j][k] = 0;
            }
        }
    }

    z[0][0] = in_0_0;
    z[0][1] = in_0_1;
    z[0][2] = in_0_2;
    z[1][0] = in_1_0;
    z[1][1] = in_1_1;
    z[1][2] = in_1_2;
    z[2][0] = in_2_0;
    z[2][1] = in_2_1;
    z[2][2] = in_2_2;
    z[3][0] = in_3_0;
    z[3][1] = in_3_1;
    z[3][2] = in_3_2;
    z[4][0] = in_4_0;
    z[4][1] = in_4_1;
    z[4][2] = in_4_2;

    for (k = 0; k < 5; k = k + 1) {
        for (i = 0; i < 5; i = i + 1) {
            for (j = 0; j < 5; j = j + 1) {
                z1[i][j] = z[i][j];
            }
        }

        for (i = 0; i < 5; i = i + 1) {
            x[i][0] = z1[i][k];
        }

        sum = 0;
        for (i = 0; i < 5; i = i + 1) {
            sum = sum + x[i][0] * x[i][0];
        }
        a = sum;

        if (z1[k][k] > 0) {
            a = -a;
        }

        for (i = 0; i < 5; i = i + 1) {
            e[i][0] = (i == k) ? 1 : 0;
        }

        for (i = 0; i < 5; i = i + 1) {
            e[i][0] = x[i][0] + a * e[i][0];
        }

        sum = 0;
        for (i = 0; i < 5; i = i + 1) {
            sum = sum + e[i][0] * e[i][0];
        }
        for (i = 0; i < 5; i = i + 1) {
            e[i][0] = e[i][0] / sum;
        }

        for (i = 0; i < 5; i = i + 1) {
            for (j = 0; j < 5; j = j + 1) {
                q[k][i][j] = -2 * e[i][0] * e[j][0];
            }
        }

        for (i = 0; i < 5; i = i + 1) {
            q[k][i][i] = q[k][i][i] + 1;
        }

        for (i = 0; i < 5; i = i + 1) {
            for (j = 0; j < 5; j = j + 1) {
                sum = 0;
                for (c = 0; c < 5; c = c + 1) {
                    sum = sum + q[k][i][c] * z1[c][j];
                }
                z[i][j] = sum;
            }
        }
    }

    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            Q[i][j] = q[0][i][j];
        }
    }

    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            sum = 0;
            for (k = 0; k < 5; k = k + 1) {
                sum = sum + Q[i][k] * z[k][j];
            }
            R[i][j] = sum;
        }
    }

    for (k = 1; k < 5; k = k + 1) {
        for (i = 0; i < 5; i = i + 1) {
            for (j = 0; j < 5; j = j + 1) {
                sum = 0;
                for (c = 0; c < 5; c = c + 1) {
                    sum = sum + q[k][i][c] * Q[c][j];
                }
                z1[i][j] = sum;
            }
        }
        for (i = 0; i < 5; i = i + 1) {
            for (j = 0; j < 5; j = j + 1) {
                Q[i][j] = z1[i][j];
            }
        }
    }

    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            sum = 0;
            for (k = 0; k < 5; k = k + 1) {
                sum = sum + Q[i][k] * z[k][j];
            }
            z1[i][j] = sum;
        }
    }

    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            R[i][j] = z1[i][j];
        }
    }

    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < i; j = j + 1) {
            t = Q[i][j];
            Q[i][j] = Q[j][i];
            Q[j][i] = t;
        }
    }

    return;
}
