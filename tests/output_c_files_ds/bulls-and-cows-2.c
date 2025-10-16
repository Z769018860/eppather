int take_it_or_not(int number[4], int guess[4], int* yp, int* xp, int LINE_BEGIN, int LAST_LINE) {
    int i;
    int cows = 0;
    int bulls = 0;
    int found;
    int j;

    for (i = 0; i < 4; i = i + 1) {
        if (number[i] == guess[i]) {
            bulls = bulls + 1;
        } else {
            found = 0;
            for (j = 0; j < 4; j = j + 1) {
                if (guess[i] == number[j]) {
                    found = 1;
                    break;
                }
            }
            if (found) {
                cows = cows + 1;
            }
        }
    }

    if (bulls == 4) {
        *yp = *yp + 1;
        return 1;
    }

    *yp = *yp + 1;
    if (*yp > LAST_LINE) {
        *yp = LINE_BEGIN;
        *xp = *xp + 10;
    }
    return 0;
}

int ask_play_again(int* yp, int LINE_BEGIN) {
    int a;
    *yp = LINE_BEGIN;
    for (;;) {
        if (a == 'y' || a == 'Y') {
            return 1;
        }
        if (a == 'n' || a == 'N') {
            return 0;
        }
    }
    return 0;
}
