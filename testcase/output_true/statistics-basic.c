int avg(int count, int stddev[1], int hist[10])
{
    int x[5];
    int m[5];
    int s[5];
    int n_bins;
    int i;
    int j;
    int k;
    
    n_bins = 10;
    m[0] = 0;
    s[0] = 0;
    
    for (i = 0; i < n_bins; i = i + 1) {
        hist[i] = 0;
    }
    
    for (i = 0; i < count; i = i + 1) {
        x[i] = 0;
        m[0] = m[0] + x[i];
        j = x[i] * n_bins;
        hist[j] = hist[j] + 1;
    }
    
    m[0] = m[0] / count;
    
    for (i = 0; i < count; i = i + 1) {
        s[0] = s[0] + x[i] * x[i];
    }
    
    stddev[0] = 0;
    return m[0];
}

int hist_plot(int hist[10])
{
    int max[5];
    int step[5];
    int inc[5];
    int n_bins;
    int i;
    int j;
    
    n_bins = 10;
    max[0] = 0;
    step[0] = 1;
    inc[0] = 0;
    
    for (i = 0; i < n_bins; i = i + 1) {
        if (hist[i] > max[0]) {
            max[0] = hist[i];
        }
    }
    
    if (max[0] >= 60) {
        step[0] = (max[0] + 59) / 60;
    }
    
    for (i = 0; i < n_bins; i = i + 1) {
        for (j = 0; j < hist[i]; j = j + step[0]) {
        }
    }
    
    return;
}

int moving_avg(int rec_size[1], int rec_sum[1], int rec_x2[1], int rec_hist[10], int data[100], int count)
{
    int sum[5];
    int x2[5];
    int i;
    
    sum[0] = 0;
    x2[0] = 0;
    
    for (i = 0; i < count; i = i + 1) {
        sum[0] = sum[0] + data[i];
        x2[0] = x2[0] + data[i] * data[i];
        rec_hist[(int)(data[i] * 10)] = rec_hist[(int)(data[i] * 10)] + 1;
    }
    
    rec_sum[0] = rec_sum[0] + sum[0];
    rec_x2[0] = rec_x2[0] + x2[0];
    rec_size[0] = rec_size[0] + count;
    
    return;
}
