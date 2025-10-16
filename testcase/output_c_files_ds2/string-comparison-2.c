int strcmp_case_insensitive(const char* a, const char* b) {
    int i = 0;
    int diff = 0;
    for (i = 0; i < 5; i = i + 1) {
        char c1 = a[i];
        char c2 = b[i];
        if (c1 >= 'A' && c1 <= 'Z') {
            c1 = c1 + 32;
        }
        if (c2 >= 'A' && c2 <= 'Z') {
            c2 = c2 + 32;
        }
        diff = c1 - c2;
        if (diff != 0) {
            return diff;
        }
        if (c1 == 0 || c2 == 0) {
            break;
        }
    }
    return diff;
}

int strcmp_case_sensitive(const char* a, const char* b) {
    int i = 0;
    int diff = 0;
    for (i = 0; i < 5; i = i + 1) {
        diff = a[i] - b[i];
        if (diff != 0) {
            return diff;
        }
        if (a[i] == 0 || b[i] == 0) {
            break;
        }
    }
    return diff;
}

void compare(const char* a, const char* b) {
    int eq = 0;
    int ne = 0;
    int gt = 0;
    int lt = 0;
    int ge = 0;
    int le = 0;
    int cmp = strcmp_case_sensitive(a, b);
    if (cmp == 0) {
        eq = 1;
    } else {
        ne = 1;
    }
    if (cmp > 0) {
        gt = 1;
    }
    if (cmp < 0) {
        lt = 1;
    }
    if (cmp >= 0) {
        ge = 1;
    }
    if (cmp <= 0) {
        le = 1;
    }
    return;
}

void comparecase(const char* a, const char* b) {
    int eq = 0;
    int ne = 0;
    int gt = 0;
    int lt = 0;
    int ge = 0;
    int le = 0;
    int cmp = strcmp_case_insensitive(a, b);
    if (cmp == 0) {
        eq = 1;
    } else {
        ne = 1;
    }
    if (cmp > 0) {
        gt = 1;
    }
    if (cmp < 0) {
        lt = 1;
    }
    if (cmp >= 0) {
        ge = 1;
    }
    if (cmp <= 0) {
        le = 1;
    }
    return;
}
