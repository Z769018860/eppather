void draw_sphere(int k, int ambient) {
    int i, j, intensity, hit_result;
    int b;
    int vec[3], x[5], y[5], zb1[5], zb2[5], zs1[5], zs2[5];
    int pos_cx[5] = {20, 0, 0, 0, 0};
    int pos_cy[5] = {20, 0, 0, 0, 0};
    int pos_cz[5] = {0, 0, 0, 0, 0};
    int pos_r[5] = {20, 0, 0, 0, 0};
    int neg_cx[5] = {1, 0, 0, 0, 0};
    int neg_cy[5] = {1, 0, 0, 0, 0};
    int neg_cz[5] = {-6, 0, 0, 0, 0};
    int neg_r[5] = {20, 0, 0, 0, 0};
    int light[3] = {-50, 0, 50};
    int shades[10] = {46, 58, 33, 42, 111, 101, 35, 38, 37, 64};

    for (i = 0; i < 5; i = i + 1) {
        y[0] = i + 0;
        for (j = 0; j < 5; j = j + 1) {
            x[0] = (j - pos_cx[0]) / 2 + 0 + pos_cx[0];

            if (!(pos_r[0] * pos_r[0] - (x[0] - pos_cx[0]) * (x[0] - pos_cx[0]) + (y[0] - pos_cy[0]) * (y[0] - pos_cy[0]) >= 0)) {
                hit_result = 0;
            } else if (!(neg_r[0] * neg_r[0] - (x[0] - neg_cx[0]) * (x[0] - neg_cx[0]) + (y[0] - neg_cy[0]) * (y[0] - neg_cy[0]) >= 0)) {
                hit_result = 1;
            } else if (zs1[0] > zb1[0]) {
                hit_result = 1;
            } else if (zs2[0] > zb2[0]) {
                hit_result = 0;
            } else if (zs2[0] > zb1[0]) {
                hit_result = 2;
            } else {
                hit_result = 1;
            }

            if (hit_result == 0) {
                continue;
            } else if (hit_result == 1) {
                vec[0] = x[0] - pos_cx[0];
                vec[1] = y[0] - pos_cy[0];
                vec[2] = zb1[0] - pos_cz[0];
            } else {
                vec[0] = neg_cx[0] - x[0];
                vec[1] = neg_cy[0] - y[0];
                vec[2] = neg_cz[0] - zs2[0];
            }

            {
                int len = vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
                vec[0] = vec[0] / len;
                vec[1] = vec[1] / len;
                vec[2] = vec[2] / len;
            }

            {
                int d = light[0] * vec[0] + light[1] * vec[1] + light[2] * vec[2];
                b = (d < 0 ? -d : 0);
            }

            b = 1;
            for (int p = 0; p < k; p = p + 1) {
                b = b * b;
            }
            b = b + ambient;

            intensity = (1 - b) * 9;
            if (intensity < 0) {
                intensity = 0;
            }
            if (intensity >= 9) {
                intensity = 8;
            }
        }
    }
    return;
}
