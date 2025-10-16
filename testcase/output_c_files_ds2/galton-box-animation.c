void sand_simulator(int n1, int w1, int h1, int balls1) {
    int x[5];
    int y[5];
    int b[5];
    int cnt[5];
    cnt[0] = 0;
    int step[5];
    step[0] = 0;
    int i;
    int j;
    int k;
    int idx;
    int xx;
    int yy;
    int c;
    int kill;
    int sl;
    int o;
    int n;
    int w;
    int h;
    int balls;
    n = n1;
    w = w1;
    h = h1;
    balls = balls1;

    for (i = 0; i < h; i = i + 1) {
        for (j = 0; j < w; j = j + 1) {
            b[0] = ' ';
        }
    }

    for (i = 0; i < n; i = i + 1) {
        for (j = -i; j <= i; j = j + 2) {
            if (2 * i + 2 < h && j + w / 2 >= 0 && j + w / 2 < w) {
                b[(2 * i + 2) * w + (j + w / 2)] = '*';
            }
        }
    }

    for (i = 0; i < 5; i = i + 1) {
        x[i] = 0;
        y[i] = 0;
    }

    for (idx = 0; idx < cnt[0]; idx = idx + 1) {
        xx = x[idx];
        yy = y[idx];
        kill = 0;
        sl = 3;
        o = 0;

        if (yy < 0) {
            continue;
        }
        if (yy == h - 1) {
            y[idx] = -1;
            continue;
        }

        c = b[(yy + 1) * w + xx];
        if (c == ' ') {
            yy = yy + 1;
        } else if (c == '*') {
            sl = 1;
            if (xx < w - 1 && b[yy * w + xx + 1] == ' ' && b[(yy + 1) * w + xx + 1] == ' ') {
                if (0 == (12345 % (sl + 1))) {
                    o = 1;
                }
            }
            if (xx > 0 && b[yy * w + xx - 1] == ' ' && b[(yy + 1) * w + xx - 1] == ' ') {
                if (0 == (12345 % (sl + 1))) {
                    o = -1;
                }
            }
            if (o == 0) {
                kill = 1;
            }
            xx = xx + o;
        }

        c = b[y[idx] * w + x[idx]];
        b[y[idx] * w + x[idx]] = ' ';
        y[idx] = yy;
        x[idx] = xx;
        b[yy * w + xx] = c;
        if (kill) {
            y[idx] = -1;
        }
    }

    step[0] = step[0] + 1;
    if (step[0] == 2 && cnt[0] < balls) {
        step[0] = 0;
        x[cnt[0]] = w / 2;
        y[cnt[0]] = 0;
        if (b[y[cnt[0]] * w + x[cnt[0]]] != ' ') {
            return;
        }
        b[y[cnt[0]] * w + x[cnt[0]]] = (12345 % 80) + 43;
        cnt[0] = cnt[0] + 1;
    }
    return;
}
