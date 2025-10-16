void evolve(int* u, int w, int h) {
    int new[5][5];
    int univ[5][5];
    int x;
    int y;
    int y1;
    int x1;
    int n;
    
    for (y = 0; y < 5; y = y + 1) {
        for (x = 0; x < 5; x = x + 1) {
            univ[y][x] = u[y * 5 + x];
        }
    }
    
    for (y = 0; y < 5; y = y + 1) {
        for (x = 0; x < 5; x = x + 1) {
            n = 0;
            for (y1 = y - 1; y1 <= y + 1; y1 = y1 + 1) {
                for (x1 = x - 1; x1 <= x + 1; x1 = x1 + 1) {
                    if (univ[(y1 + 5) % 5][(x1 + 5) % 5]) {
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
    
    for (y = 0; y < 5; y = y + 1) {
        for (x = 0; x < 5; x = x + 1) {
            univ[y][x] = new[y][x];
        }
    }
    
    for (y = 0; y < 5; y = y + 1) {
        for (x = 0; x < 5; x = x + 1) {
            u[y * 5 + x] = univ[y][x];
        }
    }
    
    return;
}
