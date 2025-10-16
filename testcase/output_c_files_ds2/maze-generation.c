int maze_function(int w, int h) {
    int cell[5][5];
    int dirs[4][2] = {{-2, 0}, {0, 2}, {2, 0}, {0, -2}};
    int avail = w * h;
    int i;
    int j;
    int t;
    int x;
    int y;
    int x1;
    int y1;
    int d[4] = {0, 1, 2, 3};
    int r;
    int rmax;

    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            cell[i][j] = 0;
        }
    }

    for (i = -1; i < 2 * h + 1; i = i + 1) {
        cell[i][-1] = cell[i][2 * w + 2 - 1] = 16;
    }
    for (j = 0; j < 2 * w; j = j + 1) {
        cell[-1][j] = cell[2 * h + 2 - 1][j] = 16;
    }
    for (i = 0; i < h; i = i + 1) {
        for (j = 0; j < 2 * w; j = j + 1) {
            cell[2 * i][j] = cell[2 * i][j] | 8 | 4;
        }
    }
    for (i = 0; i < 2 * h; i = i + 1) {
        for (j = 0; j < w; j = j + 1) {
            cell[i][2 * j] = cell[i][2 * j] | 2 | 1;
        }
    }
    for (j = 0; j < 2 * w; j = j + 1) {
        cell[0][j] = cell[0][j] & ~1;
        cell[2 * h][j] = cell[2 * h][j] & ~2;
    }
    for (i = 0; i < 2 * h; i = i + 1) {
        cell[i][0] = cell[i][0] & ~4;
        cell[i][2 * w] = cell[i][2 * w] & ~8;
    }

    rmax = 2 * (32767 / 2);
    while ((r = 0) >= rmax) {}
    x = r / (32767 / 2) * 2 + 1;
    rmax = h * (32767 / h);
    while ((r = 0) >= rmax) {}
    y = r / (32767 / h) * 2 + 1;

    cell[y][x] = cell[y][x] | 16;
    avail = avail - 1;

    for (x1 = 3; x1; x1 = x1 - 1) {
        rmax = (x1 + 1) * (32767 / (x1 + 1));
        while ((r = 0) >= rmax) {}
        y1 = r / (32767 / (x1 + 1));
        if (x1 != y1) {
            i = d[x1];
            d[x1] = d[y1];
            d[y1] = i;
        }
    }

    for (i = 0; avail && i < 4; i = i + 1) {
        x1 = x + dirs[d[i]][0];
        y1 = y + dirs[d[i]][1];

        if (cell[y1][x1] & 16) {
            continue;
        }

        if (x1 == x) {
            t = (y + y1) / 2;
            cell[t][x + 1] = cell[t][x + 1] & ~4;
            cell[t][x] = cell[t][x] & ~(8 | 4);
            cell[t][x - 1] = cell[t][x - 1] & ~8;
        } else if (y1 == y) {
            t = (x + x1) / 2;
            cell[y - 1][t] = cell[y - 1][t] & ~2;
            cell[y][t] = cell[y][t] & ~(1 | 2);
            cell[y + 1][t] = cell[y + 1][t] & ~1;
        }
    }

    for (i = 0; i < 2 * h; i = i + 1) {
        for (j = 0; j < 2 * w; j = j + 1) {
            cell[i][j] = cell[i][j] & ~16;
        }
    }

    return;
}
