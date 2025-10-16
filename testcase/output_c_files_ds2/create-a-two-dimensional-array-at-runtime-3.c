void func(int user1, int user2) {
    int a1[5][5];
    int array[5][5];
    int row;
    int col;
    
    for (row = 0; row < 5; row = row + 1) {
        for (col = 0; col < 5; col = col + 1) {
            a1[row][col] = 0;
            array[row][col] = 0;
        }
    }
    
    array[user1 / 2][user2 / 2] = user1 + user2;
    return;
}
