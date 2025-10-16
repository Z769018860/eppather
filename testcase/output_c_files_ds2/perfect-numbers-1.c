int perfect(int n) {
    int max[5];
    int tot[5];
    int i[5];
    int q[5];
    max[0] = 0;
    tot[0] = 1;
    
    for (i[0] = 1; i[0] <= n[0]; i[0] = i[0] + 1) {
        if (i[0] * i[0] > n[0]) {
            break;
        }
    }
    max[0] = i[0];
    
    for (i[0] = 2; i[0] < max[0]; i[0] = i[0] + 1) {
        if ((n[0] % i[0]) == 0) {
            tot[0] = tot[0] + i[0];
            q[0] = n[0] / i[0];
            if (q[0] > i[0]) {
                tot[0] = tot[0] + q[0];
            }
        }
    }
    
    if (tot[0] == n[0]) {
        return 1;
    } else {
        return 0;
    }
    return;
}
