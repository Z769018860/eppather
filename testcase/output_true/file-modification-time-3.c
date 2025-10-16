void rewrite_function() {
    int foo[5];
    int new_times[2][5];
    int filename[5];
    int i;
    int j;
    
    for (i = 0; i < 5; i = i + 1) {
        filename[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        foo[i] = 0;
    }
    
    for (i = 0; i < 2; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            new_times[i][j] = 0;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        new_times[0][i] = foo[i];
    }
    
    return;
}
