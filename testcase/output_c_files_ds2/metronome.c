void beat(int delay, int draw_interval) {
    int tv_sec[5] = {0};
    int tv_usec[5] = {0};
    int dir[5] = {0};
    int d[5] = {0};
    int corr[5] = {0};
    int slp[5] = {0};
    int cur[5] = {0};
    int next[5] = {0};
    int len[5] = {0};
    int s[5] = {0};
    int i[5] = {0};
    
    next[0] = tv_sec[0] * 1000000 + tv_usec[0] + delay;
    for (;;) {
        slp[0] = next[0] - (tv_sec[0] * 1000000 + tv_usec[0]) - corr[0];
        cur[0] = tv_sec[0] * 1000000 + tv_usec[0];
        d[0] = cur[0] - next[0];
        corr[0] = (corr[0] + d[0]) / 2;
        next[0] = next[0] + delay;
        dir[0] = !dir[0];
        
        for (;;) {
            if (cur[0] + d[0] + draw_interval >= next[0]) {
                break;
            }
            cur[0] = tv_sec[0] * 1000000 + tv_usec[0];
            len[0] = 40 * (next[0] - cur[0]) / delay;
            if (len[0] > 20) {
                len[0] = 40 - len[0];
            }
            s[0] = 20 + (dir[0] ? len[0] : -len[0]);
            for (i[0] = 0; i[0] <= 40; i[0] = i[0] + 1) {
                if (i[0] == 20) {
                } else if (i[0] == s[0]) {
                } else {
                }
            }
        }
    }
    return;
}
