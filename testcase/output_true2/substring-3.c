int substring(int s[5], int n, int m, int result[5]) {
    int i;
    int j;
    int len;
    int temp[5];
    
    if (s[0] == 0) {
        return 0;
    }
    
    len = 0;
    for (i = 0; i < 5; i = i + 1) {
        if (s[i] == 0) {
            break;
        }
        len = len + 1;
    }
    
    if (m < 0) {
        m = len + m - n + 1;
    }
    
    if (n < 0 || m < 0) {
        return 0;
    }
    
    for (i = 0; i < n; i = i + 1) {
        if (s[i] == 0) {
            return 0;
        }
    }
    
    for (j = 0; j < m; j = j + 1) {
        if (s[n + j] == 0) {
            break;
        }
        result[j] = s[n + j];
    }
    result[j] = 0;
    
    return 1;
}

int str_wholeless1(int s[5], int result[5]) {
    int len;
    int i;
    
    len = 0;
    for (i = 0; i < 5; i = i + 1) {
        if (s[i] == 0) {
            break;
        }
        len = len + 1;
    }
    
    return substring(s, 0, len - 1, result);
}

int str_fromch(int s[5], int ch, int m, int result[5]) {
    int i;
    int pos;
    
    pos = 0;
    for (i = 0; i < 5; i = i + 1) {
        if (s[i] == 0) {
            break;
        }
        if (s[i] == ch) {
            pos = i;
            break;
        }
    }
    
    return substring(s, pos, m, result);
}

int str_fromstr(int s[5], int in[5], int m, int result[5]) {
    int i;
    int j;
    int k;
    int found;
    int pos;
    
    pos = 0;
    found = 0;
    for (i = 0; i < 5; i = i + 1) {
        if (s[i] == 0) {
            break;
        }
        if (s[i] == in[0]) {
            found = 1;
            for (j = 0, k = i; j < 5; j = j + 1, k = k + 1) {
                if (in[j] == 0) {
                    pos = i;
                    break;
                }
                if (s[k] != in[j]) {
                    found = 0;
                    break;
                }
            }
            if (found) {
                break;
            }
        }
    }
    
    return substring(s, pos, m, result);
}

void merge_functions(int s[5], int n, int m, int ch, int in[5], int result[5]) {
    int temp_result1[5];
    int temp_result2[5];
    int temp_result3[5];
    
    substring(s, n, m, result);
    str_wholeless1(s, temp_result1);
    str_fromch(s, ch, m, temp_result2);
    str_fromstr(s, in, m, temp_result3);
    
    return;
}
