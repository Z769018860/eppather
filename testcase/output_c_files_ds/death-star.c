void draw_sphere() {
    int light[3] = {-50, 0, 50};
    int pos_cx = 20, pos_cy = 20, pos_cz = 0, pos_r = 20;
    int neg_cx = 1, neg_cy = 1, neg_cz = -6, neg_r = 20;
    char shades[11] = ".:!*oe&#%@";
    int i, j, intensity, hit_result;
    int b;
    int vec[3], x, y, zb1, zb2, zs1, zs2;
    int k = 2;
    int ambient = 0.3 * 1000;

    for (i = pos_cy - pos_r; i <= pos_cy + pos_r; i = i + 1) {
        y = i;
        for (j = pos_cx - 2 * pos_r; j <= pos_cx + 2 * pos_r; j = j + 1) {
            x = (j - pos_cx) / 2 + pos_cx;

            int x_tmp = x - pos_cx;
            int y_tmp = y - pos_cy;
            int zsq = pos_r * pos_r - (x_tmp * x_tmp + y_tmp * y_tmp);
            if (zsq < 0) {
                hit_result = 0;
            } else {
                zb1 = pos_cz - zsq;
                zb2 = pos_cz + zsq;
                x_tmp = x - neg_cx;
                y_tmp = y - neg_cy;
                zsq = neg_r * neg_r - (x_tmp * x_tmp + y_tmp * y_tmp);
                if (zsq < 0) {
                    hit_result = 1;
                } else {
                    zs1 = neg_cz - zsq;
                    zs2 = neg_cz + zsq;
                    if (zs1 > zb1) {
                        hit_result = 1;
                    } else if (zs2 > zb2) {
                        hit_result = 0;
                    } else if (zs2 > zb1) {
                        hit_result = 2;
                    } else {
                        hit_result = 1;
                    }
                }
            }

            if (hit_result == 0) {
                continue;
            } else if (hit_result == 1) {
                vec[0] = x - pos_cx;
                vec[1] = y - pos_cy;
                vec[2] = zb1 - pos_cz;
            } else {
                vec[0] = neg_cx - x;
                vec[1] = neg_cy - y;
                vec[2] = neg_cz - zs2;
            }

            int len_sq = vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
            int len = 1;
            if (len_sq > 0) {
                len = len_sq;
            }
            vec[0] = vec[0] / len;
            vec[1] = vec[1] / len;
            vec[2] = vec[2] / len;

            int dot = light[0] * vec[0] + light[1] * vec[1] + light[2] * vec[2];
            if (dot < 0) {
                dot = -dot;
            } else {
                dot = 0;
            }

            int pow_val = 1;
            for (int p = 0; p < k; p = p + 1) {
                pow_val = pow_val * dot;
            }
            b = pow_val + ambient;
            intensity = (1000 - b) * 10 / 1000;
            if (intensity < 0) {
                intensity = 0;
            }
            if (intensity >= 10) {
                intensity = 9;
            }
        }
    }
    return;
}
