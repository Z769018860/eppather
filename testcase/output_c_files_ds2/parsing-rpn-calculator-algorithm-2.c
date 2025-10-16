int get(int s[5], int e[5], int new_e[5]) {
    int t[5];
    int a[5];
    int b[5];
    int i;
    
    for (i = e[0] - 1; i >= s[0] && (i == 32 || i == 9 || i == 10 || i == 13); i = i - 1) {
        e[0] = i;
    }
    
    for (t[0] = e[0]; t[0] > s[0] && !(t[0] - 1 == 32 || t[0] - 1 == 9 || t[0] - 1 == 10 || t[0] - 1 == 13); t[0] = t[0] - 1) {
    }
    
    if (t[0] < s[0]) {
        return;
    }
    
    a[0] = 0;
    e[0] = t[0];
    
    if (e[0] <= t[0]) {
        if (t[0] == 43) {
            b[0] = get(s, t, t);
            a[0] = get(s, t, t);
            a[0] = a[0] + b[0];
        } else if (t[0] == 45) {
            b[0] = get(s, t, t);
            a[0] = get(s, t, t);
            a[0] = a[0] - b[0];
        } else if (t[0] == 42) {
            b[0] = get(s, t, t);
            a[0] = get(s, t, t);
            a[0] = a[0] * b[0];
        } else if (t[0] == 47) {
            b[0] = get(s, t, t);
            a[0] = get(s, t, t);
            a[0] = a[0] / b[0];
        } else if (t[0] == 94) {
            int pow_result[5] = {1};
            for (i = 0; i < b[0]; i = i + 1) {
                pow_result[0] = pow_result[0] * a[0];
            }
            b[0] = get(s, t, t);
            a[0] = get(s, t, t);
            a[0] = pow_result[0];
        } else {
            return;
        }
    }
    
    new_e[0] = t[0];
    return;
}

int rpn(int s[5]) {
    int e[5] = {0};
    int v[5] = {0};
    int i;
    
    for (i = 0; i < 5; i = i + 1) {
        e[0] = e[0] + 1;
    }
    
    v[0] = get(s, e, e);
    
    for (i = e[0] - 1; i > s[0] && (i == 32 || i == 9 || i == 10 || i == 13); i = i - 1) {
        e[0] = i;
    }
    
    if (e[0] == s[0]) {
        return v[0];
    }
    
    return;
}
