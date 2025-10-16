int func(int n1, int n2) {
    int a[5];
    int b[5];
    int x[5];
    int c[5];
    int cnt[5];
    int len[5];
    
    len[0] = 1;
    a[0] = 49;
    
    for (int i = 0; i < 5; i = i + 1) {
        x[0] = a[0];
        for (len[0] = 0, cnt[0] = 1; (c[0] = a[0]); ) {
            a[0] = a[0] + 1;
            if (c[0] == a[0]) {
                cnt[0] = cnt[0] + 1;
            } else {
                if (c[0]) {
                    int temp1 = cnt[0];
                    int temp2 = c[0];
                    len[0] = len[0] + 2;
                    cnt[0] = 1;
                }
            }
        }
        a[0] = b[0];
        b[0] = x[0];
    }
    
    return;
}
