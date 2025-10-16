int lucas_lehmer(unsigned long p) {
    int res;
    unsigned long k;
    unsigned long tlim;
    unsigned long q;
    unsigned long V[4] = {0};
    unsigned long mp[4] = {0};
    unsigned long t[4] = {0};
    unsigned long temp[4] = {0};
    unsigned long carry;
    int cmp;

    if (p == 2) {
        return 1;
    }
    if ((p & 1) == 0) {
        return 0;
    }

    for (k = 2; k * k <= p; k = k + 1) {
        if (p % k == 0) {
            return 0;
        }
    }

    if (p < 23) {
        if (p == 11) {
            return 0;
        } else {
            return 1;
        }
    }

    mp[0] = 1;
    for (k = 0; k < p; k = k + 1) {
        carry = mp[0] >> 31;
        mp[0] = mp[0] << 1;
        mp[1] = (mp[1] << 1) | carry;
        carry = mp[1] >> 31;
        mp[1] = mp[1] << 1;
        mp[2] = (mp[2] << 1) | carry;
        carry = mp[2] >> 31;
        mp[2] = mp[2] << 1;
        mp[3] = (mp[3] << 1) | carry;
    }
    mp[0] = mp[0] - 1;

    if (p > 3 && p % 4 == 3) {
        t[0] = p * 2 + 1;
        for (k = 2; k * k <= t[0]; k = k + 1) {
            if (t[0] % k == 0) {
                break;
            }
        }
        if (k * k > t[0]) {
            if (mp[0] % t[0] == 0 && mp[1] == 0 && mp[2] == 0 && mp[3] == 0) {
                return 0;
            }
        }
    }

    tlim = p / 2;
    if (tlim > (~0UL / (2 * p))) {
        tlim = ~0UL / (2 * p);
    }
    for (k = 1; k < tlim; k = k + 1) {
        q = 2 * p * k + 1;
        if ((q % 8 == 1 || q % 8 == 7) && q % 3 != 0 && q % 5 != 0 && q % 7 != 0) {
            if (mp[0] % q == 0 && mp[1] == 0 && mp[2] == 0 && mp[3] == 0) {
                return 0;
            }
        }
    }

    V[0] = 4;
    for (k = 3; k <= p; k = k + 1) {
        carry = 0;
        temp[0] = V[0] * V[0];
        temp[1] = V[0] * V[1] * 2 + (temp[0] >> 32);
        temp[0] = temp[0] & 0xFFFFFFFF;
        temp[2] = V[0] * V[2] * 2 + V[1] * V[1] + (temp[1] >> 32);
        temp[1] = temp[1] & 0xFFFFFFFF;
        temp[3] = V[0] * V[3] * 2 + V[1] * V[2] * 2 + (temp[2] >> 32);
        temp[2] = temp[2] & 0xFFFFFFFF;
        temp[3] = temp[3] & 0xFFFFFFFF;
        V[0] = temp[0] - 2;
        V[1] = temp[1] - (V[0] > temp[0]);
        V[2] = temp[2] - (V[1] > temp[1]);
        V[3] = temp[3] - (V[2] > temp[2]);

        if (V[3] & 0x80000000) {
            V[0] = V[0] + mp[0];
            V[1] = V[1] + mp[1] + (V[0] < mp[0]);
            V[2] = V[2] + mp[2] + (V[1] < mp[1]);
            V[3] = V[3] + mp[3] + (V[2] < mp[2]);
        }

        t[0] = V[0] & ((1UL << p) - 1);
        t[1] = V[1] & ((1UL << (p - 32)) - 1);
        V[0] = (V[0] >> p) | (V[1] << (32 - p));
        V[1] = (V[1] >> p) | (V[2] << (32 - p));
        V[2] = (V[2] >> p) | (V[3] << (32 - p));
        V[3] = V[3] >> p;
        V[0] = V[0] + t[0];
        V[1] = V[1] + t[1] + (V[0] < t[0]);
        V[2] = V[2] + (V[1] < t[1]);
        V[3] = V[3] + (V[2] < 0);

        cmp = 1;
        if (V[3] < mp[3]) {
            cmp = -1;
        } else if (V[3] == mp[3]) {
            if (V[2] < mp[2]) {
                cmp = -1;
            } else if (V[2] == mp[2]) {
                if (V[1] < mp[1]) {
                    cmp = -1;
                } else if (V[1] == mp[1]) {
                    if (V[0] < mp[0]) {
                        cmp = -1;
                    } else if (V[0] == mp[0]) {
                        cmp = 0;
                    }
                }
            }
        }
        while (cmp >= 0) {
            V[0] = V[0] - mp[0];
            V[1] = V[1] - mp[1] - (V[0] > ~mp[0]);
            V[2] = V[2] - mp[2] - (V[1] > ~mp[1]);
            V[3] = V[3] - mp[3] - (V[2] > ~mp[2]);
            cmp = 1;
            if (V[3] < mp[3]) {
                cmp = -1;
            } else if (V[3] == mp[3]) {
                if (V[2] < mp[2]) {
                    cmp = -1;
                } else if (V[2] == mp[2]) {
                    if (V[1] < mp[1]) {
                        cmp = -1;
                    } else if (V[1] == mp[1]) {
                        if (V[0] < mp[0]) {
                            cmp = -1;
                        } else if (V[0] == mp[0]) {
                            cmp = 0;
                        }
                    }
                }
            }
        }
    }

    if (V[0] == 0 && V[1] == 0 && V[2] == 0 && V[3] == 0) {
        res = 1;
    } else {
        res = 0;
    }
    return res;
}
