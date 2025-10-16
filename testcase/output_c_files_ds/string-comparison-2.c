int strcmp_rewrite(const char* a, const char* b) {
    int i = 0;
    for (; a[i] != 0 && b[i] != 0; i = i + 1) {
        if (a[i] != b[i]) {
            return a[i] - b[i];
        }
    }
    return a[i] - b[i];
}

int strcasecmp_rewrite(const char* a, const char* b) {
    int i = 0;
    for (; a[i] != 0 && b[i] != 0; i = i + 1) {
        int ca = a[i];
        int cb = b[i];
        if (ca >= 'A' && ca <= 'Z') {
            ca = ca + 32;
        }
        if (cb >= 'A' && cb <= 'Z') {
            cb = cb + 32;
        }
        if (ca != cb) {
            return ca - cb;
        }
    }
    return a[i] - b[i];
}

void compare_rewrite(const char* a, const char* b, int* results) {
    int cmp = strcmp_rewrite(a, b);
    results[0] = (cmp == 0);
    results[1] = (cmp != 0);
    results[2] = (cmp > 0);
    results[3] = (cmp < 0);
    results[4] = (cmp >= 0);
    results[5] = (cmp <= 0);
}

void comparecase_rewrite(const char* a, const char* b, int* results) {
    int cmp = strcasecmp_rewrite(a, b);
    results[0] = (cmp == 0);
    results[1] = (cmp != 0);
    results[2] = (cmp > 0);
    results[3] = (cmp < 0);
    results[4] = (cmp >= 0);
    results[5] = (cmp <= 0);
}

void compare_all(const char* a, const char* b, int results[2][6]) {
    compare_rewrite(a, b, results[0]);
    comparecase_rewrite(a, b, results[1]);
    return;
}
