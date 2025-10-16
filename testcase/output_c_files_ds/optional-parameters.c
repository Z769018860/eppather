int cmprStrgs(const char* s1, const char* s2) {
    const char* p1 = s1;
    const char* p2 = s2;
    const char* mrk1;
    const char* mrk2;
    while ((((*p1 >= 'A' && *p1 <= 'Z') ? (*p1 + 32) : *p1) == ((*p2 >= 'A' && *p2 <= 'Z') ? (*p2 + 32) : *p2)) && *p1 != 0) {
        p1 = p1 + 1;
        p2 = p2 + 1;
    }
    if ((*p1 >= '0' && *p1 <= '9') && (*p2 >= '0' && *p2 <= '9')) {
        long v1;
        long v2;
        if ((*p1 == '0') || (*p2 == '0')) {
            while (p1 > s1) {
                p1 = p1 - 1;
                p2 = p2 - 1;
                if (*p1 != '0') {
                    break;
                }
            }
            if (!(*p1 >= '0' && *p1 <= '9')) {
                p1 = p1 + 1;
                p2 = p2 + 1;
            }
        }
        mrk1 = p1;
        mrk2 = p2;
        v1 = 0;
        while (*p1 >= '0' && *p1 <= '9') {
            v1 = 10 * v1 + (*p1 - '0');
            p1 = p1 + 1;
        }
        v2 = 0;
        while (*p2 >= '0' && *p2 <= '9') {
            v2 = 10 * v2 + (*p2 - '0');
            p2 = p2 + 1;
        }
        if (v1 == v2) {
            return (p2 - mrk2) - (p1 - mrk1);
        }
        return v1 - v2;
    }
    if (((*p1 >= 'A' && *p1 <= 'Z') ? (*p1 + 32) : *p1) != ((*p2 >= 'A' && *p2 <= 'Z') ? (*p2 + 32) : *p2)) {
        return ((*p1 >= 'A' && *p1 <= 'Z') ? (*p1 + 32) : *p1) - ((*p2 >= 'A' && *p2 <= 'Z') ? (*p2 + 32) : *p2);
    }
    for (p1 = s1, p2 = s2; (*p1 == *p2) && *p1 != 0; p1 = p1 + 1, p2 = p2 + 1);
    return *p1 - *p2;
}

int CmprRows(const void* aa, const void* bb, int column, int reversed, int (*compare)(const char*, const char*)) {
    const char** rA = *(const char***)aa;
    const char** rB = *(const char***)bb;
    const char* left = reversed ? rB[column] : rA[column];
    const char* right = reversed ? rA[column] : rB[column];
    return compare(left, right);
}

void sortTable(const char*** rows, int n_rows, int n_cols, const char* argSpec, int (*compare)(const char*, const char*), int column, int reversed) {
    int i;
    int j;
    int temp;
    for (i = 0; i < n_rows - 1; i = i + 1) {
        for (j = 0; j < n_rows - i - 1; j = j + 1) {
            if (CmprRows(&rows[j], &rows[j + 1], column, reversed, compare) > 0) {
                const char** temp = rows[j];
                rows[j] = rows[j + 1];
                rows[j + 1] = temp;
            }
        }
    }
    return;
}
