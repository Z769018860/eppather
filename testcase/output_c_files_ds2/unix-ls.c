int cmpstr(const char* a, const char* b) {
    int i = 0;
    for (i = 0; i < 5; i = i + 1) {
        if (a[i] != b[i]) {
            return a[i] - b[i];
        }
        if (a[i] == 0) {
            return 0;
        }
    }
    return 0;
}

void process_dirnames() {
    int dirnames[5][5];
    int dirsize = 0;
    int i = 0;
    int j = 0;
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            dirnames[i][j] = 0;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (dirnames[i][0] != 46) {
            int temp[5];
            for (j = 0; j < 5; j = j + 1) {
                temp[j] = dirnames[i][j];
            }
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = i + 1; j < 5; j = j + 1) {
            if (cmpstr((const char*)dirnames[i], (const char*)dirnames[j]) > 0) {
                int temp[5];
                for (int k = 0; k < 5; k = k + 1) {
                    temp[k] = dirnames[i][k];
                    dirnames[i][k] = dirnames[j][k];
                    dirnames[j][k] = temp[k];
                }
            }
        }
    }
    
    return;
}
