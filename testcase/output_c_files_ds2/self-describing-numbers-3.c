void selfdesc(int base, int digs_n, int ref_val, int nums[5], int inds[5], int inds_sum, int inds_val, int i) {
    int diff_sum;
    int upper_min;
    int j;
    int lower;
    int upper;
    int k;
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
                selfdesc(base, digs_n, ref_val, nums, inds, inds_sum, inds_val, i - 1);
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
