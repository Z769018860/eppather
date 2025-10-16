void quad_bezier(int img, int x1, int y1, int x2, int y2, int x3, int y3, int r, int g, int b) {
    int n_seg = 20;
    int pts[21][2];
    int i;
    int j;
    int t_num;
    int t_den;
    int a_num;
    int a_den;
    int b_num;
    int b_den;
    int c_num;
    int c_den;
    int x_num;
    int x_den;
    int y_num;
    int y_den;

    for (i = 0; i <= n_seg; i = i + 1) {
        t_num = i;
        t_den = n_seg;
        a_num = (n_seg - i) * (n_seg - i);
        a_den = n_seg * n_seg;
        b_num = 2 * i * (n_seg - i);
        b_den = n_seg * n_seg;
        c_num = i * i;
        c_den = n_seg * n_seg;
        x_num = a_num * x1 * b_den * c_den + b_num * x2 * a_den * c_den + c_num * x3 * a_den * b_den;
        x_den = a_den * b_den * c_den;
        y_num = a_num * y1 * b_den * c_den + b_num * y2 * a_den * c_den + c_num * y3 * a_den * b_den;
        y_den = a_den * b_den * c_den;
        pts[i][0] = x_num / x_den;
        pts[i][1] = y_num / y_den;
    }

    for (i = 0; i < n_seg; i = i + 1) {
        j = i + 1;
    }

    return;
}
