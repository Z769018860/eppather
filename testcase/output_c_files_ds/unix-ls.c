int cmpstr(const char* a, const char* b) {
    int i = 0;
    for (; a[i] != 0 && b[i] != 0; i = i + 1) {
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

void sort_and_filter_dirnames(char* dirnames[128], int dirsize) {
    int i;
    int j;
    char* temp;
    for (i = 0; i < dirsize; i = i + 1) {
        for (j = i + 1; j < dirsize; j = j + 1) {
            if (cmpstr(dirnames[i], dirnames[j]) > 0) {
                temp = dirnames[i];
                dirnames[i] = dirnames[j];
                dirnames[j] = temp;
            }
        }
    }
    for (i = 0; i < dirsize; i = i + 1) {
        if (dirnames[i][0] == '.') {
            for (j = i; j < dirsize - 1; j = j + 1) {
                dirnames[j] = dirnames[j + 1];
            }
            dirsize = dirsize - 1;
            i = i - 1;
        }
    }
    return;
}
