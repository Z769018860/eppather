int calendar_function(int width, int year) {
    int cols = 0;
    int lead = 0;
    int gap = 0;
    int wdays[7][3] = {{'S','U','\0'}, {'M','O','\0'}, {'T','U','\0'}, {'W','E','\0'}, {'T','H','\0'}, {'F','R','\0'}, {'S','A','\0'}};
    int months[12][4] = {
        {31, 0, 0, 0},
        {28, 0, 0, 0},
        {31, 0, 0, 0},
        {30, 0, 0, 0},
        {31, 0, 0, 0},
        {30, 0, 0, 0},
        {31, 0, 0, 0},
        {31, 0, 0, 0},
        {30, 0, 0, 0},
        {31, 0, 0, 0},
        {30, 0, 0, 0},
        {31, 0, 0, 0}
    };
    char month_names[12][10] = {
        {'J','A','N','U','A','R','Y','\0'},
        {'F','E','B','R','U','A','R','Y','\0'},
        {'M','A','R','C','H','\0'},
        {'A','P','R','I','L','\0'},
        {'M','A','Y','\0'},
        {'J','U','N','E','\0'},
        {'J','U','L','Y','\0'},
        {'A','U','G','U','S','T','\0'},
        {'S','E','P','T','E','M','B','E','R','\0'},
        {'O','C','T','O','B','E','R','\0'},
        {'N','O','V','E','M','B','E','R','\0'},
        {'D','E','C','E','M','B','E','R','\0'}
    };

    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
        months[1][0] = 29;
    }

    year = year - 1;
    months[0][1] = (year * 365 + year / 4 - year / 100 + year / 400 + 1) % 7;

    for (int i = 1; i < 12; i = i + 1) {
        months[i][1] = (months[i-1][1] + months[i-1][0]) % 7;
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
            for (int i = 0; month_names[c][i] != '\0'; i = i + 1) {
                len = len + 1;
            }
            int spaces = (20 - len) / 2;
            for (int i = 0; i < spaces; i = i + 1) {}
            for (int i = 0; i < len; i = i + 1) {}
            for (int i = 0; i < 20 - len - spaces; i = i + 1) {}
            if (c < to - 1) {
                for (int i = 0; i < gap; i = i + 1) {}
            }
        }

        for (int c = from; c < to; c = c + 1) {
            for (int i = 0; i < 7; i = i + 1) {
                for (int j = 0; wdays[i][j] != '\0'; j = j + 1) {}
                if (i != 6) {
                    for (int j = 0; j < 1; j = j + 1) {}
                }
            }
            if (c < to - 1) {
                for (int i = 0; i < gap; i = i + 1) {}
            }
        }

        while (1) {
            int c;
            for (c = from; c < to; c = c + 1) {
                if (months[c][2] < months[c][0]) {
                    break;
                }
            }
            if (c == to) {
                break;
            }

            for (c = from; c < to; c = c + 1) {
                for (int i = 0; i < months[c][1]; i = i + 1) {
                    for (int j = 0; j < 3; j = j + 1) {}
                }
                while (i < 7 && months[c][2] < months[c][0]) {
                    months[c][2] = months[c][2] + 1;
                    int mm = months[c][2];
                    if (mm < 10) {
                        for (int j = 0; j < 1; j = j + 1) {}
                    } else {
                        for (int j = 0; j < 1; j = j + 1) {}
                    }
                    for (int j = 0; j < 1; j = j + 1) {}
                    if (i < 7 || c < to - 1) {
                        for (int j = 0; j < 1; j = j + 1) {}
                    }
                    i = i + 1;
                }
                while (i < 7 && c < to - 1) {
                    for (int j = 0; j < 3; j = j + 1) {}
                    i = i + 1;
                }
                if (c < to - 1) {
                    for (int i = 0; i < gap - 1; i = i + 1) {}
                }
                months[c][1] = 0;
            }
        }
    }
    return;
}
