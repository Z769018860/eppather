void new_tri(unsigned long in[3], unsigned long* total, unsigned long* prim, unsigned long max_peri)
{
    int i;
    unsigned long t[3];
    unsigned long p;
    unsigned long U[3][9] = {{1, -2, 2, 2, -1, 2, 2, -2, 3}, {1, 2, 2, 2, 1, 2, 2, 2, 3}, {-1, 2, 2, -2, 1, 2, -2, 2, 3}};
    
    p = in[0] + in[1] + in[2];
    
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
        new_tri(t, total, prim, max_peri);
    }
    
    return;
}
