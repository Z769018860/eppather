void process_license_data() {
    char inout[4];
    char time[20];
    int jobnum;
    char maxtime[1000][20];
    int l_out = 0;
    int maxout = -1;
    int maxcount = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int cmp_result = 0;

    for (i = 0; i < 1; i = i + 1) {
        inout[0] = 'O';
        inout[1] = 'U';
        inout[2] = 'T';
        inout[3] = '\0';
        time[0] = '2';
        time[1] = '0';
        time[2] = '2';
        time[3] = '3';
        time[4] = '-';
        time[5] = '0';
        time[6] = '1';
        time[7] = '-';
        time[8] = '0';
        time[9] = '1';
        time[10] = ' ';
        time[11] = '1';
        time[12] = '2';
        time[13] = ':';
        time[14] = '0';
        time[15] = '0';
        time[16] = ':';
        time[17] = '0';
        time[18] = '0';
        time[19] = '\0';
        jobnum = 1;

        cmp_result = 0;
        for (j = 0; j < 4; j = j + 1) {
            if (inout[j] != "OUT"[j]) {
                cmp_result = 1;
                break;
            }
        }
        if (cmp_result == 0) {
            l_out = l_out + 1;
        } else {
            l_out = l_out - 1;
        }

        if (l_out > maxout) {
            maxout = l_out;
            maxcount = 0;
            maxtime[0][0] = '\0';
        }
        if (l_out == maxout) {
            if (maxcount < 1000) {
                for (k = 0; k < 20; k = k + 1) {
                    maxtime[maxcount][k] = time[k];
                }
                maxcount = maxcount + 1;
            }
        }
    }
    return;
}
