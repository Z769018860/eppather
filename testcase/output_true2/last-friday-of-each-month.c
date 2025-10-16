int func(int y) {
    int days[12];
    days[0] = 31;
    days[1] = 29;
    days[2] = 31;
    days[3] = 30;
    days[4] = 31;
    days[5] = 30;
    days[6] = 31;
    days[7] = 31;
    days[8] = 30;
    days[9] = 31;
    days[10] = 30;
    days[11] = 31;
    int m;
    int w;
    int temp;
    
    if (y <= 1700) {
        return;
    }
    
    temp = y % 4;
    if (temp != 0) {
        days[1] = days[1] - 1;
    } else {
        temp = y % 100;
        if (temp == 0) {
            temp = y % 400;
            if (temp != 0) {
                days[1] = days[1] - 1;
            }
        }
    }
    
    w = y * 365;
    temp = y - 1;
    w = w + temp / 4;
    w = w - temp / 100;
    w = w + temp / 400;
    w = w + 6;
    
    for (m = 0; m < 12; m = m + 1) {
        w = (w + days[m]) % 7;
    }
    
    return;
}
