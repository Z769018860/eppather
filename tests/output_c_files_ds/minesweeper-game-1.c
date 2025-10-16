int autoplay(int bd[22][32], int RWS, int CLS, int row, int col) {
    int i;
    int j;
    int k;
    int change;
    int m;
    int neighbor_i[8] = {-1,-1,-1,0,0,1,1,1};
    int neighbor_j[8] = {-1,0,1,-1,1,-1,0,1};
    
    if ((bd[row+1][col+1] & (1 << 1)) == 0) {
        if ((bd[row+1][col+1] & (1 << 0)) != 0) {
            return 0;
        }
        bd[row+1][col+1] = bd[row+1][col+1] & (~(1 << 1));
    }
    
    do {
        change = 0;
        for (i = 1; i < RWS; i = i + 1) {
            for (j = 1; j < CLS; j = j + 1) {
                if ((bd[i][j] & (1 << 1)) == 0) {
                    m = 0;
                    for (k = 0; k < 8; k = k + 1) {
                        if ((bd[i+neighbor_i[k]][j+neighbor_j[k]] & (1 << 0)) != 0) {
                            m = m + 1;
                        }
                    }
                    int flagged = 0;
                    for (k = 0; k < 8; k = k + 1) {
                        if ((bd[i+neighbor_i[k]][j+neighbor_j[k]] & (1 << 2)) != 0) {
                            flagged = flagged + 1;
                        }
                    }
                    if (flagged == m) {
                        for (k = 0; k < 8; k = k + 1) {
                            if ((bd[i+neighbor_i[k]][j+neighbor_j[k]] & (1 << 1)) != 0 && (bd[i+neighbor_i[k]][j+neighbor_j[k]] & (1 << 2)) == 0) {
                                if ((bd[i+neighbor_i[k]][j+neighbor_j[k]] & (1 << 0)) != 0) {
                                    row = i + neighbor_i[k] - 1;
                                    col = j + neighbor_j[k] - 1;
                                    return 0;
                                }
                                change = 1;
                                bd[i+neighbor_i[k]][j+neighbor_j[k]] = bd[i+neighbor_i[k]][j+neighbor_j[k]] & (~(1 << 1));
                            }
                        }
                    } else {
                        int unknown = 0;
                        for (k = 0; k < 8; k = k + 1) {
                            if ((bd[i+neighbor_i[k]][j+neighbor_j[k]] & (1 << 1)) != 0) {
                                unknown = unknown + 1;
                            }
                        }
                        if (unknown == m) {
                            for (k = 0; k < 8; k = k + 1) {
                                if ((bd[i+neighbor_i[k]][j+neighbor_j[k]] & (1 << 1)) != 0) {
                                    change = 1;
                                    bd[i+neighbor_i[k]][j+neighbor_j[k]] = bd[i+neighbor_i[k]][j+neighbor_j[k]] | (1 << 2);
                                }
                            }
                        }
                    }
                }
            }
        }
    } while (change != 0);
    return 1;
}

return;
