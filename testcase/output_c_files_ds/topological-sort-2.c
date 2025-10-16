void compile_order() {
    int order[4][5] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    int cycle_21 = 0;
    int cycle_22 = 0;
    int cycle_11 = 0;
    int cycle_12 = 0;
    
    for (int i = 0; i < 5; i = i + 1) {
        order[0][i] = 0;
    }
    
    order[1][0] = 1;
    order[1][1] = 1;
    order[1][2] = 1;
    order[1][3] = 1;
    order[1][4] = 1;
    
    order[2][0] = 1;
    order[2][1] = 1;
    order[2][2] = 1;
    order[2][3] = 1;
    order[2][4] = 1;
    
    order[3][0] = 1;
    order[3][1] = 1;
    order[3][2] = 1;
    
    return;
}
