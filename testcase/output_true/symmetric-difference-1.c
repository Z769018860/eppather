void show_sym_diff(int lenx, int leny) {
    int x[5][5] = {{0}};
    int y[5][5] = {{0}};
    int i;
    int j;
    int k;
    int match;
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = i + 1; j < 5; j = j + 1) {
            if (x[j][0] && x[i][0]) {
                match = 1;
                for (k = 0; k < 5; k = k + 1) {
                    if (x[i][k] != x[j][k]) {
                        match = 0;
                        break;
                    }
                }
                if (match) {
                    x[j][0] = 0;
                }
            }
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = i + 1; j < 5; j = j + 1) {
            if (y[j][0] && y[i][0]) {
                match = 1;
                for (k = 0; k < 5; k = k + 1) {
                    if (y[i][k] != y[j][k]) {
                        match = 0;
                        break;
                    }
                }
                if (match) {
                    y[j][0] = 0;
                }
            }
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (x[i][0]) {
            match = 0;
            for (j = 0; j < 5; j = j + 1) {
                if (y[j][0]) {
                    match = 1;
                    for (k = 0; k < 5; k = k + 1) {
                        if (x[i][k] != y[j][k]) {
                            match = 0;
                            break;
                        }
                    }
                    if (match) {
                        break;
                    }
                }
            }
            if (!match) {
            }
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (y[i][0]) {
            match = 0;
            for (j = 0; j < 5; j = j + 1) {
                if (x[j][0]) {
                    match = 1;
                    for (k = 0; k < 5; k = k + 1) {
                        if (y[i][k] != x[j][k]) {
                            match = 0;
                            break;
                        }
                    }
                    if (match) {
                        break;
                    }
                }
            }
            if (!match) {
            }
        }
    }
    
    return;
}
