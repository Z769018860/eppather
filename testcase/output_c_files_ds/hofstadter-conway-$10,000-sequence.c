int a_list[1048577];

int doSqnc(int m)
{
    int max_df = 0;
    int p2_max = 2;
    int v;
    int n;
    int k1 = 2;
    int lg2 = 1;
    int amax_num = 0;
    int amax_den = 1;
    a_list[0] = -50000;
    a_list[1] = 1;
    a_list[2] = 1;
    v = a_list[2];

    for (n = 3; n <= m; n = n + 1) {
        v = a_list[v] + a_list[n - v];
        a_list[n] = v;
        if (amax_num * n < v * amax_den) {
            amax_num = v;
            amax_den = n;
        }
        if ((k1 & n) == 0) {
            amax_num = 0;
            amax_den = 1;
            lg2 = lg2 + 1;
        }
        k1 = n;
    }
    return 1;
}
