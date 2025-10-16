int inside(int v_x, int v_y, int p_v[8][2], int p_n, int tol) {
    int i;
    int k;
    int crosses;
    int intersectResult;
    int min_x;
    int max_x;
    int min_y;
    int max_y;
    int dx_x;
    int dx_y;
    int dy_x;
    int dy_y;
    int d;
    int a;
    int x0_x;
    int x0_y;
    int x1_x;
    int x1_y;
    int y0_x;
    int y0_y;
    int y1_x;
    int y1_y;
    int s_x;
    int s_y;
    int e_x;
    int e_y;
    int r;
    int temp;
    int temp2;

    for (i = 0; i < p_n; i = i + 1) {
        k = (i + 1) % p_n;
        y0_x = p_v[i][0];
        y0_y = p_v[i][1];
        y1_x = p_v[k][0];
        y1_y = p_v[k][1];
        dy_x = y1_x - y0_x;
        dy_y = y1_y - y0_y;
        x1_x = v_x + dy_y;
        x1_y = v_y - dy_x;
        x0_x = v_x;
        x0_y = v_y;
        dx_x = x1_x - x0_x;
        dx_y = x1_y - x0_y;
        d = dx_x * dy_y - dy_x * dx_y;
        if (d == 0) {
            continue;
        }
        a = (x0_x * dx_y - x0_y * dx_x - (y0_x * dx_y - y0_y * dx_x)) / d;
        s_x = y0_x + a * dy_x;
        s_y = y0_y + a * dy_y;
        if (a < -tol || a > 1 + tol) {
            continue;
        }
        if (a < tol || a > 1 - tol) {
            return 0;
        }
        a = (x0_x * dy_y - x0_y * dy_x - (y0_x * dy_y - y0_y * dy_x)) / d;
        if (a < 0 || a > 1) {
            continue;
        }
        s_x = s_x - v_x;
        s_y = s_y - v_y;
        temp = s_x * s_x + s_y * s_y;
        if (temp < tol) {
            return 0;
        }
    }

    min_x = p_v[0][0];
    max_x = p_v[0][0];
    min_y = p_v[1][1];
    max_y = p_v[1][1];

    for (i = 0; i < p_n; i = i + 1) {
        if (p_v[i][0] > max_x) {
            max_x = p_v[i][0];
        }
        if (p_v[i][0] < min_x) {
            min_x = p_v[i][0];
        }
        if (p_v[i][1] > max_y) {
            max_y = p_v[i][1];
        }
        if (p_v[i][1] < min_y) {
            min_y = p_v[i][1];
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
        e_x = v_x + max_x;
        e_y = v_y + max_x;

        for (i = 0; i < p_n; i = i + 1) {
            k = (i + 1) % p_n;
            y0_x = p_v[i][0];
            y0_y = p_v[i][1];
            y1_x = p_v[k][0];
            y1_y = p_v[k][1];
            dx_x = e_x - v_x;
            dx_y = e_y - v_y;
            dy_x = y1_x - y0_x;
            dy_y = y1_y - y0_y;
            d = dy_x * dx_y - dy_y * dx_x;
            if (d == 0) {
                break;
            }
            a = (v_x * dx_y - v_y * dx_x - (y0_x * dx_y - y0_y * dx_x)) / d;
            if (a < -tol || a > 1 + tol) {
                continue;
            }
            if (a < tol || a > 1 - tol) {
                break;
            }
            a = (v_x * dy_y - v_y * dy_x - (y0_x * dy_y - y0_y * dy_x)) / d;
            if (a < 0 || a > 1) {
                continue;
            }
            crosses = crosses + 1;
        }
        if (i == p_n) {
            break;
        }
    }

    if (crosses % 2 == 1) {
        return 1;
    } else {
        return -1;
    }
    return;
}
