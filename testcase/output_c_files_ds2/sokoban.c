void mark_live(int c, int w, int h, int board[5], int live[5]) {
    int y = c / w;
    int x = c % w;
    if (live[c]) {
        return;
    }
    live[c] = 1;
    if (y > 1 && board[c - w] != 1 && board[c - w * 2] != 1) {
        mark_live(c - w, w, h, board, live);
    }
    if (y < h - 2 && board[c + w] != 1 && board[c + w * 2] != 1) {
        mark_live(c + w, w, h, board, live);
    }
    if (x > 1 && board[c - 1] != 1 && board[c - 2] != 1) {
        mark_live(c - 1, w, h, board, live);
    }
    if (x < w - 2 && board[c + 1] != 1 && board[c + 2] != 1) {
        mark_live(c + 1, w, h, board, live);
    }
    return;
}

int parse_board(int y, int x, char s[5], int board[5], int goals[5], int live[5], int n_boxes[5]) {
    int w = x;
    int h = y;
    n_boxes[0] = 0;
    for (int i = 0; i < 5; i = i + 1) {
        if (s[i] == '#') {
            board[i] = 1;
        } else if (s[i] == '.' || s[i] == '+') {
            goals[i] = 1;
        } else if (s[i] == '*' || s[i] == '$') {
            goals[i] = (s[i] == '*') ? 1 : 0;
            n_boxes[0] = n_boxes[0] + 1;
        }
    }
    for (int i = 0; i < 5; i = i + 1) {
        if (goals[i]) {
            mark_live(i, w, h, board, live);
        }
    }
    return 0;
}

int success(int s_c[5], int goals[5], int n_boxes[5]) {
    for (int i = 1; i <= n_boxes[0]; i = i + 1) {
        if (!goals[s_c[i]]) {
            return 0;
        }
    }
    return 1;
}

int move_me(int s_c[5], int dy, int dx, int w, int h, int board[5], int live[5], int n_boxes[5], int n_c[5]) {
    int y = s_c[0] / w;
    int x = s_c[0] % w;
    int y1 = y + dy;
    int x1 = x + dx;
    int c1 = y1 * w + x1;
    if (y1 < 0 || y1 > h || x1 < 0 || x1 > w || board[c1] == 1) {
        return 0;
    }
    int at_box = 0;
    for (int i = 1; i <= n_boxes[0]; i = i + 1) {
        if (s_c[i] == c1) {
            at_box = i;
            break;
        }
    }
    int c2;
    if (at_box) {
        c2 = c1 + dy * w + dx;
        if (board[c2] == 1 || !live[c2]) {
            return 0;
        }
        for (int i = 1; i <= n_boxes[0]; i = i + 1) {
            if (s_c[i] == c2) {
                return 0;
            }
        }
    }
    for (int i = 1; i <= n_boxes[0]; i = i + 1) {
        n_c[i] = s_c[i];
    }
    n_c[0] = c1;
    if (at_box) {
        n_c[at_box] = c2;
    }
    for (int i = n_boxes[0]; i > 0; i = i - 1) {
        int t = 0;
        for (int j = 1; j < i; j = j + 1) {
            if (n_c[j] > n_c[j + 1]) {
                t = n_c[j];
                n_c[j] = n_c[j + 1];
                n_c[j + 1] = t;
            }
        }
        if (!t) {
            break;
        }
    }
    return 1;
}

int do_move(int s_c[5], int w, int h, int board[5], int goals[5], int live[5], int n_boxes[5], int next_level[5], int done[5]) {
    int n_c[5];
    if (move_me(s_c, 1, 0, w, h, board, live, n_boxes, n_c)) {
        if (success(n_c, goals, n_boxes)) {
            done[0] = 1;
            return 1;
        }
        for (int i = 0; i < 5; i = i + 1) {
            next_level[i] = n_c[i];
        }
        return 1;
    }
    if (move_me(s_c, -1, 0, w, h, board, live, n_boxes, n_c)) {
        if (success(n_c, goals, n_boxes)) {
            done[0] = 1;
            return 1;
        }
        for (int i = 0; i < 5; i = i + 1) {
            next_level[i] = n_c[i];
        }
        return 1;
    }
    if (move_me(s_c, 0, 1, w, h, board, live, n_boxes, n_c)) {
        if (success(n_c, goals, n_boxes)) {
            done[0] = 1;
            return 1;
        }
        for (int i = 0; i < 5; i = i + 1) {
            next_level[i] = n_c[i];
        }
        return 1;
    }
    if (move_me(s_c, 0, -1, w, h, board, live, n_boxes, n_c)) {
        if (success(n_c, goals, n_boxes)) {
            done[0] = 1;
            return 1;
        }
        for (int i = 0; i < 5; i = i + 1) {
            next_level[i] = n_c[i];
        }
        return 1;
    }
    return 0;
}

int main_func() {
    int board[5] = {0};
    int goals[5] = {0};
    int live[5] = {0};
    int n_boxes[5] = {0};
    char s[5] = " #.$@";
    parse_board(5, 5, s, board, goals, live, n_boxes);
    int s_c[5] = {0};
    int next_level[5] = {0};
    int done[5] = {0};
    for (int i = 0; i < 5; i = i + 1) {
        do_move(s_c, 5, 5, board, goals, live, n_boxes, next_level, done);
    }
    return 0;
}
