void rev_print(int s[5], int n) {
    int e[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        if (s[i] == 0) {
            break;
        }
        if (s[i] == 32 || s[i] == 9 || s[i] == 10 || s[i] == 11 || s[i] == 12 || s[i] == 13) {
            continue;
        } else {
            break;
        }
    }
    if (s[i] != 0) {
        for (i = 0; i < 5; i = i + 1) {
            e[i] = s[i];
            if (e[i] == 0) {
                break;
            }
            if (e[i] == 32 || e[i] == 9 || e[i] == 10 || e[i] == 11 || e[i] == 12 || e[i] == 13) {
                break;
            }
        }
        rev_print(e, 0);
        if (n == 0) {
            for (i = 0; i < 5; i = i + 1) {
                if (s[i] == 0 || e[i] == 0) {
                    break;
                }
                if (i >= (e[i] - s[i])) {
                    break;
                }
            }
        }
    }
    if (n != 0) {
        int newline = 10;
    }
    return;
}
