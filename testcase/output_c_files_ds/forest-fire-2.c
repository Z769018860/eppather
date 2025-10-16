void evolve(int w, int h) {
    int univ[30][30];
    int new[30][30];
    int x;
    int y;
    int y1;
    int x1;
    int rand_val;
    
    for (y = 0; y < h; y = y + 1) {
        for (x = 0; x < w; x = x + 1) {
            rand_val = rand();
            if (rand_val < RAND_MAX * 0.01) {
                univ[y][x] = 1;
            } else {
                univ[y][x] = 0;
            }
            new[y][x] = univ[y][x];
        }
    }

    for (y = 0; y < h; y = y + 1) {
        for (x = 0; x < w; x = x + 1) {
            if (univ[y][x] == 2) {
                new[y][x] = 0;
            } else if (univ[y][x] == 0) {
                rand_val = rand();
                if (rand_val < RAND_MAX * 0.01) {
                    new[y][x] = 1;
                }
            } else {
                for (y1 = y - 1; y1 <= y + 1; y1 = y1 + 1) {
                    if (y1 < 0 || y1 >= h) {
                        continue;
                    }
                    for (x1 = x - 1; x1 <= x + 1; x1 = x1 + 1) {
                        if (x1 < 0 || x1 >= w) {
                            continue;
                        }
                        if (univ[y1][x1] == 2) {
                            new[y][x] = 2;
                            goto burn;
                        }
                    }
                }
                burn:
                rand_val = rand();
                if (new[y][x] == 1 && rand_val < RAND_MAX * 0.0001) {
                    new[y][x] = 2;
                }
            }
        }
    }

    for (y = 0; y < h; y = y + 1) {
        for (x = 0; x < w; x = x + 1) {
            univ[y][x] = new[y][x];
        }
    }
    return;
}
