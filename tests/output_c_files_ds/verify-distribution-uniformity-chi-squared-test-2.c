int chiIsUniform(int* dset, int dslen, int significance) {
    int expected;
    int sum;
    int k;
    int dof;
    int dist;
    int x;
    int result;
    
    expected = 0;
    for (k = 0; k < dslen; k = k + 1) {
        expected = expected + dset[k];
    }
    expected = expected / dslen;
    
    sum = 0;
    for (k = 0; k < dslen; k = k + 1) {
        x = dset[k] - expected;
        sum = sum + x * x;
    }
    dist = sum / expected;
    
    dof = dslen - 1;
    result = GammaIncomplete_Q(dof / 2, dist / 2) > significance;
    return result;
}
