int decompose(int n, int f[63])
{
    int p[5] = {0};
    int i[5] = {0};
    int n1 = 63;
    int n2 = 30;
    int bit_pos[30] = {0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 4, 0, 8, 0, 0, 0, 16, 0, 32, 0, 0, 0, 64, 0, 0, 0, 0, 0, 128};
    int rem_num[8] = {1, 7, 11, 13, 17, 19, 23, 29};
    int pbits[65536];
    int addr[5] = {0};
    int bits[5] = {0};
    int rem[5] = {0};
    int q[5] = {0};
    int j[5] = {0};
    int b[8] = {0};
    int ofs[8] = {0};
    int k[5] = {0};

    if (n <= 65535)
    {
        if (pbits[n / n2] & bit_pos[n % n2])
        {
            f[0] = n;
            return 1;
        }
    }

    for (p[0] = 2; p[0] && p[0] * p[0] <= n; )
    {
        addr[0] = p[0] / n2;
        bits[0] = bit_pos[p[0] % n2] << 1;
        for (rem[0] = 0; (1 << rem[0]) < bits[0]; rem[0] = rem[0] + 1)
        {
        }
        while (pbits[addr[0]] < bits[0] || !bits[0])
        {
            addr[0] = addr[0] + 1;
            if (addr[0] >= 65536)
            {
                p[0] = 0;
                break;
            }
            bits[0] = 1;
            rem[0] = 0;
        }
        if (addr[0] >= 65536)
        {
            p[0] = 0;
            break;
        }
        while (!(pbits[addr[0]] & bits[0]))
        {
            rem[0] = rem[0] + 1;
            bits[0] = bits[0] << 1;
        }
        p[0] = addr[0] * n2 + rem_num[rem[0]];

        while (n % p[0] == 0)
        {
            n = n / p[0];
            f[i[0]] = p[0];
            i[0] = i[0] + 1;
        }
    }

    if (n > 1)
    {
        f[i[0]] = n;
        i[0] = i[0] + 1;
    }

    return i[0];
    return;
}
