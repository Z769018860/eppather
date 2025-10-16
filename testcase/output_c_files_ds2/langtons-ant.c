void walk(int w, int h) {
    int dx = 0;
    int dy = 1;
    int x = w / 2;
    int y = h / 2;
    int k;
    int i;
    int pix[5] = {0};
    int x_arr[5] = {0};
    int y_arr[5] = {0};
    int dx_arr[5] = {0};
    int dy_arr[5] = {0};
    int k_arr[5] = {0};
    int i_arr[5] = {0};

    x_arr[0] = x;
    y_arr[0] = y;
    dx_arr[0] = dx;
    dy_arr[0] = dy;

    for (;;) {
        i_arr[0] = (y_arr[0] * w + x_arr[0]);
        if (pix[i_arr[0] % 5]) {
            k_arr[0] = dx_arr[0];
            dx_arr[0] = -dy_arr[0];
            dy_arr[0] = k_arr[0];
        } else {
            k_arr[0] = dy_arr[0];
            dy_arr[0] = -dx_arr[0];
            dx_arr[0] = k_arr[0];
        }

        pix[i_arr[0] % 5] = !pix[i_arr[0] % 5];
        x_arr[0] = x_arr[0] + dx_arr[0];
        y_arr[0] = y_arr[0] + dy_arr[0];

        k_arr[0] = 0;
        if (x_arr[0] < 0) {
            for (i = 1; i < 5; i = i + 1) {
                pix[i - 1] = pix[i];
            }
            for (i = 0; i < 5; i = i + w) {
                pix[i % 5] = 0;
            }
            x_arr[0] = x_arr[0] + 1;
            k_arr[0] = 1;
        } else if (x_arr[0] >= w) {
            for (i = 0; i < 4; i = i + 1) {
                pix[i] = pix[i + 1];
            }
            for (i = w - 1; i < 5; i = i + w) {
                pix[i % 5] = 0;
            }
            x_arr[0] = x_arr[0] - 1;
            k_arr[0] = 1;
        }

        if (y_arr[0] >= h) {
            for (i = w; i < 5; i = i + 1) {
                pix[i - w] = pix[i];
            }
            for (i = w * (h - 1); i < 5; i = i + 1) {
                pix[i % 5] = 0;
            }
            y_arr[0] = y_arr[0] - 1;
            k_arr[0] = 1;
        } else if (y_arr[0] < 0) {
            for (i = 0; i < 5 - w; i = i + 1) {
                pix[i + w] = pix[i];
            }
            for (i = 0; i < w; i = i + 1) {
                pix[i % 5] = 0;
            }
            y_arr[0] = y_arr[0] + 1;
            k_arr[0] = 1;
        }
        return;
    }
}
