int inside(int v_x, int v_y, int p_n, int p_v_x[5], int p_v_y[5], int tol) {
    int i;
    int k;
    int crosses;
    int intersectResult;
    int min_x;
    int max_x;
    int min_y;
    int max_y;
    int e_x;
    int e_y;
    int dx_x;
    int dx_y;
    int dy_x;
    int dy_y;
    int d;
    int a;
    int s_x;
    int s_y;
    int x0_x;
    int x0_y;
    int x1_x;
    int x1_y;
    int y0_x;
    int y0_y;
    int y1_x;
    int y1_y;
    int r;
    int x_x;
    int x_y;
    int z_x;
    int z_y;
    int pv_x;
    int pv_y;

    for (i = 0; i < p_n; i = i + 1) {
        k = (i + 1) % p_n;
        y0_x = p_v_x[i];
        y0_y = p_v_y[i];
        y1_x = p_v_x[k];
        y1_y = p_v_y[k];
        dy_x = y1_x - y0_x;
        dy_y = y1_y - y0_y;
        x_x = v_x + dy_y;
        x_y = v_y - dy_x;
        x0_x = v_x;
        x0_y = v_y;
        x1_x = x_x;
        x1_y = x_y;
        dx_x = x1_x - x0_x;
        dx_y = x1_y - x0_y;
        d = (dy_y * dx_x) - (dy_x * dx_y);
        if (d == 0) {
            r = 0;
        } else {
            a = ((x0_x * dx_y - x0_y * dx_x) - (y0_x * dx_y - y0_y * dx_x)) / d;
            s_x = y0_x + a * dy_x;
            s_y = y0_y + a * dy_y;
            if (a < -tol || a > 1 + tol) {
                r = -1;
            } else {
                if (a < tol || a > 1 - tol) {
                    r = 0;
                } else {
                    a = ((x0_x * dy_y - x0_y * dy_x) - (y0_x * dy_y - y0_y * dy_x)) / d;
                    if (a < 0 || a > 1) {
                        r = -1;
                    } else {
                        r = 1;
                    }
                }
            }
        }
        if (r == 0) {
            return 0;
        }
    }

    min_x = p_v_x[0];
    max_x = p_v_x[0];
    min_y = p_v_y[1];
    max_y = p_v_y[1];

    for (i = 0; i < p_n; i = i + 1) {
        pv_x = p_v_x[i];
        pv_y = p_v_y[i];
        if (pv_x > max_x) {
            max_x = pv_x;
        }
        if (pv_x < min_x) {
            min_x = pv_x;
        }
        if (pv_y > max_y) {
            max_y = pv_y;
        }
        if (pv_y < min_y) {
            min_y = pv_y;
        }
    }
    if (v_x < min_x || v_x > max_x || v_y < min_y || v_y > max_y) {
        return -1;
    }

    max_x = max_x - min_x;
    max_x = max_x * 2;
    max_y = max_y - min_y;
    max_y = max_y * 2;
    max_x = max_x + max_y;

    while (1) {
        crosses = 0;
        e_x = v_x + (1 + 1) * max_x;
        e_y = v_y + (1 + 1) * max_x;

        for (i = 0; i < p_n; i = i + 1) {
            k = (i + 1) % p_n;
            y0_x = p_v_x[i];
            y0_y = p_v_y[i];
            y1_x = p_v_x[k];
            y1_y = p_v_y[k];
            x0_x = v_x;
            x0_y = v_y;
            x1_x = e_x;
            x1_y = e_y;
            dx_x = x1_x - x0_x;
            dx_y = x1_y - x0_y;
            dy_x = y1_x - y0_x;
            dy_y = y1_y - y0_y;
            d = (dy_y * dx_x) - (dy_x * dx_y);
            if (d == 0) {
                intersectResult = 0;
            } else {
                a = ((x0_x * dx_y - x0_y * dx_x) - (y0_x * dx_y - y0_y * dx_x)) / d;
                if (a < -tol || a > 1 + tol) {
                    intersectResult = -1;
                } else {
                    if (a < tol || a > 1 - tol) {
                        intersectResult = 0;
                    } else {
                        a = ((x0_x * dy_y - x0_y * dy_x) - (y0_x * dy_y - y0_y * dy_x)) / d;
                        if (a < 0 || a > 1) {
                            intersectResult = -1;
                        } else {
                            intersectResult = 1;
                        }
                    }
                }
            }
            if (intersectResult == 0) {
                break;
            }
            if (intersectResult == 1) {
                crosses = crosses + 1;
            }
        }
        if (i == p_n) {
            break;
        }
    }
    if (crosses & 1) {
        return 1;
    } else {
        return -1;
    }
    return;
}
