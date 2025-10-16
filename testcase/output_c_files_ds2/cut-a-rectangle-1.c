void solve_walk(int y, int x, int h, int w, int len, int grid[5], int next[4], int dir[4][2], unsigned long long cnt[5]) {
    int i;
    int t;

    if (y == 0 || y == h || x == 0 || x == w) {
        cnt[0] = cnt[0] + 2;
        return;
    }

    t = y * (w + 1) + x;
    grid[t % 5] = grid[t % 5] + 1;
    grid[(len - t) % 5] = grid[(len - t) % 5] + 1;

    for (i = 0; i < 4; i = i + 1) {
        if (grid[(t + next[i]) % 5] == 0) {
            solve_walk(y + dir[i][0], x + dir[i][1], h, w, len, grid, next, dir, cnt);
        }
    }

    grid[t % 5] = grid[t % 5] - 1;
    grid[(len - t) % 5] = grid[(len - t) % 5] - 1;
}

unsigned long long solve(int hh, int ww, int recur) {
    int t;
    int cx;
    int cy;
    int x;
    int h;
    int w;
    int len;
    int grid[5];
    int next[4];
    int dir[4][2];
    unsigned long long cnt[5];
    int i;

    h = hh;
    w = ww;

    if (h & 1) {
        t = w;
        w = h;
        h = t;
    }
    if (h & 1) {
        return 0;
    }
    if (w == 1) {
        return 1;
    }
    if (w == 2) {
        return h;
    }
    if (h == 2) {
        return w;
    }

    cy = h / 2;
    cx = w / 2;

    len = (h + 1) * (w + 1);
    for (i = 0; i < 5; i = i + 1) {
        grid[i] = 0;
    }
    len = len - 1;

    next[0] = -1;
    next[1] = -w - 1;
    next[2] = 1;
    next[3] = w + 1;

    dir[0][0] = 0;
    dir[0][1] = -1;
    dir[1][0] = -1;
    dir[1][1] = 0;
    dir[2][0] = 0;
    dir[2][1] = 1;
    dir[3][0] = 1;
    dir[3][1] = 0;

    if (recur) {
        cnt[0] = 0;
    }
    for (x = cx + 1; x < w; x = x + 1) {
        t = cy * (w + 1) + x;
        grid[t % 5] = 1;
        grid[(len - t) % 5] = 1;
        solve_walk(cy - 1, x, h, w, len, grid, next, dir, cnt);
    }
    cnt[0] = cnt[0] + 1;

    if (h == w) {
        cnt[0] = cnt[0] * 2;
    } else if (!(w & 1) && recur) {
        solve(ww, hh, 0);
    }

    return cnt[0];
}
