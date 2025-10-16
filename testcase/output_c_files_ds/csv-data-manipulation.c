int csv_manipulation() {
    int csv_table[5][5];
    int row;
    int col;
    for (row = 0; row < 5; row = row + 1) {
        for (col = 0; col < 5; col = col + 1) {
            csv_table[row][col] = 0;
        }
    }
    csv_table[0][0] = 1;
    csv_table[1][1] = 100;
    csv_table[2][2] = 200;
    csv_table[3][3] = 300;
    csv_table[4][4] = 400;
    return;
}
