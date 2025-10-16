void calendar_func(int width, int year) {
    int cols;
    int lead;
    int gap;
    int months_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int months_start_wday[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int months_at[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int wdays[7][3] = {{'S','U',0}, {'M','O',0}, {'T','U',0}, {'W','E',0}, {'T','H',0}, {'F','R',0}, {'S','A',0}};
    int months_name[12][10] = {
        {'J','A','N','U','A','R','Y',0,0,0},
        {'F','E','B','R','U','A','R','Y',0,0},
        {'M','A','R','C','H',0,0,0,0,0},
        {'A','P','R','I','L',0,0,0,0,0},
        {'M','A','Y',0,0,0,0,0,0,0},
        {'J','U','N','E',0,0,0,0,0,0},
        {'J','U','L','Y',0,0,0,0,0,0},
        {'A','U','G','U','S','T',0,0,0,0},
        {'S','E','P','T','E','M','B','E','R',0},
        {'O','C','T','O','B','E','R',0,0,0},
        {'N','O','V','E','M','B','E','R',0,0},
        {'D','E','C','E','M','B','E','R',0,0}
    };

    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
        months_days[1] = 29;
    }

    year = year - 1;
    months_start_wday[0] = (year * 365 + year / 4 - year / 100 + year / 400 + 1) % 7;

    for (int i = 1; i < 12; i = i + 1) {
        months_start_wday[i] = (months_start_wday[i - 1] + months_days[i - 1]) % 7;
    }

    cols = (width + 2) / 22;
    while (12 % cols != 0) {
        cols = cols - 1;
    }
    gap = cols - 1 != 0 ? (width - 20 * cols) / (cols - 1) : 0;
    if (gap > 4) {
        gap = 4;
    }
    lead = (width - (20 + gap) * cols + gap + 1) / 2;
    year = year + 1;

    for (int row = 0; row * cols < 12; row = row + 1) {
        int from = row * cols;
        int to = from + cols;

        for (int c = from; c < to; c = c + 1) {
            int len = 0;
            while (months_name[c][len] != 0 && len < 10) {
                len = len + 1;
            }
            int spaces = (20 - len) / 2;
            for (int i = 0; i < spaces; i = i + 1) {
            }
            for (int i = 0; i < len; i = i + 1) {
            }
            for (int i = 0; i < 20 - len - spaces; i = i + 1) {
            }
            if (c < to - 1) {
                for (int i = 0; i < gap; i = i + 1) {
                }
            }
        }

        for (int c = from; c < to; c = c + 1) {
            for (int i = 0; i < 7; i = i + 1) {
                for (int j = 0; j < 2; j = j + 1) {
                }
                if (i != 6) {
                }
            }
            if (c < to - 1) {
                for (int i = 0; i < gap; i = i + 1) {
                }
            }
        }

        while (1) {
            int c;
            for (c = from; c < to; c = c + 1) {
                if (months_at[c] < months_days[c]) {
                    break;
                }
            }
            if (c == to) {
                break;
            }

            for (c = from; c < to; c = c + 1) {
                for (int i = 0; i < months_start_wday[c]; i = i + 1) {
                }
                int i = months_start_wday[c];
                while (i < 7 && months_at[c] < months_days[c]) {
                    months_at[c] = months_at[c] + 1;
                    int mm = months_at[c];
                    if (mm < 10) {
                    } else {
                    }
                    if (i < 7 || c < to - 1) {
                    }
                    i = i + 1;
                }
                while (i < 7 && c < to - 1) {
                    i = i + 1;
                }
                if (c < to - 1) {
                    for (int i = 0; i < gap - 1; i = i + 1) {
                    }
                }
                months_start_wday[c] = 0;
            }
        }
    }

    int y = year;
    int buf[32];
    int b = 31;
    buf[b] = 0;
    b = b - 1;
    do {
        buf[b] = '0' + (y % 10);
        y = y / 10;
        b = b - 1;
    } while (y > 0);
    b = b + 1;
    int len = 0;
    while (buf[b + len] != 0 && len < 32) {
        len = len + 1;
    }
    int spaces = (width - len) / 2;
    for (int i = 0; i < spaces; i = i + 1) {
    }
    for (int i = 0; i < len; i = i + 1) {
    }
    return;
}
