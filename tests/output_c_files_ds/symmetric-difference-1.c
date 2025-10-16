void show_sym_diff(const char *const x[5], int lenx, const char *const y[5], int leny) {
    int i;
    int j;
    int found;
    for (i = 0; i < lenx; i = i + 1) {
        if (x[i]) {
            found = 0;
            for (j = 0; j < leny; j = j + 1) {
                if (y[j]) {
                    int k;
                    int match = 1;
                    for (k = 0; x[i][k] != 0 || y[j][k] != 0; k = k + 1) {
                        if (x[i][k] != y[j][k]) {
                            match = 0;
                            break;
                        }
                    }
                    if (match) {
                        found = 1;
                        break;
                    }
                }
            }
            if (!found) {
                ;
            }
        }
    }
    for (i = 0; i < leny; i = i + 1) {
        if (y[i]) {
            found = 0;
            for (j = 0; j < lenx; j = j + 1) {
                if (x[j]) {
                    int k;
                    int match = 1;
                    for (k = 0; y[i][k] != 0 || x[j][k] != 0; k = k + 1) {
                        if (y[i][k] != x[j][k]) {
                            match = 0;
                            break;
                        }
                    }
                    if (match) {
                        found = 1;
                        break;
                    }
                }
            }
            if (!found) {
                ;
            }
        }
    }
    return;
}
