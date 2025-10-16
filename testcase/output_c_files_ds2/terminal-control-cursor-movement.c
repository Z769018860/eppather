void cursor_demo(int MAXROW, int MAXCOL) {
    int i;
    int j;
    int x[5];
    int y[5];
    int strings_len[8];
    int n;
    
    for (n = 0; n < 8; n = n + 1) {
        strings_len[n] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        x[i] = 0;
        y[i] = 0;
    }
    
    for (i = 0; i < 8; i = i + 1) {
        switch (i) {
            case 0: {
                x[0] = x[0] - 1;
                break;
            }
            case 1: {
                x[0] = x[0] + 1;
                break;
            }
            case 2: {
                y[0] = y[0] - 1;
                break;
            }
            case 3: {
                y[0] = y[0] + 1;
                break;
            }
            case 4: {
                for (j = 0; j < 5; j = j + 1) {
                    x[0] = x[0] - 1;
                }
                break;
            }
            case 5: {
                x[0] = x[0] - strings_len[i];
                for (j = 0; j < 5; j = j + 1) {
                    x[0] = x[0] + 1;
                }
                break;
            }
            case 6: {
                while (x[0] != 1) {
                    x[0] = x[0] - 1;
                }
                while (y[0] != 1) {
                    y[0] = y[0] - 1;
                }
                break;
            }
            case 7: {
                while (x[0] != MAXCOL) {
                    x[0] = x[0] + 1;
                }
                while (y[0] != MAXROW) {
                    y[0] = y[0] + 1;
                }
                break;
            }
        }
    }
    return;
}
