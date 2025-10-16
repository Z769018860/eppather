void markoved(int rule, char text[5][20], char markoved[5][20]) {
    int i;
    int j;
    int k;
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 20; j = j + 1) {
            markoved[i][j] = text[i][j];
        }
    }
    if (rule == 1) {
        for (i = 0; i < 5; i = i + 1) {
            for (j = 0; j < 20; j = j + 1) {
                if (markoved[i][j] == 'B') {
                    markoved[i][j] = 'b';
                    markoved[i][j + 1] = 'a';
                    markoved[i][j + 2] = 'g';
                }
                if (markoved[i][j] == 'A') {
                    markoved[i][j] = 'a';
                    markoved[i][j + 1] = 'p';
                    markoved[i][j + 2] = 'p';
                    markoved[i][j + 3] = 'l';
                    markoved[i][j + 4] = 'e';
                }
                if (markoved[i][j] == 'T') {
                    markoved[i][j] = 'm';
                    markoved[i][j + 1] = 'y';
                }
                if (markoved[i][j] == 'S') {
                    markoved[i][j] = 'b';
                    markoved[i][j + 1] = 'r';
                    markoved[i][j + 2] = 'o';
                    markoved[i][j + 3] = 't';
                    markoved[i][j + 4] = 'h';
                    markoved[i][j + 5] = 'e';
                    markoved[i][j + 6] = 'r';
                }
            }
        }
    }
    if (rule == 2) {
        for (i = 0; i < 5; i = i + 1) {
            for (j = 0; j < 20; j = j + 1) {
                if (markoved[i][j] == 'B') {
                    markoved[i][j] = 'b';
                    markoved[i][j + 1] = 'a';
                    markoved[i][j + 2] = 'g';
                }
                if (markoved[i][j] == 'A') {
                    markoved[i][j] = 'a';
                    markoved[i][j + 1] = 'p';
                    markoved[i][j + 2] = 'p';
                    markoved[i][j + 3] = 'l';
                    markoved[i][j + 4] = 'e';
                }
                if (markoved[i][j] == 'S') {
                    markoved[i][j] = 's';
                    markoved[i][j + 1] = 'h';
                    markoved[i][j + 2] = 'o';
                    markoved[i][j + 3] = 'p';
                }
            }
        }
    }
    if (rule == 3) {
        for (i = 0; i < 5; i = i + 1) {
            for (j = 0; j < 20; j = j + 1) {
                if (markoved[i][j] == 'B') {
                    markoved[i][j] = 'b';
                    markoved[i][j + 1] = 'a';
                    markoved[i][j + 2] = 'g';
                }
                if (markoved[i][j] == 'A') {
                    markoved[i][j] = 'a';
                    markoved[i][j + 1] = 'p';
                    markoved[i][j + 2] = 'p';
                    markoved[i][j + 3] = 'l';
                    markoved[i][j + 4] = 'e';
                }
                if (markoved[i][j] == 'W') {
                    markoved[i][j] = 'w';
                    markoved[i][j + 1] = 'i';
                    markoved[i][j + 2] = 't';
                    markoved[i][j + 3] = 'h';
                }
                if (markoved[i][j] == 'B') {
                    markoved[i][j] = 'm';
                    markoved[i][j + 1] = 'o';
                    markoved[i][j + 2] = 'n';
                    markoved[i][j + 3] = 'e';
                    markoved[i][j + 4] = 'y';
                }
                if (markoved[i][j] == 'S') {
                    markoved[i][j] = 's';
                    markoved[i][j + 1] = 'h';
                    markoved[i][j + 2] = 'o';
                    markoved[i][j + 3] = 'p';
                }
            }
        }
    }
    if (rule == 4) {
        for (i = 0; i < 5; i = i + 1) {
            for (j = 0; j < 20; j = j + 1) {
                if (markoved[i][j] == '_') {
                    markoved[i][j] = '1';
                }
                if (markoved[i][j] == '*') {
                    markoved[i][j] = '1';
                }
            }
        }
    }
    if (rule == 5) {
        for (i = 0; i < 5; i = i + 1) {
            for (j = 0; j < 20; j = j + 1) {
                if (markoved[i][j] == 'A') {
                    markoved[i][j] = '1';
                    markoved[i][j + 1] = '1';
                    markoved[i][j + 2] = 'H';
                    markoved[i][j + 3] = '1';
                    markoved[i][j + 4] = '1';
                }
            }
        }
    }
    return;
}
