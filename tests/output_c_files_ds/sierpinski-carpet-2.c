void SierpinskiTile(int d_data[729], int d_rows[27], int s_data[1], int s_rows[1], int n) {
    int sub_data[243];
    int sub_rows[9];
    int row;
    int col;
    int rb;
    int spc_rqrd;
    int k;
    int m;
    int y0;
    int x0;
    
    if (n > 1) {
        SierpinskiTile(sub_data, sub_rows, s_data, s_rows, n - 1);
    }
    else {
        sub_data[0] = s_data[0];
        sub_rows[0] = sub_data[0];
    }
    
    for (row = 0; row < 27; row = row + 1) {
        d_rows[row] = row * 27;
    }
    
    for (col = 0; col < 3; col = col + 1) {
        for (row = 0; row < 2; row = row + 1) {
            y0 = (n > 1 ? 9 : 1) * row;
            x0 = (n > 1 ? 9 : 1) * col;
            if ((row == 1) && (col == 1)) {
                for (k = 0; k < (n > 1 ? 9 : 1); k = k + 1) {
                    for (m = 0; m < (n > 1 ? 9 : 1); m = m + 1) {
                        d_data[d_rows[y0 + k] + x0 + m] = 0;
                    }
                }
            }
            else {
                for (k = 0; k < (n > 1 ? 9 : 1); k = k + 1) {
                    for (m = 0; m < (n > 1 ? 9 : 1); m = m + 1) {
                        d_data[d_rows[y0 + k] + x0 + m] = sub_data[sub_rows[k] + m];
                    }
                }
            }
        }
    }
    return;
}
