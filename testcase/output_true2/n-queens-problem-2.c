void solve(int d, int c, int l, int r, int qs[5], int* count, int full)
{
    int b;
    int a;
    int s[5];
    if (d == 0) {
        *count = *count + 1;
        return;
    }

    l = l << 1;
    r = r >> 1;
    a = (c | l | r) & full;
    if (a != full) {
        d = d - 1;
        s[0] = 0;
        for (b = 1; b <= full; b = b << 1) {
            if (!(b & a)) {
                qs[d] = qs[d] + 1;
                solve(d, b | c, b | l, b | r, qs, count, full);
            }
        }
    }
    return;
}
