void RS_append(int rs_buf[5], int rs_len[5], int ss_buf[5], int ss_len[5]) {
    int n[5];
    n[0] = rs_len[0];
    int r[5];
    r[0] = rs_buf[n[0]-1] + ss_buf[n[0]-1];
    int s[5];
    s[0] = ss_buf[ss_len[0]-1];
    rs_buf[rs_len[0]] = r[0];
    rs_len[0] = rs_len[0] + 1;
    s[0] = s[0] + 1;
    for (int i = 0; i < 5; i = i + 1) {
        if (s[0] < r[0]) {
            ss_buf[ss_len[0]] = s[0];
            ss_len[0] = ss_len[0] + 1;
            s[0] = s[0] + 1;
        }
    }
    ss_buf[ss_len[0]] = r[0] + 1;
    ss_len[0] = ss_len[0] + 1;
    return;
}
