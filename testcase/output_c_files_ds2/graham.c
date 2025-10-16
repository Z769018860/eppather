int graham_scan(int points_x[5], int points_y[5], int size) {
    int tmp_points_x[6];
    int tmp_points_y[6];
    int m;
    int i;
    int j;
    int k;
    int tmp_x;
    int tmp_y;
    int dx1;
    int dx2;
    int dy1;
    int dy2;
    int ccw_val;
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = i + 1; j < 5; j = j + 1) {
            if (points_y[j] < points_y[i]) {
                tmp_x = points_x[i];
                tmp_y = points_y[i];
                points_x[i] = points_x[j];
                points_y[i] = points_y[j];
                points_x[j] = tmp_x;
                points_y[j] = tmp_y;
            }
        }
    }
    
    for (i = 1; i < 5; i = i + 1) {
        tmp_points_x[i] = points_x[i - 1];
        tmp_points_y[i] = points_y[i - 1];
    }
    tmp_points_x[0] = tmp_points_x[5];
    tmp_points_y[0] = tmp_points_y[5];
    
    m = 1;
    for (i = 2; i <= 5; i = i + 1) {
        while (1) {
            dx1 = tmp_points_x[m] - tmp_points_x[m - 1];
            dy1 = tmp_points_y[m] - tmp_points_y[m - 1];
            dx2 = tmp_points_x[i] - tmp_points_x[m];
            dy2 = tmp_points_y[i] - tmp_points_y[m];
            ccw_val = dx1 * dy2 - dy1 * dx2;
            
            if (ccw_val <= 0) {
                if (m > 1) {
                    m = m - 1;
                    continue;
                } else {
                    if (i == 5) {
                        break;
                    } else {
                        i = i + 1;
                    }
                }
            }
            break;
        }
        
        m = m + 1;
        tmp_x = tmp_points_x[i];
        tmp_y = tmp_points_y[i];
        tmp_points_x[i] = tmp_points_x[m];
        tmp_points_y[i] = tmp_points_y[m];
        tmp_points_x[m] = tmp_x;
        tmp_points_y[m] = tmp_y;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        points_x[i] = tmp_points_x[i + 1];
        points_y[i] = tmp_points_y[i + 1];
    }
    
    return m;
}
