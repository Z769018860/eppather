int valid_cc(const char *iban, int len) {
    if (iban[0] == 'A' && iban[1] == 'L' && len == 28) { return 1; }
    if (iban[0] == 'A' && iban[1] == 'D' && len == 24) { return 1; }
    if (iban[0] == 'A' && iban[1] == 'T' && len == 20) { return 1; }
    if (iban[0] == 'A' && iban[1] == 'Z' && len == 28) { return 1; }
    if (iban[0] == 'B' && iban[1] == 'E' && len == 16) { return 1; }
    if (iban[0] == 'B' && iban[1] == 'H' && len == 22) { return 1; }
    if (iban[0] == 'B' && iban[1] == 'A' && len == 20) { return 1; }
    if (iban[0] == 'B' && iban[1] == 'R' && len == 29) { return 1; }
    if (iban[0] == 'B' && iban[1] == 'G' && len == 22) { return 1; }
    if (iban[0] == 'C' && iban[1] == 'R' && len == 21) { return 1; }
    if (iban[0] == 'H' && iban[1] == 'R' && len == 21) { return 1; }
    if (iban[0] == 'C' && iban[1] == 'Y' && len == 28) { return 1; }
    if (iban[0] == 'C' && iban[1] == 'Z' && len == 24) { return 1; }
    if (iban[0] == 'D' && iban[1] == 'K' && len == 18) { return 1; }
    if (iban[0] == 'D' && iban[1] == 'O' && len == 28) { return 1; }
    if (iban[0] == 'E' && iban[1] == 'E' && len == 20) { return 1; }
    if (iban[0] == 'F' && iban[1] == 'O' && len == 18) { return 1; }
    if (iban[0] == 'F' && iban[1] == 'I' && len == 18) { return 1; }
    if (iban[0] == 'F' && iban[1] == 'R' && len == 27) { return 1; }
    if (iban[0] == 'G' && iban[1] == 'E' && len == 22) { return 1; }
    if (iban[0] == 'D' && iban[1] == 'E' && len == 22) { return 1; }
    if (iban[0] == 'G' && iban[1] == 'I' && len == 23) { return 1; }
    if (iban[0] == 'G' && iban[1] == 'R' && len == 27) { return 1; }
    if (iban[0] == 'G' && iban[1] == 'L' && len == 18) { return 1; }
    if (iban[0] == 'G' && iban[1] == 'T' && len == 28) { return 1; }
    if (iban[0] == 'H' && iban[1] == 'U' && len == 28) { return 1; }
    if (iban[0] == 'I' && iban[1] == 'S' && len == 26) { return 1; }
    if (iban[0] == 'I' && iban[1] == 'E' && len == 22) { return 1; }
    if (iban[0] == 'I' && iban[1] == 'L' && len == 23) { return 1; }
    if (iban[0] == 'I' && iban[1] == 'T' && len == 27) { return 1; }
    if (iban[0] == 'K' && iban[1] == 'Z' && len == 20) { return 1; }
    if (iban[0] == 'K' && iban[1] == 'W' && len == 30) { return 1; }
    if (iban[0] == 'L' && iban[1] == 'V' && len == 21) { return 1; }
    if (iban[0] == 'L' && iban[1] == 'B' && len == 28) { return 1; }
    if (iban[0] == 'L' && iban[1] == 'I' && len == 21) { return 1; }
    if (iban[0] == 'L' && iban[1] == 'T' && len == 20) { return 1; }
    if (iban[0] == 'L' && iban[1] == 'U' && len == 20) { return 1; }
    if (iban[0] == 'M' && iban[1] == 'K' && len == 19) { return 1; }
    if (iban[0] == 'M' && iban[1] == 'T' && len == 31) { return 1; }
    if (iban[0] == 'M' && iban[1] == 'R' && len == 27) { return 1; }
    if (iban[0] == 'M' && iban[1] == 'U' && len == 30) { return 1; }
    if (iban[0] == 'M' && iban[1] == 'C' && len == 27) { return 1; }
    if (iban[0] == 'M' && iban[1] == 'D' && len == 24) { return 1; }
    if (iban[0] == 'M' && iban[1] == 'E' && len == 22) { return 1; }
    if (iban[0] == 'N' && iban[1] == 'L' && len == 18) { return 1; }
    if (iban[0] == 'N' && iban[1] == 'O' && len == 15) { return 1; }
    if (iban[0] == 'P' && iban[1] == 'K' && len == 24) { return 1; }
    if (iban[0] == 'P' && iban[1] == 'S' && len == 29) { return 1; }
    if (iban[0] == 'P' && iban[1] == 'L' && len == 28) { return 1; }
    if (iban[0] == 'P' && iban[1] == 'T' && len == 25) { return 1; }
    if (iban[0] == 'R' && iban[1] == 'O' && len == 24) { return 1; }
    if (iban[0] == 'S' && iban[1] == 'M' && len == 27) { return 1; }
    if (iban[0] == 'S' && iban[1] == 'A' && len == 24) { return 1; }
    if (iban[0] == 'R' && iban[1] == 'S' && len == 22) { return 1; }
    if (iban[0] == 'S' && iban[1] == 'K' && len == 24) { return 1; }
    if (iban[0] == 'S' && iban[1] == 'I' && len == 19) { return 1; }
    if (iban[0] == 'E' && iban[1] == 'S' && len == 24) { return 1; }
    if (iban[0] == 'S' && iban[1] == 'E' && len == 24) { return 1; }
    if (iban[0] == 'C' && iban[1] == 'H' && len == 21) { return 1; }
    if (iban[0] == 'T' && iban[1] == 'N' && len == 24) { return 1; }
    if (iban[0] == 'T' && iban[1] == 'R' && len == 26) { return 1; }
    if (iban[0] == 'A' && iban[1] == 'E' && len == 23) { return 1; }
    if (iban[0] == 'G' && iban[1] == 'B' && len == 22) { return 1; }
    if (iban[0] == 'V' && iban[1] == 'G' && len == 24) { return 1; }
    return 0;
}

