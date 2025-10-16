void process_license_data(int inout_len, int time_len, int max_maxout) {
    int inout[5];
    int time[5];
    int jobnum[5];
    int maxtime[1000][20];
    int l_out[5] = {0};
    int maxout[5] = {-1};
    int maxcount[5] = {0};
    int i;
    int j;
    
    for (i = 0; i < 5; i = i + 1) {
        if (inout[i] == 0) {
            l_out[0] = l_out[0] + 1;
        } else {
            l_out[0] = l_out[0] - 1;
        }
        
        if (l_out[0] > maxout[0]) {
            maxout[0] = l_out[0];
            maxcount[0] = 0;
            for (j = 0; j < time_len; j = j + 1) {
                maxtime[0][j] = 0;
            }
        }
        
        if (l_out[0] == maxout[0]) {
            if (maxcount[0] < max_maxout) {
                for (j = 0; j < time_len; j = j + 1) {
                    maxtime[maxcount[0]][j] = time[j];
                }
                maxcount[0] = maxcount[0] + 1;
            }
        }
    }
    
    return;
}
