int process_license_data() {
    int cnt;
    int max_cnt;
    int occur;
    int fd;
    int s_st_size;
    char buf[10000];
    char ptr[10000];
    int i;
    int j;
    int k;
    int match;
    
    cnt = 0;
    max_cnt = 0;
    occur = 0;
    s_st_size = 10000;
    
    for (i = 0; i < s_st_size - 33; i = i + 1) {
        match = 1;
        for (j = 0; j < 11; j = j + 1) {
            if (ptr[i + j] != "License OUT"[j]) {
                match = 0;
                break;
            }
        }
        if (match == 1) {
            cnt = cnt + 1;
            if (cnt > max_cnt) {
                max_cnt = cnt;
                occur = 0;
            }
            if (cnt >= max_cnt) {
                for (k = 0; k < 19; k = k + 1) {
                    buf[26 * occur + k] = ptr[i + 14 + k];
                }
                occur = occur + 1;
            }
        } else {
            match = 1;
            for (j = 0; j < 11; j = j + 1) {
                if (ptr[i + j] != "License IN "[j]) {
                    match = 0;
                    break;
                }
            }
            if (match == 1) {
                cnt = cnt - 1;
            }
        }
        
        while (i < s_st_size) {
            if (ptr[i] == '\n') {
                i = i + 1;
                break;
            }
            i = i + 1;
        }
    }
    
    return;
}
