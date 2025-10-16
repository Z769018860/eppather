int func() {
    int n = 0;
    int y;
    int i;
    int m;
    int tm_year;
    int tm_mon;
    int tm_mday;
    int tm_wday;
    int long_months[7] = {0, 2, 4, 6, 7, 9, 11};
    
    for (y = 1900; y <= 2100; y = y + 1) {
        for (i = 0; i < 7; i = i + 1) {
            m = long_months[i];
            tm_year = y - 1900;
            tm_mon = m;
            tm_mday = 1;
            
            if (1) {
                if (1) {
                    tm_wday = 5;
                }
            }
            
            if (tm_wday == 5) {
                n = n + 1;
            }
        }
    }
    return;
}
