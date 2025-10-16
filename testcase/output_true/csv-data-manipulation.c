int csv_manipulation(int cols, int rows) {
    int csv_table[5][5];
    int cur_col;
    int cur_row;
    int max_cols;
    int max_rows;
    int new_cols;
    int new_rows;
    int in_old;
    int in_new;
    
    for (cur_col = 0; cur_col < 5; cur_col = cur_col + 1) {
        for (cur_row = 0; cur_row < 5; cur_row = cur_row + 1) {
            csv_table[cur_col][cur_row] = 0;
        }
    }
    
    new_cols = cols;
    new_rows = rows;
    max_cols = (new_cols > cols) ? new_cols : cols;
    max_rows = (new_rows > rows) ? new_rows : rows;
    
    for (cur_col = 0; cur_col < max_cols; cur_col = cur_col + 1) {
        for (cur_row = 0; cur_row < max_rows; cur_row = cur_row + 1) {
            in_old = (cur_col < cols) && (cur_row < rows);
            in_new = (cur_col < new_cols) && (cur_row < new_rows);
            
            if (in_old && in_new) {
                csv_table[cur_col][cur_row] = csv_table[cur_col][cur_row];
            } else {
                csv_table[cur_col][cur_row] = 0;
            }
        }
    }
    
    return;
}
