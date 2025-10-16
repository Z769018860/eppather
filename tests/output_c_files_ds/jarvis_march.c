int jarvis_march(int points[30][2], int hull_points[30][2], int num_points) {
    int ret_x = points[0][0];
    int ret_y = points[0][1];
    for (int i = 0; i < num_points; i = i + 1) {
        if (points[i][0] < ret_x) {
            ret_x = points[i][0];
            ret_y = points[i][1];
        } else {
            if (points[i][0] == ret_x) {
                if (points[i][1] < ret_y) {
                    ret_x = points[i][0];
                    ret_y = points[i][1];
                }
            }
        }
    }
    int hull_point_x = ret_x;
    int hull_point_y = ret_y;
    int end_point_x;
    int end_point_y;
    int i = 0;
    for (;;) {
        hull_points[i][0] = hull_point_x;
        hull_points[i][1] = hull_point_y;
        end_point_x = points[0][0];
        end_point_y = points[0][1];
        for (int j = 1; j < num_points; j = j + 1) {
            int equal_flag = 0;
            if (end_point_x == hull_point_x && end_point_y == hull_point_y) {
                equal_flag = 1;
            }
            int qx = end_point_x;
            int qy = end_point_y;
            int rx = points[j][0];
            int ry = points[j][1];
            int px = hull_points[i][0];
            int py = hull_points[i][1];
            int winding = (qx - px) * (ry - py) - (qy - py) * (rx - px);
            if (equal_flag == 1 || winding > 0) {
                end_point_x = points[j][0];
                end_point_y = points[j][1];
            }
        }
        i = i + 1;
        hull_point_x = end_point_x;
        hull_point_y = end_point_y;
        if (end_point_x == hull_points[0][0] && end_point_y == hull_points[0][1]) {
            break;
        }
    }
    return i;
}
