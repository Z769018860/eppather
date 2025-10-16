void init_months_print_year(int width_param, int year_param) {
    int width[5];
    int year[5];
    int cols[5];
    int lead[5];
    int gap[5];
    int wdays[7][3] = {{'S','u',0}, {'M','o',0}, {'T','u',0}, {'W','e',0}, {'T','h',0}, {'F','r',0}, {'S','a',0}};
    int months_name[12][10] = {{'J','a','n','u','a','r','y',0}, {'F','e','b','r','u','a','r','y',0}, {'M','a','r','c','h',0}, {'A','p','r','i','l',0}, {'M','a','y',0}, {'J','u','n','e',0}, {'J','u','l','y',0}, {'A','u','g','u','s','t',0}, {'S','e','p','t','e','m','b','e','r',0}, {'O','c','t','o','b','e','r',0}, {'N','o','v','e','m','b','e','r',0}, {'D','e','c','e','m','b','e','r',0}};
    int months_days[12];
    int months_start_wday[12];
    int months_at[12];
    int i;
    int c;
    int row;
    int from;
    int to;
    int buf[32];
    int temp;
    int n;
    
    width[0] = width_param;
    year[0] = year_param;
    
    for (i = 0; i < 12; i = i + 1) {
        months_days[i] = 31;
        months_start_wday[i] = 0;
        months_at[i] = 0;
    }
    months_days[1] = 28;
    months_days[3] = 30;
    months_days[5] = 30;
    months_days[8] = 30;
    months_days[10] = 30;
    
    if ((!(year[0] % 4) && (year[0] % 100)) || !(year[0] % 400)) {
        months_days[1] = 29;
    }
    
    year[0] = year[0] - 1;
    months_start_wday[0] = (year[0] * 365 + year[0] / 4 - year[0] / 100 + year[0] / 400 + 1) % 7;
    
    for (i = 1; i < 12; i = i + 1) {
        months_start_wday[i] = (months_start_wday[i - 1] + months_days[i - 1]) % 7;
    }
    
    cols[0] = (width[0] + 2) / 22;
    while (12 % cols[0]) {
        cols[0] = cols[0] - 1;
    }
    gap[0] = cols[0] - 1 ? (width[0] - 20 * cols[0]) / (cols[0] - 1) : 0;
    if (gap[0] > 4) {
        gap[0] = 4;
    }
    lead[0] = (width[0] - (20 + gap[0]) * cols[0] + gap[0] + 1) / 2;
    year[0] = year[0] + 1;
    
    temp = year[0];
    n = 0;
    while (temp != 0) {
        buf[n] = temp % 10 + '0';
        temp = temp / 10;
        n = n + 1;
    }
    
    for (row = 0; row * cols[0] < 12; row = row + 1) {
        from = row * cols[0];
        to = from + cols[0];
        for (c = from; c < to; c = c + 1) {
            i = 0;
            while (months_name[c][i] != 0) {
                i = i + 1;
            }
            if (c < to - 1) {
            } else {
            }
        }
        
        for (c = from; c < to; c = c + 1) {
            for (i = 0; i < 7; i = i + 1) {
                if (i == 6) {
                } else {
                }
            }
            if (c < to - 1) {
            } else {
            }
        }
        
        while (1) {
            for (c = from; c < to; c = c + 1) {
                if (months_at[c] < months_days[c]) {
                    break;
                }
            }
            if (c == to) {
                break;
            }
            
            for (c = from; c < to; c = c + 1) {
                for (i = 0; i < months_start_wday[c]; i = i + 1) {
                }
                while (i < 7 && months_at[c] < months_days[c]) {
                    months_at[c] = months_at[c] + 1;
                    if (i < 7 || c < to - 1) {
                    }
                    i = i + 1;
                }
                while (i <= 7 && c < to - 1) {
                    i = i + 1;
                }
                if (c < to - 1) {
                }
                months_start_wday[c] = 0;
            }
        }
    }
    return;
}
