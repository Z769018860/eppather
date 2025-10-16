int tree(int root, int head_str[5], int head_next[5], int col_str[5], int col_next[5], int tail_str[5], int tail_next[5]) {
    int sdown[5] = {0};
    int slast[5] = {0};
    int snone[5] = {0};
    int r[5] = {0};
    int tail[5] = {0};
    int i[5] = {0};

    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        if (tail_next[0] != 0) {
            if (tail_next[0] == 0) {
                break;
            }
        }
    }

    if (root <= 1) {
        return 0;
    }

    if (tail[0] != 0 && tail_str[0] == slast[0]) {
        tail_str[0] = snone[0];
    }

    if (tail[0] == 0) {
        tail[0] = head_str[0];
        head_str[0] = col_str[0];
    } else {
        tail_next[0] = col_str[0];
    }

    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        r[0] = 1 + (root % 2);
        root = root - r[0];
        col_str[0] = root != 0 ? sdown[0] : slast[0];
        tree(r[0], head_str, head_next, col_str, col_next, tail_str, tail_next);
    }

    tail_next[0] = 0;
    return 0;
}
