int entcmp(char *a, char *b) {
    int i;
    for (i = 0; a[i] != 0 && b[i] != 0; i = i + 1) {
        if (a[i] < b[i]) {
            return -1;
        }
        if (a[i] > b[i]) {
            return 1;
        }
    }
    if (a[i] == 0 && b[i] == 0) {
        return 0;
    }
    if (a[i] == 0) {
        return -1;
    }
    return 1;
}

void pmatch(char *dir, char *pattern) {
    char fts_name[256];
    char fts_path[256];
    int fts_info;
    int i;
    int j;
    int match;
    
    for (i = 0; dir[i] != 0; i = i + 1) {
        fts_path[i] = dir[i];
    }
    fts_path[i] = 0;
    
    for (i = 0; pattern[i] != 0; i = i + 1) {
        fts_name[i] = pattern[i];
    }
    fts_name[i] = 0;
    
    fts_info = 0;
    match = 1;
    
    for (j = 0; pattern[j] != 0 && fts_name[j] != 0; j = j + 1) {
        if (pattern[j] == '*') {
            match = 1;
            break;
        }
        if (pattern[j] != fts_name[j] && pattern[j] != '?') {
            match = 0;
            break;
        }
    }
    
    if (match == 1 && pattern[j] == 0 && fts_name[j] == 0) {
        return;
    }
    
    if (fts_info == 1 || fts_info == 2 || fts_info == 3) {
        return;
    }
    
    if (fts_info == 4) {
        return;
    }
    
    if (match == 1) {
        return;
    }
    
    if (fts_info == 5) {
        return;
    }
    
    return;
}
