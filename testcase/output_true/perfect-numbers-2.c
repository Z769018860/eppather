int func(int n1, int n2, int fac[5], int sum[5], int j[5]) {
    for (n2 = 2; n2 < 5; n2 = n2 + 1) {
        j[0] = n1 - 1;
        for (sum[0] = 0; j[0] && sum[0] <= n2; ) {
            j[0] = j[0] - 1;
            sum[0] = sum[0] + fac[j[0]];
        }
        if (sum[0] == n2) {
        }
    }
    return;
}
