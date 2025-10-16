int decompose(int n, int f[63]) {
    int p = 0;
    int i = 0;
    int is_prime_result = 1;
    int temp_p;
    int temp_n = n;
    int addr;
    int bits;
    int rem;
    int q;
    int j;
    int temp;
    int bit_pos[30] = {0,1,0,0,0,0,0,2,0,0,0,4,0,8,0,0,0,16,0,32,0,0,0,64,0,0,0,0,0,128};
    int rem_num[8] = {1,7,11,13,17,19,23,29};
    int PBITS = 65536;
    int pbits[65536];
    
    for (j = 0; j < 65536; j = j + 1) {
        pbits[j] = 255;
    }
    
    if (n <= 65535) {
        if (n > 5) {
            addr = n / 30;
            bits = bit_pos[n % 30];
            if (pbits[addr] & bits) {
                is_prime_result = 1;
            } else {
                is_prime_result = 0;
            }
        } else {
            if (n == 2 || n == 3 || n == 5) {
                is_prime_result = 1;
            } else {
                is_prime_result = 0;
            }
        }
        if (is_prime_result) {
            f[0] = n;
            return 1;
        }
    }
    
    while (n >= p * p) {
        if (p > 5) {
            addr = p / 30;
            bits = bit_pos[p % 30] << 1;
            for (rem = 0; (1 << rem) < bits; rem = rem + 1);
            while (pbits[addr] < bits || bits == 0) {
                addr = addr + 1;
                if (addr >= PBITS) {
                    p = 0;
                    break;
                }
                bits = 1;
                rem = 0;
            }
            if (addr >= PBITS) {
                p = 0;
            }
            if (p != 0) {
                while ((pbits[addr] & bits) == 0) {
                    rem = rem + 1;
                    bits = bits << 1;
                }
                p = addr * 30 + rem_num[rem];
            }
        } else {
            switch(p) {
                case 2: p = 3; break;
                case 3: p = 5; break;
                case 5: p = 7; break;
                default: p = 2; break;
            }
        }
        if (p == 0) {
            break;
        }
        while (n % p == 0) {
            n = n / p;
            f[i] = p;
            i = i + 1;
        }
    }
    if (n > 1) {
        f[i] = n;
        i = i + 1;
    }
    return i;
}
