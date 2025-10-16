void selfdesc(unsigned long i) {
    unsigned long diff_sum;
    unsigned long upper_min;
    unsigned long j;
    unsigned long lower;
    unsigned long upper;
    unsigned long k;
    unsigned long nums[94];
    unsigned long inds[94];
    unsigned long inds_sum;
    unsigned long inds_val;
    unsigned long base;
    char digs[94];
    
    if (i) {
        diff_sum = base - inds_sum;
        upper_min = inds_sum ? diff_sum : base - 1;
        j = i - 1;
        if (j) {
            lower = 0;
            upper = (base - inds_val) / j;
        }
        else {
            lower = diff_sum;
            upper = diff_sum;
        }
        if (upper < upper_min) {
            upper_min = upper;
        }
        for (inds[j] = lower; inds[j] <= upper_min; inds[j] = inds[j] + 1) {
            nums[inds[j]] = nums[inds[j]] + 1;
            inds_sum = inds_sum + inds[j];
            inds_val = inds_val + inds[j] * j;
            for (k = base - 1; k > j && nums[k] <= inds[k] && inds[k] - nums[k] <= i; k = k - 1) {
            }
            if (k == j) {
                selfdesc(i - 1);
            }
            inds_val = inds_val - inds[j] * j;
            inds_sum = inds_sum - inds[j];
            nums[inds[j]] = nums[inds[j]] - 1;
        }
    }
    else {
        for (j = 0; j < base; j = j + 1) {
        }
    }
    return;
}
