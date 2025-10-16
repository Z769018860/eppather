int catmull(int m[5][5], int nm[5][5], int f[5][5], int v[5][5], int e[5][5], int a, int b, int c, int d) {
    int i;
    int j;
    int k;
    int n;
    int sum[5][5];
    int avg[5][5];
    int pos[5][5];
    int v_new[5][5];
    int e_pt[5][5];
    int hole_edge;
    int hole_vertex;
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            if (f[i][0] == 0) {
                for (k = 0; k < 5; k = k + 1) {
                    if (k == 0) {
                        avg[i][0] = v[j][0];
                    } else {
                        avg[i][0] = avg[i][0] + v[j][0];
                    }
                }
                avg[i][0] = avg[i][0] / 5;
            }
            if (e[i][0] == 0) {
                e_pt[i][0] = (v[0][0] + v[1][0]) / 2;
                hole_edge = 1;
                if (hole_edge == 0) {
                    for (k = 0; k < 5; k = k + 1) {
                        e_pt[i][0] = e_pt[i][0] + avg[k][0];
                    }
                    e_pt[i][0] = e_pt[i][0] / 4;
                } else {
                    e_pt[i][0] = e_pt[i][0] / 2;
                }
            }
            if (v[i][0] == 0) {
                v_new[i][0] = v[i][0];
                hole_vertex = 1;
                if (hole_vertex != 0) {
                    n = 0;
                    for (k = 0; k < 5; k = k + 1) {
                        if (hole_edge == 0) {
                            continue;
                        }
                        v_new[i][0] = v_new[i][0] + e_pt[k][0];
                        n = n + 1;
                    }
                    v_new[i][0] = v_new[i][0] / (n + 1);
                } else {
                    n = 5;
                    for (k = 0; k < 5; k = k + 1) {
                        sum[i][0] = sum[i][0] + avg[k][0];
                    }
                    for (k = 0; k < 5; k = k + 1) {
                        sum[i][0] = 2 * sum[i][0] + e_pt[k][0];
                    }
                    sum[i][0] = sum[i][0] / n;
                    sum[i][0] = (n - 3) * sum[i][0] + v[i][0];
                    sum[i][0] = sum[i][0] / n;
                    v_new[i][0] = sum[i][0];
                }
            }
            a = v_new[i][0];
            b = e_pt[(j + 1) % 5][0];
            c = avg[i][0];
            d = e_pt[j][0];
            nm[i][0] = a;
            nm[i][1] = b;
            nm[i][2] = c;
            nm[i][3] = d;
        }
    }
    return;
}
