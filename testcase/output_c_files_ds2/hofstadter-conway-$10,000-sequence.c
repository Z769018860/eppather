int doSqnc(int m) {
    int a_list[1048577];
    int max_df[5];
    int p2_max[5];
    int v[5];
    int n[5];
    int k1[5];
    int lg2[5];
    int amax_int[5];
    int i[5];
    
    max_df[0] = 0;
    p2_max[0] = 2;
    k1[0] = 2;
    lg2[0] = 1;
    amax_int[0] = 0;
    a_list[0] = -50000;
    a_list[1] = 1;
    a_list[2] = 1;
    v[0] = a_list[2];
    
    for (n[0] = 3; n[0] <= m; n[0] = n[0] + 1) {
        v[0] = a_list[n[0]] = a_list[v[0]] + a_list[n[0] - v[0]];
        if (amax_int[0] < v[0] * 1000 / n[0]) {
            amax_int[0] = v[0] * 1000 / n[0];
        }
        if (0 == (k1[0] & n[0])) {
            amax_int[0] = 0;
            lg2[0] = lg2[0] + 1;
        }
        k1[0] = n[0];
    }
    return 1;
}
