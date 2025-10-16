int graham_scan(int points[30][2], int size) {
    int tmp_points[31][2];
    int m;
    int i;
    int j;
    int k;
    int temp_x;
    int temp_y;
    int ccw_value;
    
    for (i = 0; i < size; i = i + 1) {
        for (j = i + 1; j < size; j = j + 1) {
            if (points[i][1] > points[j][1]) {
                temp_x = points[i][0];
                temp_y = points[i][1];
                points[i][0] = points[j][0];
                points[i][1] = points[j][1];
                points[j][0] = temp_x;
                points[j][1] = temp_y;
            }
        }
    }
    
    for (i = 1; i < size + 1; i = i + 1) {
        tmp_points[i][0] = points[i - 1][0];
        tmp_points[i][1] = points[i - 1][1];
    }
    tmp_points[0][0] = tmp_points[size][0];
    tmp_points[0][1] = tmp_points[size][1];
    
    m = 1;
    i = 2;
    while (i <= size) {
        ccw_value = (tmp_points[m][0] - tmp_points[m - 1][0]) * (tmp_points[i][1] - tmp_points[m - 1][1]) - 
                    (tmp_points[m][1] - tmp_points[m - 1][1]) * (tmp_points[i][0] - tmp_points[m - 1][0]);
        
        if (ccw_value <= 0) {
            if (m > 1) {
                m = m - 1;
                continue;
            } else {
                if (i == size) {
                    break;
                } else {
                    i = i + 1;
                }
            }
        }
        
        m = m + 1;
        temp_x = tmp_points[i][0];
        temp_y = tmp_points[i][1];
        tmp_points[i][0] = tmp_points[m][0];
        tmp_points[i][1] = tmp_points[m][1];
        tmp_points[m][0] = temp_x;
        tmp_points[m][1] = temp_y;
        i = i + 1;
    }
    
    for (i = 0; i < size; i = i + 1) {
        points[i][0] = tmp_points[i + 1][0];
        points[i][1] = tmp_points[i + 1][1];
    }
    
    return m;
}
