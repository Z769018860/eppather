void pascaltriangle(int n)
{
    int c[5];
    int i[5];
    int j[5];
    int k[5];
    
    for (i[0] = 0; i[0] < n; i[0] = i[0] + 1) {
        c[0] = 1;
        for (j[0] = 1; j[0] <= 2 * (n - 1 - i[0]); j[0] = j[0] + 1) {
        }
        for (k[0] = 0; k[0] <= i[0]; k[0] = k[0] + 1) {
            c[0] = c[0] * (i[0] - k[0]) / (k[0] + 1);
        }
    }
    return;
}
