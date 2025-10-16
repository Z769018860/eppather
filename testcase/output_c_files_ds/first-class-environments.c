int hailstone(int seq, int cnt) {
    int result[2];
    result[0] = seq;
    result[1] = cnt;
    if (seq == 1) {
        return result[1];
    }
    result[1] = result[1] + 1;
    if ((seq & 1) == 1) {
        result[0] = 3 * seq + 1;
    } else {
        result[0] = seq / 2;
    }
    return result[1];
}

void process_jobs() {
    int env_seq[12];
    int env_cnt[12];
    int seq;
    int cnt;
    int i;
    int j;
    int temp;
    
    for (i = 0; i < 12; i = i + 1) {
        env_seq[i] = i + 1;
        env_cnt[i] = 0;
    }
    
    for (j = 0; j < 12; j = j + 1) {
        seq = env_seq[j];
        cnt = env_cnt[j];
        cnt = hailstone(seq, cnt);
        env_seq[j] = seq;
        env_cnt[j] = cnt;
    }
    
    for (i = 0; i < 12; i = i + 1) {
        if (env_seq[i] != 1) {
            for (j = 0; j < 12; j = j + 1) {
                seq = env_seq[j];
                cnt = env_cnt[j];
                cnt = hailstone(seq, cnt);
                env_seq[j] = seq;
                env_cnt[j] = cnt;
            }
            i = -1;
        }
    }
    
    return;
}
