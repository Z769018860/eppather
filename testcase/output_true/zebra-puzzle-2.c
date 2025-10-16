int solve_zebra_puzzle(int nationality, int pet, int drink, int smoke, int color) {
    int house[5][5];
    int i;
    int j;
    int k;
    int l;
    int m;
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            house[i][j] = 0;
        }
    }
    
    house[0][0] = 3;
    house[2][3] = 2;
    
    for (i = 0; i < 5; i = i + 1) {
        if (house[i][0] == 1) {
            house[i][1] = 0;
        }
        if (house[i][0] == 4) {
            house[i][1] = 0;
        }
        if (house[i][1] == 0) {
            house[i][0] = 1;
        }
        if (house[i][1] == 4) {
            house[i][0] = 4;
        }
        if (house[i][2] == 2) {
            house[i][3] = 3;
        }
        if (house[i][3] == 0) {
            house[i][2] = 2;
        }
        if (house[i][4] == 1) {
            house[i][1] = 2;
        }
        if (house[i][1] == 2) {
            house[i][4] = 1;
        }
        if (house[i][3] == 1) {
            house[i][4] = 4;
        }
        if (house[i][4] == 4) {
            house[i][3] = 1;
        }
        if (house[i][2] == 3) {
            house[i][0] = 0;
        }
        if (house[i][0] == 0) {
            house[i][2] = 3;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            if (house[i][j] == 0) {
                for (k = 0; k < 5; k = k + 1) {
                    if (house[i][k] != 0) {
                        continue;
                    }
                    for (l = 0; l < 5; l = l + 1) {
                        if (house[l][k] != 0) {
                            continue;
                        }
                        for (m = 0; m < 5; m = m + 1) {
                            if (house[l][m] != 0) {
                                continue;
                            }
                            house[i][j] = k + 1;
                            house[l][k] = m + 1;
                        }
                    }
                }
            }
        }
    }
    
    return;
}
