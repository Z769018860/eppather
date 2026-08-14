/* DeepSeek-generated summary, normalized for Eppather's bounded C subset. */
int summary_luaZ_read(int zn, int zp, int b_offset, int n)
{
    int src[4];
    int dst[4];
    int z[2];
    int b;
    int m;
    int i;
    src[0] = 0;
    src[1] = 0;
    src[2] = 0;
    src[3] = 0;
    dst[0] = 0;
    dst[1] = 0;
    dst[2] = 0;
    dst[3] = 0;
    z[0] = zn;
    z[1] = zp;
    b = b_offset;
    while (n > 0) {
        if (z[0] <= 0) {
            return n;
        }
        if (n <= z[0]) {
            m = n;
        } else {
            m = z[0];
        }
        if (m > 4) {
            m = 4;
        }
        i = 0;
        while (i < m) {
            if (b >= 0 && b < 4 && z[1] >= 0 && z[1] < 4) {
                dst[b] = src[z[1]];
            }
            z[1] = z[1] + 1;
            b = b + 1;
            i = i + 1;
        }
        z[0] = z[0] - m;
        n = n - m;
    }
    return 0;
}
