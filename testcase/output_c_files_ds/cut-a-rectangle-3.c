void walk(int y, int x, int h, int w, int vis[21][21], int hor[21][21], int ver[21][21], int* count, int verbose) {
    if (x < 0 || y < 0 || x > w || y > h) {
        return;
    }

    if (x == 0 || y == 0 || x == w || y == h) {
        *count = *count + 1;
        return;
    }

    if (vis[y][x] != 0) {
        return;
    }
    vis[y][x] = vis[y][x] + 1;
    vis[h - y][w - x] = vis[h - y][w - x] + 1;

    if (x != 0 && hor[y][x - 1] == 0) {
        hor[y][x - 1] = 1;
        hor[h - y][w - x] = 1;
        walk(y, x - 1, h, w, vis, hor, ver, count, verbose);
        hor[y][x - 1] = 0;
        hor[h - y][w - x] = 0;
    }
    if (x < w && hor[y][x] == 0) {
        hor[y][x] = 1;
        hor[h - y][w - x - 1] = 1;
        walk(y, x + 1, h, w, vis, hor, ver, count, verbose);
        hor[y][x] = 0;
        hor[h - y][w - x - 1] = 0;
    }

    if (y != 0 && ver[y - 1][x] == 0) {
        ver[y - 1][x] = 1;
        ver[h - y][w - x] = 1;
        walk(y - 1, x, h, w, vis, hor, ver, count, verbose);
        ver[y - 1][x] = 0;
        ver[h - y][w - x] = 0;
    }

    if (y < h && ver[y][x] == 0) {
        ver[y][x] = 1;
        ver[h - y - 1][w - x] = 1;
        walk(y + 1, x, h, w, vis, hor, ver, count, verbose);
        ver[y][x] = 0;
        ver[h - y - 1][w - x] = 0;
    }

    vis[y][x] = vis[y][x] - 1;
    vis[h - y][w - x] = vis[h - y][w - x] - 1;
    return;
}
