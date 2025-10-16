void process_licenses(int fd, int st_size) {
    int cnt[5];
    int max_cnt[5];
    int occur[5];
    char buf[5][26];
    char ptr[5];
    int i;
    int j;
    
    cnt[0] = 0;
    max_cnt[0] = 0;
    occur[0] = 0;
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 26; j = j + 1) {
            buf[i][j] = 0;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        ptr[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (ptr[i] == 'L' && ptr[i + 1] == 'i' && ptr[i + 2] == 'c' && ptr[i + 3] == 'e' && ptr[i + 4] == 'n' && ptr[i + 5] == 's' && ptr[i + 6] == 'e' && ptr[i + 7] == ' ' && ptr[i + 8] == 'O' && ptr[i + 9] == 'U' && ptr[i + 10] == 'T') {
            cnt[0] = cnt[0] + 1;
            if (cnt[0] > max_cnt[0]) {
                max_cnt[0] = cnt[0];
                occur[0] = 0;
            }
            for (j = 0; j < 19; j = j + 1) {
                buf[occur[0]][j] = ptr[i + 14 + j];
            }
            occur[0] = occur[0] + 1;
        } else if (ptr[i] == 'L' && ptr[i + 1] == 'i' && ptr[i + 2] == 'c' && ptr[i + 3] == 'e' && ptr[i + 4] == 'n' && ptr[i + 5] == 's' && ptr[i + 6] == 'e' && ptr[i + 7] == ' ' && ptr[i + 8] == 'I' && ptr[i + 9] == 'N' && ptr[i + 10] == ' ') {
            cnt[0] = cnt[0] - 1;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (ptr[i] != '\n') {
            ptr[i] = ptr[i + 1];
        }
    }
    
    return;
}
