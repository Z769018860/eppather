int left_of(int a_x, int a_y, int b_x, int b_y, int c_x, int c_y) {
    int tmp1_x = b_x - a_x;
    int tmp1_y = b_y - a_y;
    int tmp2_x = c_x - b_x;
    int tmp2_y = c_y - b_y;
    int x = tmp1_x * tmp2_y - tmp1_y * tmp2_x;
    if (x < 0) {
        return -1;
    } else {
        if (x > 0) {
            return 1;
        } else {
            return 0;
        }
    }
}

int line_sect(int x0_x, int x0_y, int x1_x, int x1_y, int y0_x, int y0_y, int y1_x, int y1_y, int res[2]) {
    int dx_x = x1_x - x0_x;
    int dx_y = x1_y - x0_y;
    int dy_x = y1_x - y0_x;
    int dy_y = y1_y - y0_y;
    int d_x = x0_x - y0_x;
    int d_y = x0_y - y0_y;
    int dyx = dy_x * dx_y - dy_y * dx_x;
    if (dyx == 0) {
        return 0;
    }
    int d_cross_dx = d_x * dx_y - d_y * dx_x;
    dyx = d_cross_dx / dyx;
    if (dyx <= 0 || dyx >= 1) {
        return 0;
    }
    res[0] = y0_x + dyx * dy_x;
    res[1] = y0_y + dyx * dy_y;
    return 1;
}

void poly_edge_clip(int sub_v[][2], int sub_len, int x0_x, int x0_y, int x1_x, int x1_y, int left, int res_v[][2], int res_len[1]) {
    int side0 = left_of(x0_x, x0_y, x1_x, x1_y, sub_v[sub_len - 1][0], sub_v[sub_len - 1][1]);
    res_len[0] = 0;
    if (side0 != -left) {
        res_v[res_len[0]][0] = sub_v[sub_len - 1][0];
        res_v[res_len[0]][1] = sub_v[sub_len - 1][1];
        res_len[0] = res_len[0] + 1;
    }
    int v0_x = sub_v[sub_len - 1][0];
    int v0_y = sub_v[sub_len - 1][1];
    int side1;
    int i;
    for (i = 0; i < sub_len; i = i + 1) {
        int v1_x = sub_v[i][0];
        int v1_y = sub_v[i][1];
        side1 = left_of(x0_x, x0_y, x1_x, x1_y, v1_x, v1_y);
        if (side0 + side1 == 0 && side0 != 0) {
            int tmp[2];
            if (line_sect(x0_x, x0_y, x1_x, x1_y, v0_x, v0_y, v1_x, v1_y, tmp)) {
                res_v[res_len[0]][0] = tmp[0];
                res_v[res_len[0]][1] = tmp[1];
                res_len[0] = res_len[0] + 1;
            }
        }
        if (i == sub_len - 1) {
            break;
        }
        if (side1 != -left) {
            res_v[res_len[0]][0] = v1_x;
            res_v[res_len[0]][1] = v1_y;
            res_len[0] = res_len[0] + 1;
        }
        v0_x = v1_x;
        v0_y = v1_y;
        side0 = side1;
    }
    return;
}

void poly_clip(int sub_v[][2], int sub_len, int clip_v[][2], int clip_len, int res_v[][2], int res_len[1]) {
    int p1_v[100][2];
    int p1_len = 0;
    int p2_v[100][2];
    int p2_len = 0;
    int dir = left_of(clip_v[0][0], clip_v[0][1], clip_v[1][0], clip_v[1][1], clip_v[2][0], clip_v[2][1]);
    poly_edge_clip(sub_v, sub_len, clip_v[clip_len - 1][0], clip_v[clip_len - 1][1], clip_v[0][0], clip_v[0][1], dir, p2_v, &p2_len);
    int i;
    for (i = 0; i < clip_len - 1; i = i + 1) {
        int tmp_v[100][2];
        int tmp_len = p2_len;
        for (int j = 0; j < p2_len; j = j + 1) {
            tmp_v[j][0] = p2_v[j][0];
            tmp_v[j][1] = p2_v[j][1];
        }
        p2_len = p1_len;
        for (int j = 0; j < p1_len; j = j + 1) {
            p2_v[j][0] = p1_v[j][0];
            p2_v[j][1] = p1_v[j][1];
        }
        p1_len = tmp_len;
        for (int j = 0; j < tmp_len; j = j + 1) {
            p1_v[j][0] = tmp_v[j][0];
            p1_v[j][1] = tmp_v[j][1];
        }
        if (p1_len == 0) {
            p2_len = 0;
            break;
        }
        poly_edge_clip(p1_v, p1_len, clip_v[i][0], clip_v[i][1], clip_v[i + 1][0], clip_v[i + 1][1], dir, p2_v, &p2_len);
    }
    for (i = 0; i < p2_len; i = i + 1) {
        res_v[i][0] = p2_v[i][0];
        res_v[i][1] = p2_v[i][1];
    }
    res_len[0] = p2_len;
    return;
}
