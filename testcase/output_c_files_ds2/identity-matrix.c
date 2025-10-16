void identitymatrix(int rowsize) {
    int numElements[5];
    numElements[0] = rowsize * rowsize;
    int matrix[5][5];
    for (int row = 0; row < 5; row = row + 1) {
        for (int column = 0; column < 5; column = column + 1) {
            matrix[row][column] = 0;
        }
    }
    for (int row = 0; row < 5; row = row + 1) {
        matrix[row][row] = 1;
    }
    return;
}
