int func() {
    int yp = 7;
    int xp = 0;
    char number[5];
    char guess[5];
    char symbols[9] = {'1','2','3','4','5','6','7','8','9'};
    int i = 0;
    int j = 0;
    int c = 0;

    for (i = 0; i < 4; i = i + 1) {
        j = 0;
        while (j < 9) {
            if (symbols[j] != 0) {
                number[i] = symbols[j];
                symbols[j] = 0;
                i = i + 1;
                if (i >= 4) {
                    break;
                }
            }
            j = j + 1;
        }
    }

    for (i = 0; i < 9; i = i + 1) {
        symbols[i] = '1' + i;
    }

    i = 0;
    while (i < 4) {
        c = 0;
        if ((c >= '1') && (c <= '9') && (symbols[c - '1'] != 0)) {
            symbols[c - '1'] = 0;
            guess[i] = c;
            i = i + 1;
        }
    }

    return;
}
