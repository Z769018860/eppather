int entcmp(int a[5], int b[5]) {
    int i;
    for (i = 0; i < 5; i = i + 1) {
        if (a[i] < b[i]) {
            return -1;
        }
        if (a[i] > b[i]) {
            return 1;
        }
    }
    return 0;
}

void pmatch(int dir[5], int pattern[5]) {
    int tree[5];
    int f[5];
    int argv[5][5];
    int i;
    int j;
    
    for (i = 0; i < 5; i = i + 1) {
        argv[0][i] = dir[i];
    }
    argv[1][0] = 0;
    
    for (i = 0; i < 5; i = i + 1) {
        tree[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        f[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (tree[i] != 0) {
            continue;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        f[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (f[i] == 1) {
            continue;
        }
        if (f[i] == 2) {
            continue;
        }
        if (f[i] == 3) {
            continue;
        }
        if (f[i] == 4) {
            continue;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (pattern[i] == 0) {
            continue;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (f[i] == 5) {
            continue;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (tree[i] != 0) {
            continue;
        }
    }
    
    return;
}
