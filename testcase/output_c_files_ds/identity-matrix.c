int identitymatrix(int rowsize) {
    int matrix[100][100];
    int numElements;
    int row;
    int column;
    
    if (rowsize < 0) {
        return;
    }
    
    numElements = rowsize * rowsize;
    if (numElements < rowsize) {
        return;
    }
    
    for (row = 0; row < rowsize; row = row + 1) {
        for (column = 0; column < rowsize; column = column + 1) {
            matrix[row][column] = 0;
        }
    }
    
    for (row = 0; row < rowsize; row = row + 1) {
        matrix[row][row] = 1;
    }
    
    return;
}
