void ddate_and_day_of_year(int y, int m, int d, int argc, int result[2]) {
    int month_lengths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int doy = d;
    int leap = 0;
    
    if (y % 400 == 0) {
        leap = 1;
    } else {
        if (y % 4 == 0) {
            if (y % 100 != 0) {
                leap = 1;
            }
        }
    }
    
    if (argc == 4) {
        for (; m > 1; m = m - 1) {
            doy = doy + month_lengths[m - 2];
            if (m == 3) {
                if (leap != 0) {
                    doy = doy + 1;
                }
            }
        }
    }
    
    result[1] = doy;
    
    if (leap != 0) {
        if (doy == 60) {
            result[0] = -1;
            return;
        } else {
            if (doy >= 60) {
                doy = doy - 1;
            }
        }
    }
    
    int day = doy % 5;
    int season_num = ((doy % 73) == 0 ? doy - 1 : doy) / 73;
    int date_num = (doy % 73) == 0 ? 73 : doy % 73;
    
    if (day == 1) {
        result[0] = 1;
    } else if (day == 2) {
        result[0] = 2;
    } else if (day == 3) {
        result[0] = 3;
    } else if (day == 4) {
        result[0] = 4;
    } else {
        result[0] = 5;
    }
    
    if (season_num == 0) {
        result[0] = result[0] * 10 + 0;
    } else if (season_num == 1) {
        result[0] = result[0] * 10 + 1;
    } else if (season_num == 2) {
        result[0] = result[0] * 10 + 2;
    } else if (season_num == 3) {
        result[0] = result[0] * 10 + 3;
    } else {
        result[0] = result[0] * 10 + 4;
    }
    
    result[0] = result[0] * 100 + date_num;
    result[0] = result[0] * 10000 + (1166 + y);
    return;
}
