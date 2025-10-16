int nqueens(int n)
{
    int q0;
    int q1;
    int cols[31];
    int diagl[31];
    int diagr[31];
    int posibs[31];
    int num;
    num = 0;
    for (q0 = 0; q0 < n - 2; q0 = q0 + 1) {
        for (q1 = q0 + 2; q1 < n; q1 = q1 + 1) {
            int bit0;
            int bit1;
            int d;
            bit0 = 1 << q0;
            bit1 = 1 << q1;
            d = 0;
            cols[0] = bit0 | bit1 | (-1 << n);
            diagl[0] = (bit0 << 1 | bit1) << 1;
            diagr[0] = (bit0 >> 1 | bit1) >> 1;
            int posib;
            posib = ~(cols[0] | diagl[0] | diagr[0]);
            while (d >= 0) {
                while (posib) {
                    int bit;
                    int ncols;
                    int ndiagl;
                    int ndiagr;
                    int nposib;
                    bit = posib & -posib;
                    ncols = cols[d] | bit;
                    ndiagl = (diagl[d] | bit) << 1;
                    ndiagr = (diagr[d] | bit) >> 1;
                    nposib = ~(ncols | ndiagl | ndiagr);
                    posib = posib ^ bit;
                    num = num + (ncols == -1);
                    if (nposib) {
                        if (posib) {
                            posibs[d] = posib;
                            d = d + 1;
                        }
                        cols[d] = ncols;
                        diagl[d] = ndiagl;
                        diagr[d] = ndiagr;
                        posib = nposib;
                    }
                }
                d = d - 1;
                if (d >= 0) {
                    posib = posibs[d];
                }
            }
        }
    }
    return num * 2;
}
