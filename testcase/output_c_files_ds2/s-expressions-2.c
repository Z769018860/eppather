void parse_example(int max_depth) {
    int tokens[5][5] = {0};
    int depth[5] = {0};
    int i;
    int j;
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            tokens[i][j] = 0;
        }
        depth[i] = 0;
    }
    
    depth[0] = 0;
    tokens[0][0] = 40;
    tokens[0][1] = 40;
    tokens[0][2] = 100;
    tokens[0][3] = 97;
    tokens[0][4] = 116;
    
    depth[1] = 1;
    tokens[1][0] = 97;
    tokens[1][1] = 100;
    tokens[1][2] = 97;
    tokens[1][3] = 92;
    tokens[1][4] = 40;
    
    depth[2] = 1;
    tokens[2][0] = 34;
    tokens[2][1] = 113;
    tokens[2][2] = 117;
    tokens[2][3] = 111;
    tokens[2][4] = 116;
    
    depth[3] = 1;
    tokens[3][0] = 49;
    tokens[3][1] = 50;
    tokens[3][2] = 51;
    tokens[3][3] = 0;
    tokens[3][4] = 0;
    
    depth[4] = 1;
    tokens[4][0] = 52;
    tokens[4][1] = 46;
    tokens[4][2] = 53;
    tokens[4][3] = 0;
    tokens[4][4] = 0;
    
    return;
}
