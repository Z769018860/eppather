int func(int user1) {
    int space_needed;
    int a1[100];
    int array[100];
    int row;
    int col;
    int offset;
    
    space_needed = (user1 + 1) * user1 / 2;
    for (row = 0, offset = 0; row < user1; row = row + 1) {
        array[row] = a1 + offset - row;
        for (col = row; col < user1; col = col + 1) {
            array[row][col] = 1 + col - row;
        }
        offset = offset + (user1 - row);
    }
    return array[user1 - 1][user1 - 1];
}
