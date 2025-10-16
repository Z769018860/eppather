int rs_buf[1000];
int ss_buf[1000];
int rs_len = 0;
int ss_len = 0;
int rs_alloc = 0;
int ss_alloc = 0;

void RS_append(void);

int R(int n) {
    for (; n > rs_len; ) {
        RS_append();
    }
    return rs_buf[n - 1];
}

int S(int n) {
    for (; n > ss_len; ) {
        RS_append();
    }
    return ss_buf[n - 1];
}

void RS_append() {
    int n = rs_len;
    int r = R(n) + S(n);
    int s = S(ss_len);
    int i = 0;

    if (rs_alloc <= rs_len) {
        int new_alloc = rs_alloc;
        if (new_alloc == 0) {
            new_alloc = 1;
        }
        for (; new_alloc <= rs_len; ) {
            new_alloc = new_alloc * 2;
        }
        rs_alloc = new_alloc;
    }
    rs_buf[rs_len] = r;
    rs_len = rs_len + 1;

    s = s + 1;
    for (; s < r; s = s + 1) {
        if (ss_alloc <= ss_len) {
            int new_alloc = ss_alloc;
            if (new_alloc == 0) {
                new_alloc = 1;
            }
            for (; new_alloc <= ss_len; ) {
                new_alloc = new_alloc * 2;
            }
            ss_alloc = new_alloc;
        }
        ss_buf[ss_len] = s;
        ss_len = ss_len + 1;
    }

    if (ss_alloc <= ss_len) {
        int new_alloc = ss_alloc;
        if (new_alloc == 0) {
            new_alloc = 1;
        }
        for (; new_alloc <= ss_len; ) {
            new_alloc = new_alloc * 2;
        }
        ss_alloc = new_alloc;
    }
    ss_buf[ss_len] = r + 1;
    ss_len = ss_len + 1;
    return;
}
