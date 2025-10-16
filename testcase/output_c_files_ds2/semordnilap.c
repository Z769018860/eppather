void processWords(int ct, int len, char words[5][24], char drows[5][24], char tmp[24]) {
    int i;
    int j;
    int c;
    int sem;
    char swap;
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = len - 1; j >= len / 2; j = j - 1) {
            swap = drows[i][len - j - 1];
            drows[i][len - j - 1] = drows[i][j];
            drows[i][j] = swap;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            if (i < j) {
                c = 0;
                while (drows[i][c] == words[j][c] && drows[i][c] != 0 && words[j][c] != 0) {
                    c = c + 1;
                }
                if (drows[i][c] > words[j][c]) {
                    c = 0;
                    while (drows[i][c] != 0) {
                        tmp[c] = drows[i][c];
                        c = c + 1;
                    }
                    tmp[c] = 0;
                    c = 0;
                    while (tmp[c] != 0) {
                        c = c + 1;
                    }
                    for (c = c - 1; c >= 0; c = c - 1) {
                        swap = tmp[c];
                        tmp[c] = tmp[len - c - 1];
                        tmp[len - c - 1] = swap;
                    }
                    c = 0;
                    while (drows[i][c] == tmp[c] && drows[i][c] != 0 && tmp[c] != 0) {
                        c = c + 1;
                    }
                    if (drows[i][c] > tmp[c] && sem < 5) {
                        sem = sem + 1;
                    }
                }
            }
        }
    }
    return;
}
