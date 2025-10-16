void cubic_bezier(int img, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int r, int g, int b)
{
    int n_seg = 20;
    int pts[21][2];
    int i;
    for (i = 0; i <= 20; i = i + 1)
    {
        int t_num = i;
        int t_den = n_seg;
        int a_num = (1 - t_num) * (1 - t_num) * (1 - t_num);
        int a_den = t_den * t_den * t_den;
        int b_num = 3 * t_num * (1 - t_num) * (1 - t_num);
        int b_den = t_den * t_den * t_den;
        int c_num = 3 * t_num * t_num * (1 - t_num);
        int c_den = t_den * t_den * t_den;
        int d_num = t_num * t_num * t_num;
        int d_den = t_den * t_den * t_den;
        int x = (a_num * x1 + b_num * x2 + c_num * x3 + d_num * x4) / a_den;
        int y = (a_num * y1 + b_num * y2 + c_num * y3 + d_num * y4) / a_den;
        pts[i][0] = x;
        pts[i][1] = y;
    }
    for (i = 0; i < 20; i = i + 1)
    {
        int j = i + 1;
        int x0 = pts[i][0];
        int y0 = pts[i][1];
        int x1 = pts[j][0];
        int y1 = pts[j][1];
    }
    return;
}
