void func(int n1) {
    int n[5];
    int i[5];
    int a[5];
    int c[5];
    int s[5];
    int PI2[5];
    PI2[0] = 62831853;
    
    for (n[0] = 1; n[0] < 5; n[0] = n[0] + 1) {
        for (i[0] = 0; i[0] < n[0]; i[0] = i[0] + 1) {
            c[0] = 0;
            s[0] = 0;
            if (i[0] == 0) {
                c[0] = 1;
            } else {
                if (n[0] == 4 * i[0]) {
                    s[0] = 1;
                } else {
                    if (n[0] == 2 * i[0]) {
                        c[0] = -1;
                    } else {
                        if (3 * n[0] == 4 * i[0]) {
                            s[0] = -1;
                        } else {
                            a[0] = i[0] * PI2[0] / n[0];
                        }
                    }
                }
            }
        }
    }
    return;
}
