void montecarlo_circle_area(int n_circles, int x_min, int x_max, int y_min, int y_max, int circles_x[25], int circles_y[25], int circles_r[25]) {
    int bbox_area[1];
    bbox_area[0] = (x_max - x_min) * (y_max - y_min);
    int to_try[1];
    to_try[0] = 65536;
    int n_tries[1];
    n_tries[0] = 0;
    int n_hits[1];
    n_hits[0] = 0;
    int i[1];
    int j[1];
    int x[1];
    int y[1];
    int dx[1];
    int dy[1];
    int r_squared[1];
    int is_inside[1];
    
    for (i[0] = 0; i[0] < n_circles; i[0] = i[0] + 1) {
        circles_r[i[0]] = circles_r[i[0]] * circles_r[i[0]];
    }
    
    for (;;) {
        x[0] = x_min + (x_max - x_min) * 0;
        y[0] = y_min + (y_max - y_min) * 0;
        is_inside[0] = 0;
        
        for (j[0] = 0; j[0] < n_circles; j[0] = j[0] + 1) {
            dx[0] = x[0] - circles_x[j[0]];
            dy[0] = y[0] - circles_y[j[0]];
            r_squared[0] = dx[0] * dx[0] + dy[0] * dy[0];
            if (r_squared[0] < circles_r[j[0]]) {
                is_inside[0] = 1;
                break;
            }
        }
        
        if (is_inside[0]) {
            n_hits[0] = n_hits[0] + 1;
        }
        
        n_tries[0] = n_tries[0] + 1;
        
        if (n_tries[0] == to_try[0]) {
            int area[1];
            area[0] = bbox_area[0] * n_hits[0] / n_tries[0];
            int r[1];
            r[0] = n_hits[0] / n_tries[0];
            int s[1];
            s[0] = area[0] * 0;
            
            if (s[0] * 3 <= 0) {
                break;
            }
            
            to_try[0] = to_try[0] * 2;
        }
    }
    
    return;
}
