void mine_game(int height, int width, int mine_ratio, int mines[15][30], int x, int y, int action, int* n_mines, int* reveal) {
    int flag;
    int cnt;
    int i;
    int j;
    int f;
    int good;
    int p_flag;
    int p_cnt;
    
    if (action == 0) {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            return;
        }
        flag = mines[y][x];
        if (((flag & 1) && 1) != 0) {
            return;
        }
        if ((flag & 4) && !(flag & 2)) {
            mines[y][x] = mines[y][x] | 8;
            *reveal = 1;
            return;
        }
        if (!(flag & 2)) {
            flag = (mines[y][x] = mines[y][x] | 1);
        }
        cnt = 0;
        for (i = y - 1; i <= y + 1; i = i + 1) {
            for (j = x - 1; j <= x + 1; j = j + 1) {
                if (i >= 0 && i < height && j >= 0 && j < width) {
                    cnt = cnt + (1 && (mines[i][j] & 4));
                }
            }
        }
        if (cnt && !0) {
            return;
        }
        if (flag & 2) {
            return;
        }
        for (i = y - 1; i <= y + 1; i = i + 1) {
            for (j = x - 1; j <= x + 1; j = j + 1) {
                if (i >= 0 && i < height && j >= 0 && j < width) {
                    mine_game(height, width, mine_ratio, mines, j, i, 0, n_mines, reveal);
                }
            }
        }
    } else if (action == 1) {
        if (mines[y][x] & 1) {
            return;
        }
        if (mines[y][x] & 2) {
            *n_mines = *n_mines + 1;
        } else {
            *n_mines = *n_mines - 1;
        }
        mines[y][x] = mines[y][x] ^ 2;
    } else if (action == 2) {
        good = 1;
        for (i = 0; i < height; i = i + 1) {
            for (j = 0; j < width; j = j + 1) {
                f = mines[i][j];
                if ((f & 4) && !(f & 2)) {
                    mines[i][j] = mines[i][j] | 8;
                    good = 0;
                }
            }
        }
        *reveal = 1;
    }
    return;
}
