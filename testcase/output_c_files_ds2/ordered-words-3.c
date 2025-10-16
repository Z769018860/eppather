int ordered(char s[5], char end[5][5]) {
    int r[5];
    r[0] = 1;
    int i[5];
    i[0] = 0;
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        if (s[i[0] + 1] != 10 && s[i[0] + 1] != 13 && s[i[0] + 1] != 0) {
            if (s[i[0] + 1] < s[i[0]]) {
                r[0] = 0;
            }
        } else {
            break;
        }
    }
    end[0][0] = s[i[0] + 1];
    return r[0];
}
