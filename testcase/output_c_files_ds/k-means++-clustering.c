int nearest(int pt_x, int pt_y, int pt_group, int cent_x[], int cent_y[], int cent_group[], int n_cluster, int d2[]) {
    int i;
    int min_i;
    int min_d;
    int d;
    int dx;
    int dy;
    
    min_d = 2147483647;
    min_i = pt_group;
    for (i = 0; i < n_cluster; i = i + 1) {
        dx = pt_x - cent_x[i];
        dy = pt_y - cent_y[i];
        d = dx * dx + dy * dy;
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

void kpp(int pts_x[], int pts_y[], int pts_group[], int len, int cent_x[], int cent_y[], int n_cent) {
    int i;
    int j;
    int n_cluster;
    int sum;
    int d[100000];
    int p;
    int c;
    
    cent_x[0] = pts_x[0];
    cent_y[0] = pts_y[0];
    for (n_cluster = 1; n_cluster < n_cent; n_cluster = n_cluster + 1) {
        sum = 0;
        for (j = 0; j < len; j = j + 1) {
            nearest(pts_x[j], pts_y[j], pts_group[j], cent_x, cent_y, pts_group, n_cluster, d + j);
            sum = sum + d[j];
        }
        sum = sum % 1000;
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
        pts_group[j] = nearest(pts_x[j], pts_y[j], pts_group[j], cent_x, cent_y, pts_group, n_cluster, 0);
    }
    return;
}

void lloyd(int pts_x[], int pts_y[], int pts_group[], int len, int n_cluster, int cent_x[], int cent_y[]) {
    int i;
    int j;
    int min_i;
    int changed;
    int p;
    int c;
    
    kpp(pts_x, pts_y, pts_group, len, cent_x, cent_y, n_cluster);
    do {
        for (i = 0; i < n_cluster; i = i + 1) {
            pts_group[i] = 0;
            cent_x[i] = 0;
            cent_y[i] = 0;
        }
        for (j = 0; j < len; j = j + 1) {
            c = pts_group[j];
            pts_group[c] = pts_group[c] + 1;
            cent_x[c] = cent_x[c] + pts_x[j];
            cent_y[c] = cent_y[c] + pts_y[j];
        }
        for (i = 0; i < n_cluster; i = i + 1) {
            cent_x[i] = cent_x[i] / pts_group[i];
            cent_y[i] = cent_y[i] / pts_group[i];
        }
        changed = 0;
        for (j = 0; j < len; j = j + 1) {
            min_i = nearest(pts_x[j], pts_y[j], pts_group[j], cent_x, cent_y, pts_group, n_cluster, 0);
            if (min_i != pts_group[j]) {
                changed = changed + 1;
                pts_group[j] = min_i;
            }
        }
    } while (changed > (len / 1024));
    for (i = 0; i < n_cluster; i = i + 1) {
        pts_group[i] = i;
    }
    return;
}
