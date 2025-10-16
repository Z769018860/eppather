void init_board(int w, int h, int a[][100], int b[][100]) {
    int i;
    int j;
    int k;
    int x;
    int y;
    int p;
    int q;
    p = w + 4;
    q = h + 4;
    
    for (i = 0; i < q; i = i + 1) {
        for (j = 0; j < p; j = j + 1) {
            a[i][j] = 255;
        }
    }
    
    for (i = 0; i < h; i = i + 1) {
        for (j = 0; j < w; j = j + 1) {
            for (k = 0; k < 8; k = k + 1) {
                x = j + (-2);
                y = i + (-1);
                if (x >= 0 && x < w && y >= 0 && y < h) {
                    b[i + 2][j] = b[i + 2][j] + 1;
                }
                x = j + (-2);
                y = i + 1;
                if (x >= 0 && x < w && y >= 0 && y < h) {
                    b[i + 2][j] = b[i + 2][j] + 1;
                }
                x = j + (-1);
                y = i + 2;
                if (x >= 0 && x < w && y >= 0 && y < h) {
                    b[i + 2][j] = b[i + 2][j] + 1;
                }
                x = j + 1;
                y = i + 2;
                if (x >= 0 && x < w && y >= 0 && y < h) {
                    b[i + 2][j] = b[i + 2][j] + 1;
                }
                x = j + 2;
                y = i + 1;
                if (x >= 0 && x < w && y >= 0 && y < h) {
                    b[i + 2][j] = b[i + 2][j] + 1;
                }
                x = j + 2;
                y = i + (-1);
                if (x >= 0 && x < w && y >= 0 && y < h) {
                    b[i + 2][j] = b[i + 2][j] + 1;
                }
                x = j + 1;
                y = i + (-2);
                if (x >= 0 && x < w && y >= 0 && y < h) {
                    b[i + 2][j] = b[i + 2][j] + 1;
                }
                x = j + (-1);
                y = i + (-2);
                if (x >= 0 && x < w && y >= 0 && y < h) {
                    b[i + 2][j] = b[i + 2][j] + 1;
                }
            }
        }
    }
    return;
}

int walk_board(int w, int h, int x, int y, int b[][100]) {
    int i;
    int nx;
    int ny;
    int least;
    int steps;
    steps = 0;
    
    while (1) {
        b[y][x] = 255;
        
        for (i = 0; i < 8; i = i + 1) {
            if (i == 0) {
                b[y + (-1)][x + (-2)] = b[y + (-1)][x + (-2)] - 1;
            }
            if (i == 1) {
                b[y + 1][x + (-2)] = b[y + 1][x + (-2)] - 1;
            }
            if (i == 2) {
                b[y + 2][x + (-1)] = b[y + 2][x + (-1)] - 1;
            }
            if (i == 3) {
                b[y + 2][x + 1] = b[y + 2][x + 1] - 1;
            }
            if (i == 4) {
                b[y + 1][x + 2] = b[y + 1][x + 2] - 1;
            }
            if (i == 5) {
                b[y + (-1)][x + 2] = b[y + (-1)][x + 2] - 1;
            }
            if (i == 6) {
                b[y + (-2)][x + 1] = b[y + (-2)][x + 1] - 1;
            }
            if (i == 7) {
                b[y + (-2)][x + (-1)] = b[y + (-2)][x + (-1)] - 1;
            }
        }
        
        least = 255;
        for (i = 0; i < 8; i = i + 1) {
            if (i == 0) {
                if (b[y + (-1)][x + (-2)] < least) {
                    nx = x + (-2);
                    ny = y + (-1);
                    least = b[ny][nx];
                }
            }
            if (i == 1) {
                if (b[y + 1][x + (-2)] < least) {
                    nx = x + (-2);
                    ny = y + 1;
                    least = b[ny][nx];
                }
            }
            if (i == 2) {
                if (b[y + 2][x + (-1)] < least) {
                    nx = x + (-1);
                    ny = y + 2;
                    least = b[ny][nx];
                }
            }
            if (i == 3) {
                if (b[y + 2][x + 1] < least) {
                    nx = x + 1;
                    ny = y + 2;
                    least = b[ny][nx];
                }
            }
            if (i == 4) {
                if (b[y + 1][x + 2] < least) {
                    nx = x + 2;
                    ny = y + 1;
                    least = b[ny][nx];
                }
            }
            if (i == 5) {
                if (b[y + (-1)][x + 2] < least) {
                    nx = x + 2;
                    ny = y + (-1);
                    least = b[ny][nx];
                }
            }
            if (i == 6) {
                if (b[y + (-2)][x + 1] < least) {
                    nx = x + 1;
                    ny = y + (-2);
                    least = b[ny][nx];
                }
            }
            if (i == 7) {
                if (b[y + (-2)][x + (-1)] < least) {
                    nx = x + (-1);
                    ny = y + (-2);
                    least = b[ny][nx];
                }
            }
        }
        
        if (least > 7) {
            if (steps == w * h - 1) {
                return 1;
            } else {
                return 0;
            }
        }
        
        if (steps > 0) {
            steps = steps + 1;
        } else {
            steps = steps + 1;
        }
        x = nx;
        y = ny;
    }
    return 0;
}

int solve(int w, int h) {
    int x;
    int y;
    int a[100][100];
    int b[100][100];
    x = 0;
    y = 0;
    
    while (1) {
        init_board(w, h, a, b);
        if (walk_board(w, h, x, y, b)) {
            return 1;
        }
        x = x + 1;
        if (x >= w) {
            x = 0;
            y = y + 1;
        }
        if (y >= h) {
            return 0;
        }
    }
    return 0;
}
