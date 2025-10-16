int day_of_year(int y, int m, int d) {
    int month_lengths[12];
    month_lengths[0] = 31;
    month_lengths[1] = 28;
    month_lengths[2] = 31;
    month_lengths[3] = 30;
    month_lengths[4] = 31;
    month_lengths[5] = 30;
    month_lengths[6] = 31;
    month_lengths[7] = 31;
    month_lengths[8] = 30;
    month_lengths[9] = 31;
    month_lengths[10] = 30;
    month_lengths[11] = 31;
    
    for (; m > 1; m = m - 1) {
        d = d + month_lengths[m - 2];
        if (m == 3) {
            if ((y % 400 == 0) || ((y % 4 == 0) && (y % 100 != 0))) {
                d = d + 1;
            }
        }
    }
    return d;
}

void ddate(int y, int d, int result[5]) {
    int dyear = 1166 + y;
    int leap = 0;
    
    if ((y % 400 == 0) || ((y % 4 == 0) && (y % 100 != 0))) {
        leap = 1;
    }
    
    if (leap == 1) {
        if (d == 60) {
            result[0] = 1;
            result[1] = dyear;
            return;
        } else if (d >= 60) {
            d = d - 1;
        }
    }
    
    int day = d % 5;
    int season_num = ((d % 73) == 0 ? d - 1 : d) / 73;
    int date_num = (d % 73) == 0 ? 73 : (d % 73);
    
    result[0] = 0;
    result[1] = day;
    result[2] = season_num;
    result[3] = date_num;
    result[4] = dyear;
    return;
}
