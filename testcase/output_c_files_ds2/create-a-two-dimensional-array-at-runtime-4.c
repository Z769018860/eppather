void func(int user1) {
    int a1[5];
    int array[5][5];
    int row;
    int col;
    int offset;
    int space_needed;
    int n1;
    int n2;
    
    n1 = user1;
    space_needed = (n1 + 1) * n1 / 2;
    for (row = 0, offset = 0; row < n1; offset = offset + (n1 - row), row = row + 1) {
        n2 = offset - row;
        for (col = row; col < n1; col = col + 1) {
            array[row][col] = 1 + col - row;
        }
    }
    for (row = 0; row < n1; row = row + 1) {
        n2 = array[row][n1 - 1];
    }
    return;
}
