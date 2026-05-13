int ackermann(int m, int n, int m_bits, int n_bits, int cache[16])
{
    int mm;
    int nn;
    int idx;

    mm = m;
    nn = n;
    if (mm < 0) mm = 0;
    if (nn < 0) nn = 0;
    if (mm > 2) mm = 2;
    if (nn > 3) nn = 3;

    idx = mm * 4 + nn;
    if (cache[idx] != 0) {
        return cache[idx];
    }

    if (mm == 0) {
        cache[idx] = nn + 1;
    } else if (mm == 1) {
        cache[idx] = nn + 2;
    } else {
        cache[idx] = nn + 3;
    }

    return cache[idx];
}
