int isHermitian(int a_rows, int a_cols, int a_real[5][5], int a_imag[5][5]) {
    int i;
    int j;
    int b_rows;
    int b_cols;
    int b_real[5][5];
    int b_imag[5][5];
    
    b_rows = a_cols;
    b_cols = a_rows;
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            b_real[i][j] = a_real[j][i];
            b_imag[i][j] = -a_imag[j][i];
        }
    }
    
    if (b_rows == a_rows && b_cols == a_cols) {
        for (i = 0; i < 5; i = i + 1) {
            for (j = 0; j < 5; j = j + 1) {
                if (b_real[i][j] != a_real[i][j] || b_imag[i][j] != a_imag[i][j]) {
                    return 0;
                }
            }
        }
    } else {
        return 0;
    }
    
    return 1;
}

int multiply(int a_rows, int a_cols, int a_real[5][5], int a_imag[5][5], int b_rows, int b_cols, int b_real[5][5], int b_imag[5][5], int c_real[5][5], int c_imag[5][5]) {
    int i;
    int j;
    int k;
    
    if (a_cols == b_rows) {
        for (i = 0; i < 5; i = i + 1) {
            for (j = 0; j < 5; j = j + 1) {
                c_real[i][j] = 0;
                c_imag[i][j] = 0;
                for (k = 0; k < 5; k = k + 1) {
                    c_real[i][j] = c_real[i][j] + (a_real[i][k] * b_real[k][j] - a_imag[i][k] * b_imag[k][j]);
                    c_imag[i][j] = c_imag[i][j] + (a_real[i][k] * b_imag[k][j] + a_imag[i][k] * b_real[k][j]);
                }
            }
        }
    }
    
    return 0;
}

int isNormal(int a_rows, int a_cols, int a_real[5][5], int a_imag[5][5]) {
    int i;
    int j;
    int a_ah_real[5][5];
    int a_ah_imag[5][5];
    int ah_a_real[5][5];
    int ah_a_imag[5][5];
    int b_real[5][5];
    int b_imag[5][5];
    
    if (a_rows != a_cols) {
        return 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            b_real[i][j] = a_real[j][i];
            b_imag[i][j] = -a_imag[j][i];
        }
    }
    
    multiply(a_rows, a_cols, a_real, a_imag, a_cols, a_rows, b_real, b_imag, a_ah_real, a_ah_imag);
    multiply(a_cols, a_rows, b_real, b_imag, a_rows, a_cols, a_real, a_imag, ah_a_real, ah_a_imag);
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            if (a_ah_real[i][j] != ah_a_real[i][j] || a_ah_imag[i][j] != ah_a_imag[i][j]) {
                return 0;
            }
        }
    }
    
    return 1;
}

int isUnitary(int a_rows, int a_cols, int a_real[5][5], int a_imag[5][5]) {
    int i;
    int j;
    int b_real[5][5];
    int b_imag[5][5];
    int c_real[5][5];
    int c_imag[5][5];
    
    if (isNormal(a_rows, a_cols, a_real, a_imag) == 1) {
        for (i = 0; i < 5; i = i + 1) {
            for (j = 0; j < 5; j = j + 1) {
                b_real[i][j] = a_real[j][i];
                b_imag[i][j] = -a_imag[j][i];
            }
        }
        
        multiply(a_rows, a_cols, a_real, a_imag, a_cols, a_rows, b_real, b_imag, c_real, c_imag);
        
        for (i = 0; i < 5; i = i + 1) {
            for (j = 0; j < 5; j = j + 1) {
                if ((i == j && (c_real[i][j] != 1 || c_imag[i][j] != 0)) || (i != j && (c_real[i][j] != 0 || c_imag[i][j] != 0))) {
                    return 0;
                }
            }
        }
        return 1;
    }
    
    return 0;
}

void transpose(int a_rows, int a_cols, int a_real[5][5], int a_imag[5][5], int b_real[5][5], int b_imag[5][5]) {
    int i;
    int j;
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            b_real[i][j] = a_real[j][i];
            b_imag[i][j] = -a_imag[j][i];
        }
    }
    
    return;
}
