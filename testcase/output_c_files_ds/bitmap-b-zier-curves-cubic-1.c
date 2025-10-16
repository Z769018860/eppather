void cubic_bezier(int img[1], int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int r, int g, int b) {
    int i;
    int j;
    int points[100][2];
    int n;
    int x;
    int y;
    int t;
    int t1;
    int t2;
    int t3;
    int t4;
    n = 0;
    for (i = 0; i <= 100; i = i + 1) {
        t = i;
        t = t / 100;
        t1 = 1 - t;
        t2 = t1 * t1 * t1;
        t3 = 3 * t * t1 * t1;
        t4 = 3 * t * t * t1;
        t = t * t * t;
        x = t2 * x1 + t3 * x2 + t4 * x3 + t * x4;
        y = t2 * y1 + t3 * y2 + t4 * y3 + t * y4;
        if (n < 100) {
            points[n][0] = x;
            points[n][1] = y;
            n = n + 1;
        }
    }
    for (i = 0; i < n - 1; i = i + 1) {
        for (j = i + 1; j < n; j = j + 1) {
            if (points[i][0] > points[j][0]) {
                x = points[i][0];
                points[i][0] = points[j][0];
                points[j][0] = x;
                y = points[i][1];
                points[i][1] = points[j][1];
                points[j][1] = y;
            }
        }
    }
    return;
}
