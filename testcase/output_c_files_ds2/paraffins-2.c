void calc_unrooted(int n, int max_branch, int max_n) {
    int bcache[501][1];
    int ucache[501][1];
    int rcache[501][5][500][1];
    int tmp1[1];
    int tmp2[1];
    int rtmp1[1];
    int rtmp2[1];
    
    int i;
    int b;
    int r;
    int b1;
    int r1;
    
    for (i = 0; i < 501; i = i + 1) {
        bcache[i][0] = 0;
        ucache[i][0] = 0;
    }
    
    for (i = 0; i < 501; i = i + 1) {
        for (b = 0; b < 5; b = b + 1) {
            for (r = 0; r < 500; r = r + 1) {
                rcache[i][b][r][0] = 0;
            }
        }
    }
    
    tmp1[0] = 0;
    tmp2[0] = 0;
    rtmp1[0] = 0;
    rtmp2[0] = 0;
    
    for (i = 1; i < 5; i = i + 1) {
        for (b = 0; b < 5; b = b + 1) {
            for (r = 0; r < 500; r = r + 1) {
                if (i == 1 && b == 0 && r == 0) {
                    rcache[i][b][r][0] = 1;
                } else if (i <= b || i <= r || i == 1 || b == 0 || r == 0) {
                    rcache[i][b][r][0] = 0;
                } else {
                    rcache[i][b][r][0] = 0;
                    for (b1 = 1; b1 <= b && r * b1 < i; b1 = b1 + 1) {
                        rtmp1[0] = bcache[r][0];
                        for (int k = 1; k < b1; k = k + 1) {
                            rtmp1[0] = rtmp1[0] * (bcache[r][0] + 1);
                            rtmp1[0] = rtmp1[0] / (k + 1);
                        }
                        rtmp2[0] = 0;
                        for (r1 = 0; r1 < r && r1 + r * b1 < i; r1 = r1 + 1) {
                            rtmp2[0] = rtmp2[0] + rcache[i - r * b1][b - b1][r1][0];
                        }
                        rcache[i][b][r][0] = rcache[i][b][r][0] + rtmp1[0] * rtmp2[0];
                    }
                }
            }
        }
        
        for (b = 0; b < 5; b = b + 1) {
            for (r = 0; r < 500; r = r + 1) {
                bcache[i][0] = bcache[i][0] + rcache[i][b][r][0];
            }
        }
        
        for (r = 0; r * 2 < i; r = r + 1) {
            for (b = 0; b < 5; b = b + 1) {
                ucache[i][0] = ucache[i][0] + rcache[i][b][r][0];
            }
        }
        
        if ((i % 2) == 0) {
            rtmp1[0] = bcache[i / 2][0] + 1;
            rtmp1[0] = rtmp1[0] * bcache[i / 2][0];
            rtmp1[0] = rtmp1[0] / 2;
            ucache[i][0] = ucache[i][0] + rtmp1[0];
        }
    }
    return;
}
