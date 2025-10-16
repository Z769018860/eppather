int hailstone(int jobs_param) {
    int env_seq[12];
    int env_cnt[12];
    int seq;
    int cnt;
    int i;
    int j;
    int k;
    
    for (i = 0; i < jobs_param; i = i + 1) {
        env_seq[i] = i + 1;
        env_cnt[i] = 0;
    }
    
    for (k = 0; k < 5; k = k + 1) {
        for (i = 0; i < jobs_param; i = i + 1) {
            seq = env_seq[i];
            cnt = env_cnt[i];
            
            if (seq == 1) {
                continue;
            }
            cnt = cnt + 1;
            if ((seq & 1) == 1) {
                seq = 3 * seq + 1;
            } else {
                seq = seq / 2;
            }
            env_seq[i] = seq;
            env_cnt[i] = cnt;
        }
        
        for (j = 0; j < jobs_param; j = j + 1) {
            if (env_seq[j] != 1) {
                k = 0;
                break;
            }
        }
    }
    
    return;
}
