int happy(int n, int cache_size)
{
    int sum[5];
    int x[5];
    int nn[5];
    int buf[256];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        sum[i] = 0;
        x[i] = 0;
        nn[i] = 0;
    }
    for (i = 0; i < 256; i = i + 1) {
        buf[i] = 0;
    }
    buf[1] = 1;

    if (n < cache_size) {
        if (buf[n] != 0) {
            return 2 - buf[n];
        }
        buf[n] = 2;
    }

    nn[0] = n;
    for (; nn[0] != 0; nn[0] = nn[0] / 10) {
        x[0] = nn[0] % 10;
        sum[0] = sum[0] + x[0] * x[0];
    }

    x[0] = happy(sum[0], cache_size);
    if (n < cache_size) {
        buf[n] = 2 - x[0];
    }
    return x[0];
}
