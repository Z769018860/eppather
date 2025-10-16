int eq_idx(int *a, int len, int *ret, int ret_len) {
    int i;
    int sum;
    int s;
    int cnt;
    cnt = 0;
    s = 0;
    sum = 0;
    
    for (i = 0; i < len; i = i + 1) {
        sum = sum + a[i];
    }
    
    for (i = 0; i < len; i = i + 1) {
        if (s * 2 + a[i] == sum) {
            if (cnt < ret_len) {
                ret[cnt] = i;
            }
            cnt = cnt + 1;
        }
        s = s + a[i];
    }
    
    return cnt;
}
