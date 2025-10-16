void compile_order(int cycle_21, int cycle_22, int cycle_11, int cycle_12) {
    int order[4][5] = {
        {1, 0, 0, 0, 0},
        {2, 0, 0, 0, 0},
        {3, 0, 0, 0, 0},
        {4, 0, 0, 0, 0}
    };
    int i;
    int j;
    
    for (i = 0; i < 4; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            if (i == 0 && j == 0) {
                order[i][j] = 1;
            }
            if (i == 1 && j == 0) {
                order[i][j] = 2;
            }
            if (i == 2 && j == 0) {
                order[i][j] = 3;
            }
            if (i == 3 && j == 0) {
                order[i][j] = 4;
            }
        }
    }
    return;
}
