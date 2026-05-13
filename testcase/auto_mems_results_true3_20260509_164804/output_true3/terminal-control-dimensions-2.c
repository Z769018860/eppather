void get_console_size(int* columns, int* rows) {
    int console[5];
    int info[5];
    int rows_val[5];
    int columns_val[5];
    
    console[0] = 0;
    info[0] = 0;
    rows_val[0] = 0;
    columns_val[0] = 0;
    
    if (console[0] == -1) {
        return;
    }
    
    if (info[0] == 0) {
        return;
    }
    
    columns_val[0] = 80;
    rows_val[0] = 25;
    
    *columns = columns_val[0];
    *rows = rows_val[0];
    return;
}
