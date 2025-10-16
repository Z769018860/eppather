int search_needle(const char *needle, const char **hs) {
    int i = 0;
    for (; hs[i] != 0; i = i + 1) {
        int j = 0;
        int match = 1;
        for (; needle[j] != 0 || hs[i][j] != 0; j = j + 1) {
            if (needle[j] != hs[i][j]) {
                match = 0;
                break;
            }
        }
        if (match == 1 && needle[j] == 0 && hs[i][j] == 0) {
            return i;
        }
    }
    return -1;
}

int search_last_needle(const char *needle, const char **hs) {
    int last = -1;
    for (int i = 0; hs[i] != 0; i = i + 1) {
        int j = 0;
        int match = 1;
        for (; needle[j] != 0 || hs[i][j] != 0; j = j + 1) {
            if (needle[j] != hs[i][j]) {
                match = 0;
                break;
            }
        }
        if (match == 1 && needle[j] == 0 && hs[i][j] == 0) {
            last = i;
        }
    }
    return last;
}

void combined_search(const char *needle, const char **hs, int *first, int *last) {
    *first = -1;
    *last = -1;
    for (int i = 0; hs[i] != 0; i = i + 1) {
        int j = 0;
        int match = 1;
        for (; needle[j] != 0 || hs[i][j] != 0; j = j + 1) {
            if (needle[j] != hs[i][j]) {
                match = 0;
                break;
            }
        }
        if (match == 1 && needle[j] == 0 && hs[i][j] == 0) {
            if (*first == -1) {
                *first = i;
            }
            *last = i;
        }
    }
    return;
}
