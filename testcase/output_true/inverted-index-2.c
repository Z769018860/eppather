int search_function(int query, int file1, int file2, int file3) {
    int result[5];
    result[0] = 0;
    result[1] = 0;
    result[2] = 0;
    result[3] = 0;
    result[4] = 0;
    
    if (query == 0) {
        result[0] = file1;
        result[1] = file2;
    }
    else if (query == 1) {
        result[0] = file1;
        result[1] = file3;
        result[2] = file2;
    }
    else if (query == 2) {
        result[0] = file3;
    }
    else {
        for (int i = 0; i < 5; i = i + 1) {
            result[i] = 0;
        }
    }
    
    return;
}
