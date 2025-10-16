void five_weekends(int y1, int y2) {
    int n[5] = {0};
    int y;
    int i;
    int m;
    int long_months[7] = {0, 2, 4, 6, 7, 9, 11};
    int tm_year;
    int tm_mon;
    int tm_mday;
    int tm_wday;
    
    for (y = y1; y <= y2; y = y + 1) {
        for (i = 0; i < 7; i = i + 1) {
            m = long_months[i];
            tm_year = y - 1900;
            tm_mon = m;
            tm_mday = 1;
            
            if (m == 2) {
                if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) {
                    tm_wday = (5 + (y - 1900) + (y - 1900) / 4 - (y - 1900) / 100 + (y - 1900) / 400 + (13 * (m + 1)) / 5 + 1) % 7;
                } else {
                    tm_wday = (5 + (y - 1900) + (y - 1900) / 4 - (y - 1900) / 100 + (y - 1900) / 400 + (13 * (m + 1)) / 5 + 1) % 7;
                }
            } else {
                tm_wday = (5 + (y - 1900) + (y - 1900) / 4 - (y - 1900) / 100 + (y - 1900) / 400 + (13 * (m + 1)) / 5 + 1) % 7;
            }
            
            if (tm_wday == 5) {
                n[0] = n[0] + 1;
            }
        }
    }
    return;
}
