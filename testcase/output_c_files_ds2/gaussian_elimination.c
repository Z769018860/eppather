void gaussian_elimination_gauss_jordan_back_substitution(int rows, int cols, int a[5][5], int x[5]) {
    int row = 0;
    int col = 0;
    int pivot = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int tmp = 0;
    int scale = 0;
    int sum = 0;
    
    for (col = 0; col < cols - 1; col = col + 1) {
        pivot = row;
        
        for (i = row + 1; i < rows; i = i + 1) {
            if ((a[i][col] > 0 ? a[i][col] : -a[i][col]) > (a[pivot][col] > 0 ? a[pivot][col] : -a[pivot][col])) {
                pivot = i;
            }
        }
        
        if (a[pivot][col] == 0) {
            continue;
        }
        
        if (col != pivot) {
            for (j = 0; j < cols; j = j + 1) {
                tmp = a[col][j];
                a[col][j] = a[pivot][j];
                a[pivot][j] = tmp;
            }
        }
        
        for (i = row + 1; i < rows; i = i + 1) {
            scale = a[i][col] / a[row][col];
            
            for (j = col + 1; j < cols; j = j + 1) {
                a[i][j] = a[i][j] - a[row][j] * scale;
            }
            
            a[i][col] = 0;
        }
        
        row = row + 1;
    }
    
    row = 0;
    
    for (col = 0; col < cols - 1; col = col + 1) {
        if (a[row][col] != 0) {
            for (i = cols - 1; i > col - 1; i = i - 1) {
                a[row][i] = a[row][i] / a[row][col];
            }
            
            for (i = 0; i < row; i = i + 1) {
                for (j = cols - 1; j > col - 1; j = j - 1) {
                    a[i][j] = a[i][j] - a[i][col] * a[row][j];
                }
            }
            
            row = row + 1;
        }
    }
    
    for (i = rows - 1; i >= 0; i = i - 1) {
        sum = 0;
        
        for (j = cols - 2; j > i; j = j - 1) {
            sum = sum + x[j] * a[i][j];
        }
        
        x[i] = (a[i][cols - 1] - sum) / a[i][i];
    }
    
    return;
}
