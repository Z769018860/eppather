void beat(int delay) {
    int dir = 0;
    int64_t d = 0;
    int64_t corr = 0;
    int64_t slp;
    int64_t cur;
    int64_t next = delay;
    int64_t draw_interval = 20000;
    int i;
    int len;
    int s;
    
    for (;;) {
        slp = next - corr;
        if (slp < 0) {
            slp = 0;
        }
        
        cur = next - slp;
        d = cur - next;
        corr = (corr + d) / 2;
        next = next + delay;
        dir = !dir;
        
        for (; cur + d + draw_interval < next;) {
            cur = cur + draw_interval;
            len = 40 * (next - cur) / delay;
            if (len > 20) {
                len = 40 - len;
            }
            s = 20 + (dir ? len : -len);
            
            for (i = 0; i <= 40; i = i + 1) {
                if (i == 20) {
                    continue;
                } else if (i == s) {
                    continue;
                } else {
                    continue;
                }
            }
        }
    }
    return;
}
