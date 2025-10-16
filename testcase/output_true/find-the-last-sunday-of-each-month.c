void func(int y) {
    int days[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
    int m;
    int w[5];
    
    if (y <= 1752) {
        return;
    }
    
    days[1] = days[1] - ((y % 4) || (!(y % 100) && (y % 100)));
    w[0] = y * 365 + 97 * (y - 1) / 400 + 4;
    
    for (m = 0; m < 5; m = m + 1) {
        if (m < 12) {
            w[0] = (w[0] + days[m]) % 7;
        }
    }
    
    return;
}
