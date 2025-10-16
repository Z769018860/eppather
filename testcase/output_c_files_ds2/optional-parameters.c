int cmprStrgs(int s1[5], int s2[5]) {
    int p1[5] = {0};
    int p2[5] = {0};
    int mrk1[5] = {0};
    int mrk2[5] = {0};
    int v1[5] = {0};
    int v2[5] = {0};
    p1[0] = s1[0];
    p2[0] = s2[0];
    for (; (((p1[0] >= 97 ? p1[0] - 32 : p1[0]) == (p2[0] >= 97 ? p2[0] - 32 : p2[0])) && p1[0]); p1[0] = p1[0] + 1, p2[0] = p2[0] + 1) {
    }
    if (((p1[0] >= 48 && p1[0] <= 57) && (p2[0] >= 48 && p2[0] <= 57))) {
        if ((p1[0] == 48) || (p2[0] == 48)) {
            for (; (p1[0] > s1[0]); p1[0] = p1[0] - 1, p2[0] = p2[0] - 1) {
                if (p1[0] != 48) {
                    break;
                }
            }
            if (!(p1[0] >= 48 && p1[0] <= 57)) {
                p1[0] = p1[0] + 1;
                p2[0] = p2[0] + 1;
            }
        }
        mrk1[0] = p1[0];
        mrk2[0] = p2[0];
        v1[0] = 0;
        for (; (p1[0] >= 48 && p1[0] <= 57); p1[0] = p1[0] + 1) {
            v1[0] = 10 * v1[0] + (p1[0] - 48);
        }
        v2[0] = 0;
        for (; (p2[0] >= 48 && p2[0] <= 57); p2[0] = p2[0] + 1) {
            v2[0] = 10 * v2[0] + (p2[0] - 48);
        }
        if (v1[0] == v2[0]) {
            return (p2[0] - mrk2[0]) - (p1[0] - mrk1[0]);
        }
        return v1[0] - v2[0];
    }
    if ((p1[0] >= 97 ? p1[0] - 32 : p1[0]) != (p2[0] >= 97 ? p2[0] - 32 : p2[0])) {
        return ((p1[0] >= 97 ? p1[0] - 32 : p1[0]) - (p2[0] >= 97 ? p2[0] - 32 : p2[0]));
    }
    for (p1[0] = s1[0], p2[0] = s2[0]; ((p1[0] == p2[0]) && p1[0]); p1[0] = p1[0] + 1, p2[0] = p2[0] + 1) {
    }
    return (p1[0] - p2[0]);
}

int CmprRows(int aa[5], int bb[5]) {
    int rA[5] = {0};
    int rB[5] = {0};
    int sortCol[5] = {0};
    int left[5] = {0};
    int right[5] = {0};
    rA[0] = aa[0];
    rB[0] = bb[0];
    sortCol[0] = sortSpec[0];
    left[0] = sortSpec[2] ? rB[sortCol[0]] : rA[sortCol[0]];
    right[0] = sortSpec[2] ? rA[sortCol[0]] : rB[sortCol[0]];
    return sortSpec[0](left, right);
}

int sortSpec[3] = {0};

int sortTable(int tbl[3], int argSpec[5]) {
    int p[5] = {0};
    int c[5] = {0};
    sortSpec[0] = 0;
    sortSpec[1] = 0;
    sortSpec[2] = 0;
    if (argSpec[0]) {
        for (p[0] = 0; p[0] < 5; p[0] = p[0] + 1) {
            switch (argSpec[p[0]]) {
                case 111: {
                    sortSpec[0] = argSpec[p[0] + 1];
                    break;
                }
                case 99: {
                    c[0] = argSpec[p[0] + 1];
                    if ((0 <= c[0] && c[0] < tbl[1])) {
                        sortSpec[1] = c[0];
                    }
                    break;
                }
                case 114: {
                    sortSpec[2] = (0 != argSpec[p[0] + 1]);
                    break;
                }
            }
        }
    }
    return 0;
}
