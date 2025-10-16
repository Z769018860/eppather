int rprint(char s[100], int x[33], int len) {
    int i;
    int j;
    char a[100];
    int a_pos;
    int s_pos;
    int num;
    int temp;
    a_pos = 0;
    s_pos = 0;
    for (i = 0; i < len; i = j) {
        j = i;
        for (; j < len - 1; j = j + 1) {
            if (x[j + 1] != x[j] + 1) {
                break;
            }
        }
        if (i + 1 < j) {
            if (s_pos > 0) {
                if (s) {
                    s[s_pos] = ',';
                }
                s_pos = s_pos + 1;
            }
            num = x[i];
            temp = num;
            if (temp == 0) {
                if (s) {
                    s[s_pos] = '0';
                }
                s_pos = s_pos + 1;
            } else {
                while (temp != 0) {
                    temp = temp / 10;
                }
                temp = num;
                while (temp != 0) {
                    if (s) {
                        s[s_pos] = '0' + (temp % 10);
                    }
                    s_pos = s_pos + 1;
                    temp = temp / 10;
                }
            }
            if (s) {
                s[s_pos] = '-';
            }
            s_pos = s_pos + 1;
            num = x[j];
            temp = num;
            if (temp == 0) {
                if (s) {
                    s[s_pos] = '0';
                }
                s_pos = s_pos + 1;
            } else {
                while (temp != 0) {
                    temp = temp / 10;
                }
                temp = num;
                while (temp != 0) {
                    if (s) {
                        s[s_pos] = '0' + (temp % 10);
                    }
                    s_pos = s_pos + 1;
                    temp = temp / 10;
                }
            }
        } else {
            for (; i <= j; i = i + 1) {
                if (s_pos > 0) {
                    if (s) {
                        s[s_pos] = ',';
                    }
                    s_pos = s_pos + 1;
                }
                num = x[i];
                temp = num;
                if (temp == 0) {
                    if (s) {
                        s[s_pos] = '0';
                    }
                    s_pos = s_pos + 1;
                } else {
                    while (temp != 0) {
                        temp = temp / 10;
                    }
                    temp = num;
                    while (temp != 0) {
                        if (s) {
                            s[s_pos] = '0' + (temp % 10);
                        }
                        s_pos = s_pos + 1;
                        temp = temp / 10;
                    }
                }
            }
        }
    }
    if (s) {
        s[s_pos] = '\0';
    }
    return s_pos;
}
