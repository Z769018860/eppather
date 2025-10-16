int func() {
    char s[23] = {'H','e','l','l','o',',','H','o','w',',','A','r','e',',','Y','o','u',',','T','o','d','a','y'};
    char a[5][20];
    int n = 0;
    int nn;
    int i = 0;
    int j = 0;
    int k = 0;

    for (i = 0; i < 23; i = i + 1) {
        if (s[i] == ',') {
            a[n][j] = '\0';
            n = n + 1;
            j = 0;
            if (n >= 4) {
                break;
            }
        } else {
            a[n][j] = s[i];
            j = j + 1;
        }
    }
    a[n][j] = '\0';

    for (nn = 0; nn <= n; nn = nn + 1) {
        for (k = 0; a[nn][k] != '\0'; k = k + 1) {
        }
    }
    
    return;
}
