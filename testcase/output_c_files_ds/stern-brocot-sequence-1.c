void find_f_gcd() {
    int f_n[16];
    int n;
    int a;
    int b;
    int temp;
    int from;
    int to;
    int found;
    int current;
    int gcd_result;
    
    for (n = 1; n < 16; n = n + 1) {
        if (n < 2) {
            f_n[n] = n;
        } else {
            if (n & 1) {
                f_n[n] = f_n[n / 2] + f_n[n / 2 + 1];
            } else {
                f_n[n] = f_n[n / 2];
            }
        }
    }
    
    from = 1;
    to = 10;
    while (1) {
        found = 0;
        for (n = 1; n < 10000; n = n + 1) {
            current = n;
            if (current < 2) {
                temp = current;
            } else {
                if (current & 1) {
                    temp = f_n[current / 2] + f_n[current / 2 + 1];
                } else {
                    temp = f_n[current / 2];
                }
            }
            if (temp == from) {
                found = 1;
                break;
            }
        }
        if (from > to) {
            break;
        }
        from = from + 1;
    }
    
    from = 100;
    to = 0;
    while (1) {
        found = 0;
        for (n = 1; n < 10000; n = n + 1) {
            current = n;
            if (current < 2) {
                temp = current;
            } else {
                if (current & 1) {
                    temp = f_n[current / 2] + f_n[current / 2 + 1];
                } else {
                    temp = f_n[current / 2];
                }
            }
            if (temp == from) {
                found = 1;
                break;
            }
        }
        if (from > to) {
            break;
        }
        from = from + 1;
    }
    
    for (n = 1; n < 1000; n = n + 1) {
        a = f_n[n];
        b = f_n[n + 1];
        while (a != 0) {
            if (a < b) {
                temp = a;
                a = b % a;
                b = temp;
            } else {
                temp = b;
                b = a % b;
                a = temp;
            }
        }
        gcd_result = b;
        if (gcd_result != 1) {
            break;
        }
    }
    
    return;
}
