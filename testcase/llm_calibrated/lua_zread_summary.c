/* Source-guided bounded projection of luaZ_read for the no-refill domain.
 * z[0]=ZIO.n, z[1]=offset of ZIO.p into src; b is offset into dst.
 * Inputs must satisfy 0<=n<=3, 0<=z[0]<=3, 0<=z[1]<=3,
 * 0<=b<=3, and the copied interval must fit the arrays.
 * A zero z[0] models luaZ_fill returning EOZ. memcpy is modeled as one
 * source read and one destination write per copied byte.
 */
int summary_luaZ_read(int *z, int *src, int *dst, int b, int n)
{
    int m;
    int p;
    int i;
    while (n > 0) {
        if (z[0] == 0) {
            return n;
        }
        if (n <= z[0]) {
            m = n;
        } else {
            m = z[0];
        }
        p = z[1];
        i = 0;
        while (i < m) {
            dst[b + i] = src[p + i];
            i = i + 1;
        }
        z[0] = z[0] - m;
        z[1] = z[1] + m;
        b = b + m;
        n = n - m;
    }
    return 0;
}
