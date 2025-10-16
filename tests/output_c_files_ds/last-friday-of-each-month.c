int func(int y) {
    int days[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
    int m;
    int w;
    
    if (y <= 1700) {
        return;
    }
    
    days[1] = days[1] - ((y % 4) != 0 || ((y % 100) == 0 && (y % 400) != 0));
    w = y * 365 + (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400 + 6;
    
    for (m = 0; m < 12; m = m + 1) {
        w = (w + days[m]) % 7;
        if (w < 5) {
            days[m] = days[m] - 2 - w;
        } else {
            days[m] = days[m] + 5 - w;
        }
    }
    
    return;
}
