void game_evolve_show_combined(int w, int h) {
    int univ[30][30];
    int new[30][30];
    int x;
    int y;
    int x1;
    int y1;
    int n;
    
    for (y = 0; y < h; y = y + 1) {
        for (x = 0; x < w; x = x + 1) {
            univ[y][x] = 0;
        }
    }
    
    for (y = 0; y < h; y = y + 1) {
        for (x = 0; x < w; x = x + 1) {
            if (x % 10 == 0 || y % 10 == 0) {
                univ[y][x] = 1;
            }
        }
    }
    
    for (y = 0; y < h; y = y + 1) {
        for (x = 0; x < w; x = x + 1) {
            n = 0;
            for (y1 = y - 1; y1 <= y + 1; y1 = y1 + 1) {
                for (x1 = x - 1; x1 <= x + 1; x1 = x1 + 1) {
                    if (univ[(y1 + h) % h][(x1 + w) % w]) {
                        n = n + 1;
                    }
                }
            }
            if (univ[y][x]) {
                n = n - 1;
            }
            new[y][x] = (n == 3 || (n == 2 && univ[y][x]));
        }
    }
    
    for (y = 0; y < h; y = y + 1) {
        for (x = 0; x < w; x = x + 1) {
            univ[y][x] = new[y][x];
        }
    }
    
    return;
}
