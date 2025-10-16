int func(int max_buf) {
    int seconds[5];
    int now_tm_year[5];
    int now_tm_mon[5];
    int now_tm_mday[5];
    int now_tm_wday[5];
    int months[12][5];
    int days[7][5];
    int buf[50];
    int i;
    
    for (i = 0; i < 5; i = i + 1) {
        seconds[i] = 0;
        now_tm_year[i] = 0;
        now_tm_mon[i] = 0;
        now_tm_mday[i] = 0;
        now_tm_wday[i] = 0;
        buf[i] = 0;
    }
    
    for (i = 0; i < 12; i = i + 1) {
        for (int j = 0; j < 5; j = j + 1) {
            months[i][j] = 0;
        }
    }
    
    for (i = 0; i < 7; i = i + 1) {
        for (int j = 0; j < 5; j = j + 1) {
            days[i][j] = 0;
        }
    }
    
    now_tm_year[0] = now_tm_year[0] + 1900;
    now_tm_mon[0] = now_tm_mon[0] + 1;
    
    return;
}
