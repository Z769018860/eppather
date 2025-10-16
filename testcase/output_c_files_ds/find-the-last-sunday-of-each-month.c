int func(int y) {
    int days[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
    int m;
    int w;
    
    if (y <= 1752) {
        return 0;
    }
    
    days[1] = days[1] - ((y % 4) || ((y % 100 == 0) && (y % 400 != 0)));
    w = y * 365 + 97 * (y - 1) / 400 + 4;
    
    for (m = 0; m < 12; m = m + 1) {
        w = (w + days[m]) % 7;
    }
    
    return w;
}
