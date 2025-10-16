void process_words() {
    int i;
    int j;
    int len;
    int ct;
    int c;
    int sem;
    char tmp[24];
    char words[1000][24];
    char drows[1000][24];
    
    ct = 0;
    sem = 0;
    
    for (i = 0; i < ct; i = i + 1) {
        len = 0;
        for (j = 0; j < 24; j = j + 1) {
            if (words[i][j] != '\0') {
                len = len + 1;
            } else {
                break;
            }
        }
        
        for (j = 0; j < len; j = j + 1) {
            drows[i][j] = words[i][len - j - 1];
        }
        drows[i][len] = '\0';
    }
    
    for (i = 0; i < ct; i = i + 1) {
        for (j = i + 1; j < ct; j = j + 1) {
            c = 0;
            while (drows[i][c] != '\0' && words[j][c] != '\0' && drows[i][c] == words[j][c]) {
                c = c + 1;
            }
            if (drows[i][c] == '\0' && words[j][c] == '\0') {
                len = 0;
                while (drows[i][len] != '\0') {
                    len = len + 1;
                }
                for (c = 0; c < len / 2; c = c + 1) {
                    tmp[0] = drows[i][c];
                    drows[i][c] = drows[i][len - c - 1];
                    drows[i][len - c - 1] = tmp[0];
                }
                if (sem < 5) {
                    sem = sem + 1;
                }
            }
        }
    }
    
    return;
}
