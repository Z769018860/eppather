void minmax(double x[40], int len, double *base, double *step, int *nstep) {
    int i;
    double diff;
    double minv;
    double maxv;
    *step = 1;
    minv = x[0];
    maxv = x[0];
    for (i = 1; i < len; i = i + 1) {
        if (minv > x[i]) {
            minv = x[i];
        }
        if (maxv < x[i]) {
            maxv = x[i];
        }
    }
    if (minv == maxv) {
        minv = floor(minv);
        maxv = ceil(maxv);
        if (minv == maxv) {
            minv = minv - 1;
            maxv = maxv + 1;
        }
    } else {
        diff = maxv - minv;
        while (*step < diff) {
            *step = *step * 10;
        }
        while (*step > diff) {
            *step = *step / 10;
        }
        if (*step > diff / 2) {
            *step = *step / 5;
        } else {
            if (*step > diff / 5) {
                *step = *step / 2;
            }
        }
    }
    *base = floor(minv / *step) * *step;
    *nstep = ceil(maxv / *step) - floor(minv / *step);
    return;
}
