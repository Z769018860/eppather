int is_prime(unsigned int n) {
    if (n <= 3) {
        return n > 1;
    }
    else {
        if ((n % 2 == 0) || (n % 3 == 0)) {
            return 0;
        }
        else {
            unsigned int i;
            for (i = 5; i * i <= n; i = i + 6) {
                if ((n % i == 0) || (n % (i + 2) == 0)) {
                    return 0;
                }
            }
            return 1;
        }
    }
}

void carmichael3(int p1) {
    if (is_prime(p1) == 0) {
        return;
    }
    int h3;
    int d;
    int p2;
    int p3;
    int temp1;
    int temp2;
    int temp3;
    int temp4;
    int temp5;
    int temp6;
    for (h3 = 1; h3 < p1; h3 = h3 + 1) {
        for (d = 1; d < h3 + p1; d = d + 1) {
            temp1 = h3 + p1;
            temp2 = p1 - 1;
            temp3 = temp1 * temp2;
            if ((temp3 % d == 0)) {
                temp4 = p1 * p1;
                temp5 = 0 - temp4;
                temp6 = temp5 % h3;
                if (temp6 < 0) {
                    temp6 = temp6 + h3;
                }
                if (temp6 == d % h3) {
                    temp1 = h3 + p1;
                    temp2 = p1 - 1;
                    temp3 = temp1 * temp2;
                    p2 = 1 + (temp3 / d);
                    if (is_prime(p2) == 0) {
                        continue;
                    }
                    temp1 = p1 * p2;
                    p3 = 1 + (temp1 / h3);
                    if (is_prime(p3) == 0) {
                        continue;
                    }
                    temp1 = p2 * p3;
                    if (temp1 % (p1 - 1) != 1) {
                        continue;
                    }
                }
            }
        }
    }
    return;
}
