void new_tri(int in[3], int max_peri, int* total, int* prim, int U[3][9])
{
    int i;
    int t[3];
    int p = in[0] + in[1] + in[2];

    if (p > max_peri)
    {
        return;
    }

    *prim = *prim + 1;
    *total = *total + max_peri / p;

    for (i = 0; i < 3; i = i + 1)
    {
        t[0] = U[i][0] * in[0] + U[i][1] * in[1] + U[i][2] * in[2];
        t[1] = U[i][3] * in[0] + U[i][4] * in[1] + U[i][5] * in[2];
        t[2] = U[i][6] * in[0] + U[i][7] * in[1] + U[i][8] * in[2];
        new_tri(t, max_peri, total, prim, U);
    }
    return;
}
