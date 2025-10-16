int nearest(int pt_x[5], int pt_y[5], int pt_group[5], int cent_x[5], int cent_y[5], int n_cluster, int d2[5]) {
    int min_i;
    int min_d;
    int d;
    int i;
    int j;
    min_d = 2147483647;
    min_i = pt_group[0];
    for (i = 0; i < n_cluster; i = i + 1) {
        d = (cent_x[i] - pt_x[0]) * (cent_x[i] - pt_x[0]) + (cent_y[i] - pt_y[0]) * (cent_y[i] - pt_y[0]);
        if (min_d > d) {
            min_d = d;
            min_i = i;
        }
    }
    if (d2) {
        d2[0] = min_d;
    }
    return min_i;
}

void kpp(int pts_x[5], int pts_y[5], int pts_group[5], int len, int cent_x[5], int cent_y[5], int n_cent) {
    int d[5];
    int sum;
    int j;
    int p_x[5];
    int p_y[5];
    int p_group[5];
    int n_cluster;
    cent_x[0] = pts_x[0];
    cent_y[0] = pts_y[0];
    for (n_cluster = 1; n_cluster < n_cent; n_cluster = n_cluster + 1) {
        sum = 0;
        for (j = 0; j < len; j = j + 1) {
            p_x[0] = pts_x[j];
            p_y[0] = pts_y[j];
            p_group[0] = pts_group[j];
            d[j] = nearest(p_x, p_y, p_group, cent_x, cent_y, n_cluster, d + j);
            sum = sum + d[j];
        }
        sum = sum % 100;
        for (j = 0; j < len; j = j + 1) {
            sum = sum - d[j];
            if (sum > 0) {
                continue;
            }
            cent_x[n_cluster] = pts_x[j];
            cent_y[n_cluster] = pts_y[j];
            break;
        }
    }
    for (j = 0; j < len; j = j + 1) {
        p_x[0] = pts_x[j];
        p_y[0] = pts_y[j];
        p_group[0] = pts_group[j];
        pts_group[j] = nearest(p_x, p_y, p_group, cent_x, cent_y, n_cluster, 0);
    }
    return;
}

void lloyd(int pts_x[5], int pts_y[5], int pts_group[5], int len, int n_cluster, int cent_x[5], int cent_y[5]) {
    int changed;
    int min_i;
    int i;
    int j;
    int p_x[5];
    int p_y[5];
    int p_group[5];
    int c_x[5];
    int c_y[5];
    int c_group[5];
    kpp(pts_x, pts_y, pts_group, len, cent_x, cent_y, n_cluster);
    do {
        for (i = 0; i < n_cluster; i = i + 1) {
            c_group[i] = 0;
            c_x[i] = 0;
            c_y[i] = 0;
        }
        for (j = 0; j < len; j = j + 1) {
            p_x[0] = pts_x[j];
            p_y[0] = pts_y[j];
            p_group[0] = pts_group[j];
            c_x[p_group[0]] = c_x[p_group[0]] + p_x[0];
            c_y[p_group[0]] = c_y[p_group[0]] + p_y[0];
            c_group[p_group[0]] = c_group[p_group[0]] + 1;
        }
        for (i = 0; i < n_cluster; i = i + 1) {
            c_x[i] = c_x[i] / c_group[i];
            c_y[i] = c_y[i] / c_group[i];
        }
        changed = 0;
        for (j = 0; j < len; j = j + 1) {
            p_x[0] = pts_x[j];
            p_y[0] = pts_y[j];
            p_group[0] = pts_group[j];
            min_i = nearest(p_x, p_y, p_group, cent_x, cent_y, n_cluster, 0);
            if (min_i != p_group[0]) {
                changed = changed + 1;
                pts_group[j] = min_i;
            }
        }
    } while (changed > (len / 1024));
    for (i = 0; i < n_cluster; i = i + 1) {
        cent_x[i] = c_x[i];
        cent_y[i] = c_y[i];
    }
    return;
}
