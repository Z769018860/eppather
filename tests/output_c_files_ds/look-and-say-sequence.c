int func() {
    char a[2] = {'1', '\0'};
    char b[5];
    char x[5];
    int cnt;
    int len = 1;
    int i;
    int j;
    int k;
    
    for (i = 0; i < 1; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            x[j] = a[j];
        }
        for (len = 0, cnt = 1, k = 0; a[k] != '\0'; k = k + 1) {
            if (a[k] == a[k + 1]) {
                cnt = cnt + 1;
            } else {
                if (a[k]) {
                    b[len] = cnt + '0';
                    len = len + 1;
                    b[len] = a[k];
                    len = len + 1;
                    cnt = 1;
                }
            }
        }
        b[len] = '\0';
        for (j = 0; j < 5; j = j + 1) {
            a[j] = b[j];
        }
    }
    return;
}
