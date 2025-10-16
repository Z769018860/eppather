void next_cell(int res[4]) {
    int supply[4] = {50, 60, 50, 50};
    int demand[5] = {30, 20, 70, 30, 60};
    int costs[4][5] = {{16, 16, 13, 22, 17}, {14, 14, 13, 19, 15}, {19, 19, 20, 23, 50}, {50, 12, 50, 15, 11}};
    int row_done[4] = {0, 0, 0, 0};
    int col_done[5] = {0, 0, 0, 0, 0};
    int res1[4];
    int res2[4];
    int i;
    int j;
    int min1;
    int min2;
    int min_p;
    int c;
    int pc;
    int pm;
    int mc;
    int md;
    int res2_temp[3];
    int k;
    int l;
    int res1_temp[3];
    
    for (i = 0; i < 4; i = i + 1) {
        if (row_done[i] != 0) {
            continue;
        }
        min1 = 2147483647;
        min2 = 2147483647;
        min_p = -1;
        for (j = 0; j < 5; j = j + 1) {
            if (col_done[j] != 0) {
                continue;
            }
            c = costs[i][j];
            if (c < min1) {
                min2 = min1;
                min1 = c;
                min_p = j;
            }
            else {
                if (c < min2) {
                    min2 = c;
                }
            }
        }
        res1_temp[0] = min2 - min1;
        res1_temp[1] = min1;
        res1_temp[2] = min_p;
        if (res1_temp[0] > md) {
            md = res1_temp[0];
            pm = i;
            mc = res1_temp[1];
            pc = res1_temp[2];
        }
    }
    res1[0] = pm;
    res1[1] = pc;
    res1[2] = mc;
    res1[3] = md;
    
    md = -2147483648;
    for (i = 0; i < 5; i = i + 1) {
        if (col_done[i] != 0) {
            continue;
        }
        min1 = 2147483647;
        min2 = 2147483647;
        min_p = -1;
        for (j = 0; j < 4; j = j + 1) {
            if (row_done[j] != 0) {
                continue;
            }
            c = costs[j][i];
            if (c < min1) {
                min2 = min1;
                min1 = c;
                min_p = j;
            }
            else {
                if (c < min2) {
                    min2 = c;
                }
            }
        }
        res2_temp[0] = min2 - min1;
        res2_temp[1] = min1;
        res2_temp[2] = min_p;
        if (res2_temp[0] > md) {
            md = res2_temp[0];
            pm = i;
            mc = res2_temp[1];
            pc = res2_temp[2];
        }
    }
    res2[0] = pc;
    res2[1] = pm;
    res2[2] = mc;
    res2[3] = md;
    
    if (res1[3] == res2[3]) {
        if (res1[2] < res2[2]) {
            for (i = 0; i < 4; i = i + 1) {
                res[i] = res1[i];
            }
        }
        else {
            for (i = 0; i < 4; i = i + 1) {
                res[i] = res2[i];
            }
        }
        return;
    }
    if (res1[3] > res2[3]) {
        for (i = 0; i < 4; i = i + 1) {
            res[i] = res2[i];
        }
    }
    else {
        for (i = 0; i < 4; i = i + 1) {
            res[i] = res1[i];
        }
    }
    return;
}
