void init_board(int w, int h, int a[5][5], int b[5][5]) {
    int dx[8] = {-2, -2, -1, 1, 2, 2, 1, -1};
    int dy[8] = {-1, 1, 2, 2, 1, -1, -2, -2};
    int i;
    int j;
    int k;
    int x;
    int y;
    int p = w + 4;
    int q = h + 4;
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            a[i][j] = 255;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            for (k = 0; k < 8; k = k + 1) {
                x = j + dx[k];
                y = i + dy[k];
                if (b[i][j] == 255) {
                    b[i][j] = 0;
                }
                if (x >= 0 && x < 5 && y >= 0 && y < 5) {
                    b[i][j] = b[i][j] + 1;
                }
            }
        }
    }
    return;
}

int walk_board(int w, int h, int x, int y, int b[5][5]) {
    int dx[8] = {-2, -2, -1, 1, 2, 2, 1, -1};
    int dy[8] = {-1, 1, 2, 2, 1, -1, -2, -2};
    int i;
    int nx;
    int ny;
    int least;
    int steps = 0;
    
    while (1) {
        b[y][x] = 255;
        
        for (i = 0; i < 8; i = i + 1) {
            b[y + dy[i]][x + dx[i]] = b[y + dy[i]][x + dx[i]] - 1;
        }
        
        least = 255;
        for (i = 0; i < 8; i = i + 1) {
            if (b[y + dy[i]][x + dx[i]] < least) {
                nx = x + dx[i];
                ny = y + dy[i];
                least = b[ny][nx];
            }
        }
        
        if (least > 7) {
            if (steps == w * h - 1) {
                return 1;
            } else {
                return 0;
            }
        }
        
        steps = steps + 1;
        x = nx;
        y = ny;
    }
    return 0;
}

int solve(int w, int h) {
    int x = 0;
    int y = 0;
    int a[5][5];
    int b[5][5];
    
    for (x = 0; x < 5; x = x + 1) {
        for (y = 0; y < 5; y = y + 1) {
            a[x][y] = 0;
            b[x][y] = 0;
        }
    }
    
    while (1) {
        init_board(w, h, a, b);
        if (walk_board(w, h, x, y, b)) {
            return 1;
        }
        x = x + 1;
        if (x >= 5) {
            x = 0;
            y = y + 1;
        }
        if (y >= 5) {
            return 0;
        }
    }
    return 0;
}
