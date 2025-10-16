int func() {
    int PI2_fixed = 62832;
    int n;
    int i;
    int c;
    int s;
    int a;
    
    for (n = 1; n < 10; n = n + 1) {
        for (i = 0; i < n; i = i + 1) {
            c = 0;
            s = 0;
            if (i == 0) {
                c = 10000;
            } else {
                if (n == 4 * i) {
                    s = 10000;
                } else {
                    if (n == 2 * i) {
                        c = -10000;
                    } else {
                        if (3 * n == 4 * i) {
                            s = -10000;
                        } else {
                            a = i * PI2_fixed / n;
                            c = 10000 - (a * a) / 20000 + (a * a * a * a) / 24000000;
                            s = a - (a * a * a) / 600000 + (a * a * a * a * a) / 1200000000;
                        }
                    }
                }
            }
        }
    }
    return;
}
