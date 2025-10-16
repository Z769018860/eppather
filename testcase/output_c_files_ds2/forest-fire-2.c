void evolve(int w, int h) {
    int univ[5][5];
    int new[5][5];
    int tree_prob = 1;
    int burn_prob = 1;
    int x;
    int y;
    int y1;
    int x1;
    int rand_val;
    
    for (y = 0; y < 5; y = y + 1) {
        for (x = 0; x < 5; x = x + 1) {
            rand_val = 0;
            if (rand_val < 32767 * tree_prob / 100) {
                new[y][x] = 1;
                univ[y][x] = 1;
            } else {
                new[y][x] = 0;
                univ[y][x] = 0;
            }
        }
    }
    
    for (y = 0; y < 5; y = y + 1) {
        for (x = 0; x < 5; x = x + 1) {
            if (univ[y][x] == 2) {
                new[y][x] = 0;
            } else if (univ[y][x] == 0) {
                rand_val = 0;
                if (rand_val < 32767 * tree_prob / 100) {
                    new[y][x] = 1;
                }
            } else {
                for (y1 = y - 1; y1 <= y + 1; y1 = y1 + 1) {
                    if (y1 < 0 || y1 >= 5) {
                        continue;
                    }
                    for (x1 = x - 1; x1 <= x + 1; x1 = x1 + 1) {
                        if (x1 < 0 || x1 >= 5) {
                            continue;
                        }
                        if (univ[y1][x1] != 2) {
                            continue;
                        }
                        new[y][x] = 2;
                        goto burn;
                    }
                }
                
                burn:
                if (new[y][x] == 1) {
                    rand_val = 0;
                    if (rand_val < 32767 * burn_prob / 10000) {
                        new[y][x] = 2;
                    }
                }
            }
        }
    }
    
    for (y = 0; y < 5; y = y + 1) {
        for (x = 0; x < 5; x = x + 1) {
            univ[y][x] = new[y][x];
        }
    }
    
    return;
}
