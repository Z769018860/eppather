int rooted_result[501][5][500];
int bcache_val[501];
int ucache_val[501];
int tmp_val1;
int tmp_val2;
int rtmp_val1;
int rtmp_val2;

void choose(int* r, int m, int k)
{
    int i;
    *r = m;
    tmp_val1 = m + 1;
    for (i = 1; i < k; i = i + 1)
    {
        *r = *r * tmp_val1;
        i = i + 1;
        *r = *r / i;
        if (i >= k)
        {
            break;
        }
        tmp_val1 = tmp_val1 + 1;
    }
}

void calc_rooted(int* res, int n, int b, int r)
{
    *res = 0;
    if (n == 1 && b == 0 && r == 0)
    {
        *res = 1;
        return;
    }
    else if (n <= b || n <= r || n == 1 || b == 0 || r == 0)
    {
        return;
    }
    int b1;
    int r1;
    for (b1 = 1; b1 <= b && r * b1 < n; b1 = b1 + 1)
    {
        choose(&rtmp_val1, bcache_val[r], b1);
        rtmp_val2 = 0;
        for (r1 = 0; r1 < r && r1 + r * b1 < n; r1 = r1 + 1)
        {
            rtmp_val2 = rtmp_val2 + rooted_result[n - r * b1][b - b1][r1];
        }
        *res = *res + rtmp_val1 * rtmp_val2;
    }
}

void calc_first_branch(int n)
{
    int b;
    int r;
    bcache_val[n] = 0;
    for (b = 0; b < 4; b = b + 1)
    {
        for (r = 0; r < n; r = r + 1)
        {
            bcache_val[n] = bcache_val[n] + rooted_result[n][b][r];
        }
    }
}

void calc_unrooted(int n)
{
    int b;
    int r;
    for (b = 0; b <= 4; b = b + 1)
    {
        for (r = 0; r < n; r = r + 1)
        {
            calc_rooted(&rooted_result[n][b][r], n, b, r);
        }
    }
    calc_first_branch(n);
    ucache_val[n] = 0;
    for (r = 0; r * 2 < n; r = r + 1)
    {
        for (b = 0; b <= 4; b = b + 1)
        {
            ucache_val[n] = ucache_val[n] + rooted_result[n][b][r];
        }
    }
    if (!(n & 1))
    {
        rtmp_val1 = bcache_val[n / 2] + 1;
        rtmp_val1 = rtmp_val1 * bcache_val[n / 2];
        rtmp_val1 = rtmp_val1 / 2;
        ucache_val[n] = ucache_val[n] + rtmp_val1;
    }
    return;
}
