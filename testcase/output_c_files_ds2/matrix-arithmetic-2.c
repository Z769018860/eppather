int det(int in[5], int n) {
    int m[5][5];
    int i;
    int j;
    int k;
    int sign;
    int max;
    int row;
    int col;
    int tmp;
    int p;
    int r;
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            m[i][j] = in[i * 5 + j];
        }
    }
    
    sign = 1;
    for (i = 0; i < 5; i = i + 1) {
        max = 0;
        
        for (row = i; row < 5; row = row + 1) {
            if ((m[row][i] > 0 ? m[row][i] : -m[row][i]) > (m[max][i] > 0 ? m[max][i] : -m[max][i])) {
                max = row;
            }
        }
        
        if (max != 0) {
            sign = -sign;
            for (k = 0; k < 5; k = k + 1) {
                tmp = m[i][k];
                m[i][k] = m[max][k];
                m[max][k] = tmp;
            }
        }
        
        if (m[i][i] == 0) {
            return 0;
        }
        
        for (row = i + 1; row < 5; row = row + 1) {
            r = m[row][i] / m[i][i];
            if (r != 0) {
                for (col = i; col < 5; col = col + 1) {
                    m[row][col] = m[row][col] - m[i][col] * r;
                }
            }
        }
    }
    
    p = 1;
    for (i = 0; i < 5; i = i + 1) {
        p = p * m[i][i];
    }
    
    return p * sign;
}
