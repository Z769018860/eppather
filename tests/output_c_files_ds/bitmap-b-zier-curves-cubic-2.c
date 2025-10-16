void cubic_bezier(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int r, int g, int b) {
    int pts[21][2];
    int i;
    int N_SEG = 20;
    
    for (i = 0; i <= N_SEG; i = i + 1) {
        int t_num = i;
        int t_den = N_SEG;
        
        int a_num = (t_den - t_num) * (t_den - t_num) * (t_den - t_num);
        int a_den = t_den * t_den * t_den;
        
        int b_num = 3 * t_num * (t_den - t_num) * (t_den - t_num);
        int b_den = t_den * t_den * t_den;
        
        int c_num = 3 * t_num * t_num * (t_den - t_num);
        int c_den = t_den * t_den * t_den;
        
        int d_num = t_num * t_num * t_num;
        int d_den = t_den * t_den * t_den;
        
        int x = (a_num * x1) / a_den + (b_num * x2) / b_den + (c_num * x3) / c_den + (d_num * x4) / d_den;
        int y = (a_num * y1) / a_den + (b_num * y2) / b_den + (c_num * y3) / c_den + (d_num * y4) / d_den;
        
        pts[i][0] = x;
        pts[i][1] = y;
    }
    
    for (i = 0; i < N_SEG; i = i + 1) {
        int j = i + 1;
    }
    
    return;
}
