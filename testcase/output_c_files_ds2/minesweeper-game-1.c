int autoplay(int bd[5][5], int RWS, int CLS, int row, int col) {
    int i;
    int j;
    int k;
    int change;
    int m;
    int neighbor_i[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int neighbor_j[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    
    if ((bd[row+1][col+1] & (1 << 2)) != 0) {
        return 1;
    }
    if ((bd[row+1][col+1] & (1 << 0)) != 0) {
        return 0;
    }
    bd[row+1][col+1] = bd[row+1][col+1] & ~(1 << 1);
    
    for (i = 0; i < 5; i = i + 1) {
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
                    int flags = 0;
                    for (k = 0; k < 8; k = k + 1) {
                        if ((bd[i+neighbor_i[k]][j+neighbor_j[k]] & (1 << 2)) != 0) {
                            flags = flags + 1;
                        }
                    }
                    if (flags == m) {
                        for (k = 0; k < 8; k = k + 1) {
                            if (((bd[i+neighbor_i[k]][j+neighbor_j[k]] & (1 << 1)) != 0) && 
                                ((bd[i+neighbor_i[k]][j+neighbor_j[k]] & (1 << 2)) == 0)) {
                                if ((bd[i+neighbor_i[k]][j+neighbor_j[k]] & (1 << 0)) != 0) {
                                    row = i + neighbor_i[k] - 1;
                                    col = j + neighbor_j[k] - 1;
                                    return 0;
                                }
                                change = 1;
                                bd[i+neighbor_i[k]][j+neighbor_j[k]] = bd[i+neighbor_i[k]][j+neighbor_j[k]] & ~(1 << 1);
                            }
                        }
                    } else {
                        int unknowns = 0;
                        for (k = 0; k < 8; k = k + 1) {
                            if ((bd[i+neighbor_i[k]][j+neighbor_j[k]] & (1 << 1)) != 0) {
                                unknowns = unknowns + 1;
                            }
                        }
                        if (unknowns == m) {
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
    }
    return 1;
}
