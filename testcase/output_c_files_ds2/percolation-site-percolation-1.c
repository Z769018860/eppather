int percolate(int m, int n, int p) {
    int cell[5];
    int start[5];
    int end[5];
    int thresh[5];
    int i[5];
    int j[5];
    int cnt[5];
    int ip[5];
    
    thresh[0] = p * 32767;
    m = 5;
    n = 5;
    
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        start[i[0]] = 0;
    }
    
    cell[0] = 0;
    end[0] = 0;
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        for (j[0] = 0; j[0] < 5; j[0] = j[0] + 1) {
            if (rand() < thresh[0]) {
                cell[0] = 1;
            } else {
                cell[0] = 0;
            }
        }
    }
    
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        if (cell[i[0]] != 1) {
            cell[i[0]] = 2;
        }
    }
    
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        if (i[0] < m && cell[i[0]] == 2) {
            cnt[0] = cnt[0] + 1;
        }
    }
    
    for (ip[0] = 0; ip[0] <= 10; ip[0] = ip[0] + 1) {
        p = ip[0] / 10;
        cnt[0] = 0;
        for (i[0] = 0; i[0] < 10000; i[0] = i[0] + 1) {
            cnt[0] = cnt[0] + (cell[0] == 2 ? 1 : 0);
        }
    }
    
    return cnt[0];
}
