int maze_walk_solve(int x, int y, int tox, int toy, int cell[][100], int dirs[4][2]) {
    int i;
    int x1;
    int y1;
    int t;
    
    cell[y][x] = cell[y][x] | 16;
    if ((x == tox) && (y == toy)) {
        return 1;
    }
    
    for (i = 0; i <= 3; i = i + 1) {
        x1 = x + dirs[i][0];
        y1 = y + dirs[i][1];
        if (cell[y1][x1]) {
            continue;
        }
        
        if (x1 == x) {
            t = (y + y1) / 2;
            if (cell[t][x] || !maze_walk_solve(x1, y1, tox, toy, cell, dirs)) {
                continue;
            }
            cell[t-1][x] = cell[t-1][x] | 2;
            cell[t][x] = cell[t][x] | 16 | 1 | 2;
            cell[t+1][x] = cell[t+1][x] | 1;
        } else {
            if (y1 == y) {
                t = (x + x1) / 2;
                if (cell[y][t] || !maze_walk_solve(x1, y1, tox, toy, cell, dirs)) {
                    continue;
                }
                cell[y][t-1] = cell[y][t-1] | 8;
                cell[y][t] = cell[y][t] | 16 | 8 | 4;
                cell[y][t+1] = cell[y][t+1] | 4;
            }
        }
        return 1;
    }
    
    cell[y][x] = cell[y][x] & ~16;
    return 0;
}

void maze_generate(int x, int y, int cell[][100], int dirs[4][2], int *avail) {
    int i;
    int t;
    int x1;
    int y1;
    int d[4] = {0, 1, 2, 3};
    int temp;
    
    cell[y][x] = cell[y][x] | 16;
    *avail = *avail - 1;
    
    for (x1 = 3; x1; x1 = x1 - 1) {
        y1 = rand() % (x1 + 1);
        if (x1 != y1) {
            temp = d[x1];
            d[x1] = d[y1];
            d[y1] = temp;
        }
    }
    
    for (i = 0; (*avail) && (i < 4); i = i + 1) {
        x1 = x + dirs[d[i]][0];
        y1 = y + dirs[d[i]][1];
        
        if (cell[y1][x1] & 16) {
            continue;
        }
        
        if (x1 == x) {
            t = (y + y1) / 2;
            cell[t][x+1] = cell[t][x+1] & ~4;
            cell[t][x] = cell[t][x] & ~(8 | 4);
            cell[t][x-1] = cell[t][x-1] & ~8;
        } else {
            if (y1 == y) {
                t = (x + x1) / 2;
                cell[y-1][t] = cell[y-1][t] & ~2;
                cell[y][t] = cell[y][t] & ~(1 | 2);
                cell[y+1][t] = cell[y+1][t] & ~1;
            }
        }
        maze_generate(x1, y1, cell, dirs, avail);
    }
    return;
}
