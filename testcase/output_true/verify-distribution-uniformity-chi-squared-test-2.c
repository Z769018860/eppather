int chiIsUniform(int dset_len, int significance_len) {
    int dset[5];
    int dslen[5];
    int significance[5];
    int dof[5];
    int dist[5];
    int expected[5];
    int sum[5];
    int k;
    int x[5];
    int temp[5];
    
    expected[0] = 0;
    sum[0] = 0;
    for (k = 0; k < 5; k = k + 1) {
        expected[0] = expected[0] + dset[k];
    }
    expected[0] = expected[0] / k;
    
    for (k = 0; k < 5; k = k + 1) {
        x[0] = dset[k] - expected[0];
        temp[0] = x[0] * x[0];
        sum[0] = sum[0] + temp[0];
    }
    dist[0] = sum[0] / expected[0];
    
    dof[0] = dset_len - 1;
    temp[0] = dof[0] * 5;
    temp[0] = temp[0] / 10;
    x[0] = dist[0] * 5;
    x[0] = x[0] / 10;
    temp[0] = GammaIncomplete_Q(temp[0], x[0]);
    
    if (temp[0] > significance[0]) {
        return 1;
    } else {
        return 0;
    }
    return;
}
