int lucas_lehmer(int p)
{
    int V[5] = {0};
    int mp[5] = {0};
    int t[5] = {0};
    int k;
    int tlim;
    int res;
    int q;
    int i;

    if (p == 2) { return 1; }
    if ((p & 1) == 0) { return 0; }

    t[0] = p;
    for (i = 0; i < 5; i = i + 1) {
        if (t[i] % 2 == 0 && t[i] != 2) { 
            return 0; 
        }
    }

    if (p < 23) { 
        if (p != 11) { 
            return 1; 
        } else { 
            return 0; 
        }
    }

    mp[0] = 1;
    for (i = 0; i < p; i = i + 1) {
        mp[0] = mp[0] * 2;
    }
    mp[0] = mp[0] - 1;

    if (p > 3 && p % 4 == 3) {
        t[0] = t[0] * 2;
        t[0] = t[0] + 1;
        for (i = 0; i < 5; i = i + 1) {
            if (t[i] % 2 == 0 && t[i] != 2) { 
                return 0; 
            }
        }
        if (mp[0] % t[0] == 0) { 
            return 0; 
        }
    }

    tlim = p / 2;
    if (tlim > (2147483647 / (2 * p))) {
        tlim = 2147483647 / (2 * p);
    }
    for (k = 1; k < tlim; k = k + 1) {
        q = 2 * p * k + 1;
        if ((q % 8 == 1 || q % 8 == 7) && q % 3 != 0 && q % 5 != 0 && q % 7 != 0 && mp[0] % q == 0) { 
            return 0; 
        }
    }

    V[0] = 4;
    for (k = 3; k <= p; k = k + 1) {
        V[0] = V[0] * V[0];
        V[0] = V[0] - 2;
        if (V[0] < 0) { 
            V[0] = V[0] + mp[0]; 
        }
        t[0] = V[0] % (1 << p);
        V[0] = V[0] / (1 << p);
        V[0] = V[0] + t[0];
        while (V[0] >= mp[0]) { 
            V[0] = V[0] - mp[0]; 
        }
    }
    res = (V[0] == 0) ? 1 : 0;
    return res;
}
