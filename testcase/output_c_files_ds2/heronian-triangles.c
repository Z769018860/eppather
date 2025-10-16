void generateTriangleList(int maxSide, int count[5], int herons[5][5]) {
    int a;
    int b;
    int c;
    int t_a[5];
    int t_b[5];
    int t_c[5];
    int t_perimeter[5];
    double t_area[5];
    int gcd1;
    int gcd2;
    int temp;
    int flag;
    int i;
    int j;
    int k;
    int l;
    int m;
    int n;
    int o;
    int p;
    int q;
    int r;
    int s;
    int u;
    int v;
    int w;
    int x;
    int y;
    int z;

    count[0] = 0;
    for (a = 1; a <= maxSide; a = a + 1) {
        for (b = 1; b <= a; b = b + 1) {
            for (c = 1; c <= b; c = c + 1) {
                if (c + b > a) {
                    gcd1 = a;
                    gcd2 = b;
                    while (gcd2 != 0) {
                        temp = gcd1 % gcd2;
                        gcd1 = gcd2;
                        gcd2 = temp;
                    }
                    gcd2 = c;
                    while (gcd2 != 0) {
                        temp = gcd1 % gcd2;
                        gcd1 = gcd2;
                        gcd2 = temp;
                    }
                    if (gcd1 == 1) {
                        t_a[0] = a;
                        t_b[0] = b;
                        t_c[0] = c;
                        t_perimeter[0] = t_a[0] + t_b[0] + t_c[0];
                        t_area[0] = sqrt(0.5 * t_perimeter[0] * (0.5 * t_perimeter[0] - t_a[0]) * (0.5 * t_perimeter[0] - t_b[0]) * (0.5 * t_perimeter[0] - t_c[0]));
                        if (t_area[0] / (int)t_area[0] == 1) {
                            flag = 0;
                            for (i = 0; i < 5; i = i + 1) {
                                if (herons[i][0] == 0) {
                                    herons[i][0] = t_a[0];
                                    herons[i][1] = t_b[0];
                                    herons[i][2] = t_c[0];
                                    herons[i][3] = t_perimeter[0];
                                    herons[i][4] = (int)t_area[0];
                                    count[0] = count[0] + 1;
                                    flag = 1;
                                    break;
                                }
                            }
                            if (flag == 0) {
                                for (j = 0; j < 5; j = j + 1) {
                                    if ((herons[j][4] < t_area[0]) || (herons[j][4] == t_area[0] && herons[j][3] < t_perimeter[0]) || (herons[j][4] == t_area[0] && herons[j][3] == t_perimeter[0] && herons[j][0] <= t_a[0])) {
                                        for (k = 4; k > j; k = k - 1) {
                                            for (l = 0; l < 5; l = l + 1) {
                                                herons[k][l] = herons[k - 1][l];
                                            }
                                        }
                                        herons[j][0] = t_a[0];
                                        herons[j][1] = t_b[0];
                                        herons[j][2] = t_c[0];
                                        herons[j][3] = t_perimeter[0];
                                        herons[j][4] = (int)t_area[0];
                                        count[0] = count[0] + 1;
                                        flag = 1;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return;
}
