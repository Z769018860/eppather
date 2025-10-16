int area(int n_circ, int ymin, int ymax, int step) {
    int c[5][8];
    int n = n_circ;
    int i;
    int row;
    int total = 0;
    int right;
    
    for (i = 0; i < n; i = i + 1) {
        c[i][0] = 0;
        c[i][1] = 0;
        c[i][2] = 0;
        c[i][3] = 0;
        c[i][4] = 0;
        c[i][5] = 0;
        c[i][6] = 0;
        c[i][7] = 0;
    }
    
    while (n > 0) {
        n = n - 1;
        for (i = 0; i < n; i = i + 1) {
            if (c[i][5] < c[i + 1][5]) {
                int tmp[8];
                tmp[0] = c[i][0];
                tmp[1] = c[i][1];
                tmp[2] = c[i][2];
                tmp[3] = c[i][3];
                tmp[4] = c[i][4];
                tmp[5] = c[i][5];
                tmp[6] = c[i][6];
                tmp[7] = c[i][7];
                c[i][0] = c[i + 1][0];
                c[i][1] = c[i + 1][1];
                c[i][2] = c[i + 1][2];
                c[i][3] = c[i + 1][3];
                c[i][4] = c[i + 1][4];
                c[i][5] = c[i + 1][5];
                c[i][6] = c[i + 1][6];
                c[i][7] = c[i + 1][7];
                c[i + 1][0] = tmp[0];
                c[i + 1][1] = tmp[1];
                c[i + 1][2] = tmp[2];
                c[i + 1][3] = tmp[3];
                c[i + 1][4] = tmp[4];
                c[i + 1][5] = tmp[5];
                c[i + 1][6] = tmp[6];
                c[i + 1][7] = tmp[7];
            }
        }
    }
    
    row = 1 + (ymax - ymin) / step;
    while (row > 0) {
        row = row - 1;
        int y = ymin + step * row;
        for (n = 0; n < n_circ; n = n + 1) {
            if (y >= c[n][5]) {
                break;
            } else if (y > c[n][4]) {
                int dx = 0;
                c[n][6] = c[n][0] - dx;
                c[n][7] = c[n][0] + dx;
                
                for (i = n; i > 0; i = i - 1) {
                    if (c[i - 1][6] > c[i][6]) {
                        int tmp[8];
                        tmp[0] = c[i][0];
                        tmp[1] = c[i][1];
                        tmp[2] = c[i][2];
                        tmp[3] = c[i][3];
                        tmp[4] = c[i][4];
                        tmp[5] = c[i][5];
                        tmp[6] = c[i][6];
                        tmp[7] = c[i][7];
                        c[i][0] = c[i - 1][0];
                        c[i][1] = c[i - 1][1];
                        c[i][2] = c[i - 1][2];
                        c[i][3] = c[i - 1][3];
                        c[i][4] = c[i - 1][4];
                        c[i][5] = c[i - 1][5];
                        c[i][6] = c[i - 1][6];
                        c[i][7] = c[i - 1][7];
                        c[i - 1][0] = tmp[0];
                        c[i - 1][1] = tmp[1];
                        c[i - 1][2] = tmp[2];
                        c[i - 1][3] = tmp[3];
                        c[i - 1][4] = tmp[4];
                        c[i - 1][5] = tmp[5];
                        c[i - 1][6] = tmp[6];
                        c[i - 1][7] = tmp[7];
                    } else {
                        break;
                    }
                }
            } else {
                for (i = n; i < n_circ - 1; i = i + 1) {
                    c[i][0] = c[i + 1][0];
                    c[i][1] = c[i + 1][1];
                    c[i][2] = c[i + 1][2];
                    c[i][3] = c[i + 1][3];
                    c[i][4] = c[i + 1][4];
                    c[i][5] = c[i + 1][5];
                    c[i][6] = c[i + 1][6];
                    c[i][7] = c[i + 1][7];
                }
                n_circ = n_circ - 1;
                n = n - 1;
            }
        }
        
        if (n == 0) {
            continue;
        }
        
        right = c[0][7];
        total = total + c[0][7] - c[0][6];
        
        for (i = 1; i < n; i = i + 1) {
            if (c[i][7] <= right) {
                continue;
            }
            total = total + c[i][7] - (c[i][6] > right ? c[i][6] : right);
            right = c[i][7];
        }
    }
    
    return total * step;
}