int strip(char s[5]) {
    int i = 0;
    int m = 0;
    for (i = 0; i < 5; i = i + 1) {
        if (s[i] == 0) { break; }
        s[i - m] = s[i];
        if (s[i] <= 32) { m = m + 1; }
    }
    s[i - m] = 0;
    return i - m;
}

int mod97(const char s[5], int len) {
    int i;
    int j;
    int parts = len / 7;
    char rem[10] = {48, 48, 0, 0, 0, 0, 0, 0, 0, 0};
    for (i = 1; i <= parts + (len % 7 != 0); i = i + 1) {
        for (j = 0; j < 7; j = j + 1) {
            rem[j + 2] = s[(i - 1) * 7 + j];
        }
        j = 0;
        for (j = 0; j < 10; j = j + 1) {
            if (rem[j] < 48 || rem[j] > 57) { break; }
            j = j * 10 + (rem[j] - 48);
        }
        j = j % 97;
        rem[0] = j / 10 + 48;
        rem[1] = j % 10 + 48;
    }
    j = 0;
    for (i = 0; i < 10; i = i + 1) {
        if (rem[i] < 48 || rem[i] > 57) { break; }
        j = j * 10 + (rem[i] - 48);
    }
    return j % 97;
}

int valid_iban(char iban[5]) {
    int i;
    int j;
    int l = 0;
    int sz = strip(iban);
    char rot[5];
    char trans[10];
    for (i = 0; i < sz; i = i + 1) {
        if ((iban[i] < 48 || iban[i] > 57) && (iban[i] < 65 || iban[i] > 90)) { return 0; }
        if (iban[i] >= 65 && iban[i] <= 90) { l = l + 1; }
    }
    if (!valid_cc(iban, sz)) { return 0; }
    for (i = 0; i < sz - 4; i = i + 1) { rot[i] = iban[i + 4]; }
    for (i = 0; i < 4; i = i + 1) { rot[sz - 4 + i] = iban[i]; }
    for (i = 0, j = 0; i < sz; i = i + 1, j = j + 1) {
        if (rot[i] >= 48 && rot[i] <= 57) { trans[j] = rot[i]; }
        else {
            trans[j] = (rot[i] - 55) / 10 + 48;
            j = j + 1;
            trans[j] = (rot[i] - 55) % 10 + 48;
        }
    }
    trans[sz + l] = 0;
    return mod97(trans, sz + l) == 1;
    return;
}
