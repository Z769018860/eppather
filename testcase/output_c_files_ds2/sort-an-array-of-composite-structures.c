int cmprStrgs(int key1[5], int key2[5], int value1[5], int value2[5]) {
    int p1[5] = {0};
    int p2[5] = {0};
    int mrk1[5] = {0};
    int mrk2[5] = {0};
    int v1[5] = {0};
    int v2[5] = {0};
    int dgts[10] = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57};
    
    for (p1[0] = 0; p1[0] < 5; p1[0] = p1[0] + 1) {
        for (p2[0] = 0; p2[0] < 10; p2[0] = p2[0] + 1) {
            if (key1[p1[0]] == dgts[p2[0]]) {
                break;
            }
        }
    }
    
    for (p1[0] = 0; p1[0] < 5; p1[0] = p1[0] + 1) {
        for (p2[0] = 0; p2[0] < 5; p2[0] = p2[0] + 1) {
            if (((key1[p1[0]] >= 97 ? key1[p1[0]] - 32 : key1[p1[0]]) == (key2[p2[0]] >= 97 ? key2[p2[0]] - 32 : key2[p2[0]])) && key1[p1[0]] != 0) {
                p1[0] = p1[0] + 1;
                p2[0] = p2[0] + 1;
            } else {
                break;
            }
        }
    }
    
    if ((key1[p1[0]] >= 48 && key1[p1[0]] <= 57) && (key2[p2[0]] >= 48 && key2[p2[0]] <= 57)) {
        if ((key1[p1[0]] == 48) || (key2[p2[0]] == 48)) {
            for (; p1[0] > 0; p1[0] = p1[0] - 1) {
                p2[0] = p2[0] - 1;
                if (key1[p1[0]] != 48) {
                    break;
                }
            }
            if (!(key1[p1[0]] >= 48 && key1[p1[0]] <= 57)) {
                p1[0] = p1[0] + 1;
                p2[0] = p2[0] + 1;
            }
        }
        mrk1[0] = p1[0];
        mrk2[0] = p2[0];
        v1[0] = 0;
        for (; (key1[p1[0]] >= 48 && key1[p1[0]] <= 57); p1[0] = p1[0] + 1) {
            v1[0] = 10 * v1[0] + (key1[p1[0]] - 48);
        }
        v2[0] = 0;
        for (; (key2[p2[0]] >= 48 && key2[p2[0]] <= 57); p2[0] = p2[0] + 1) {
            v2[0] = 10 * v2[0] + (key2[p2[0]] - 48);
        }
        if (v1[0] == v2[0]) {
            return (p2[0] - mrk2[0]) - (p1[0] - mrk1[0]);
        }
        return v1[0] - v2[0];
    }
    if ((key1[p1[0]] >= 97 ? key1[p1[0]] - 32 : key1[p1[0]]) != (key2[p2[0]] >= 97 ? key2[p2[0]] - 32 : key2[p2[0]])) {
        return (key1[p1[0]] >= 97 ? key1[p1[0]] - 32 : key1[p1[0]]) - (key2[p2[0]] >= 97 ? key2[p2[0]] - 32 : key2[p2[0]]);
    }
    for (p1[0] = 0, p2[0] = 0; (key1[p1[0]] == key2[p2[0]]) && key1[p1[0]] != 0; p1[0] = p1[0] + 1, p2[0] = p2[0] + 1);
    return key1[p1[0]] - key2[p2[0]];
}

int maxstrlen(int a[5], int b[5]) {
    int la[5] = {0};
    int lb[5] = {0};
    for (la[0] = 0; a[la[0]] != 0 && la[0] < 5; la[0] = la[0] + 1);
    for (lb[0] = 0; b[lb[0]] != 0 && lb[0] < 5; lb[0] = lb[0] + 1);
    return (la[0] > lb[0]) ? la[0] : lb[0];
}

void combined(int key1[5], int key2[5], int value1[5], int value2[5]) {
    cmprStrgs(key1, key2, value1, value2);
    maxstrlen(key1, key2);
    return;
}
