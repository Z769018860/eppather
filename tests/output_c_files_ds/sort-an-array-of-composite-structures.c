int cmprStrgs(int s1_key[100], int s2_key[100]) {
    int p1 = 0;
    int p2 = 0;
    int mrk1 = 0;
    int mrk2 = 0;
    int v1 = 0;
    int v2 = 0;
    int temp1 = 0;
    int temp2 = 0;
    
    while ((((s1_key[p1] >= 'A' && s1_key[p1] <= 'Z') ? s1_key[p1] + 32 : s1_key[p1]) == ((s2_key[p2] >= 'A' && s2_key[p2] <= 'Z') ? s2_key[p2] + 32 : s2_key[p2])) && s1_key[p1] != 0) {
        p1 = p1 + 1;
        p2 = p2 + 1;
    }
    
    if ((s1_key[p1] >= '0' && s1_key[p1] <= '9') && (s2_key[p2] >= '0' && s2_key[p2] <= '9')) {
        if ((s1_key[p1] == '0') || (s2_key[p2] == '0')) {
            while (p1 > 0) {
                p1 = p1 - 1;
                p2 = p2 - 1;
                if (s1_key[p1] != '0') {
                    break;
                }
            }
            if (!(s1_key[p1] >= '0' && s1_key[p1] <= '9')) {
                p1 = p1 + 1;
                p2 = p2 + 1;
            }
        }
        mrk1 = p1;
        mrk2 = p2;
        v1 = 0;
        while (s1_key[p1] >= '0' && s1_key[p1] <= '9') {
            v1 = 10 * v1 + (s1_key[p1] - '0');
            p1 = p1 + 1;
        }
        v2 = 0;
        while (s2_key[p2] >= '0' && s2_key[p2] <= '9') {
            v2 = 10 * v2 + (s2_key[p2] - '0');
            p2 = p2 + 1;
        }
        if (v1 == v2) {
            return (p2 - mrk2) - (p1 - mrk1);
        }
        return v1 - v2;
    }
    
    if (((s1_key[p1] >= 'A' && s1_key[p1] <= 'Z') ? s1_key[p1] + 32 : s1_key[p1]) != ((s2_key[p2] >= 'A' && s2_key[p2] <= 'Z') ? s2_key[p2] + 32 : s2_key[p2])) {
        return ((s1_key[p1] >= 'A' && s1_key[p1] <= 'Z') ? s1_key[p1] + 32 : s1_key[p1]) - ((s2_key[p2] >= 'A' && s2_key[p2] <= 'Z') ? s2_key[p2] + 32 : s2_key[p2]);
    }
    
    for (p1 = 0, p2 = 0; (s1_key[p1] == s2_key[p2]) && s1_key[p1] != 0; p1 = p1 + 1, p2 = p2 + 1) {
    }
    return s1_key[p1] - s2_key[p2];
    return;
}
