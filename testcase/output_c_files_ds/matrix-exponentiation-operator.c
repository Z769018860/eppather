void matrixMultiply(int mr[3][3], int left[3][3], int right[3][3]) {
    int rw;
    int col;
    int ix;
    int sum;
    for (rw = 0; rw < 3; rw = rw + 1) {
        for (col = 0; col < 3; col = col + 1) {
            sum = 0;
            for (ix = 0; ix < 3; ix = ix + 1) {
                sum = sum + left[rw][ix] * right[ix][col];
            }
            mr[rw][col] = sum;
        }
    }
    return;
}

void matrixIdentity(int cells[3][3]) {
    int rw;
    int col;
    for (rw = 0; rw < 3; rw = rw + 1) {
        for (col = 0; col < 3; col = col + 1) {
            cells[rw][col] = 0;
        }
        cells[rw][rw] = 1;
    }
    return;
}

void matrixCopy(int dest[3][3], int src[3][3]) {
    int rw;
    int col;
    for (rw = 0; rw < 3; rw = rw + 1) {
        for (col = 0; col < 3; col = col + 1) {
            dest[rw][col] = src[rw][col];
        }
    }
    return;
}

void matrixPow(int result[3][3], int base[3][3], int exp) {
    int v0[3][3];
    int v1[3][3];
    int base0[3][3];
    int base1[3][3];
    int temp[3][3];
    int i;
    
    matrixIdentity(v0);
    matrixCopy(base0, base);
    
    for (i = 0; i < 3; i = i + 1) {
        for (int j = 0; j < 3; j = j + 1) {
            v1[i][j] = 0;
            base1[i][j] = 0;
        }
    }
    
    while (exp > 0) {
        if (exp % 2 == 1) {
            matrixMultiply(temp, v0, base0);
            for (i = 0; i < 3; i = i + 1) {
                for (int j = 0; j < 3; j = j + 1) {
                    v1[i][j] = temp[i][j];
                }
            }
            for (i = 0; i < 3; i = i + 1) {
                for (int j = 0; j < 3; j = j + 1) {
                    temp[i][j] = v0[i][j];
                    v0[i][j] = v1[i][j];
                    v1[i][j] = temp[i][j];
                }
            }
        }
        matrixMultiply(temp, base0, base0);
        for (i = 0; i < 3; i = i + 1) {
            for (int j = 0; j < 3; j = j + 1) {
                base1[i][j] = temp[i][j];
            }
        }
        for (i = 0; i < 3; i = i + 1) {
            for (int j = 0; j < 3; j = j + 1) {
                temp[i][j] = base0[i][j];
                base0[i][j] = base1[i][j];
                base1[i][j] = temp[i][j];
            }
        }
        exp = exp / 2;
    }
    matrixCopy(result, v0);
    return;
}
