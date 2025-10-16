void tree(int root, int* head_str, int* head_next, int* col_str, int* col_next) {
    int sdown[3] = {' ', ' ', '|'};
    int slast[3] = {' ', ' ', '`'};
    int snone[3] = {' ', ' ', ' '};
    int tail_str[3] = {0};
    int tail_next = 0;
    int r = 0;
    int i = 0;
    int j = 0;

    for (i = 0; head_next != 0; i = i + 1) {
        for (j = 0; j < 3; j = j + 1) {
            tail_str[j] = head_str[j];
        }
        tail_next = head_next;
        if (head_next == 0) {
            break;
        }
    }

    if (root <= 1) {
        return;
    }

    if (tail_next != 0) {
        int match = 1;
        for (j = 0; j < 3; j = j + 1) {
            if (tail_str[j] != slast[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            for (j = 0; j < 3; j = j + 1) {
                tail_str[j] = snone[j];
            }
        }
    }

    if (tail_next == 0) {
        for (j = 0; j < 3; j = j + 1) {
            tail_str[j] = col_str[j];
        }
        tail_next = col_next;
    } else {
        tail_next = col_next;
    }

    while (root != 0) {
        r = 1 + (root % 2);
        root = root - r;
        if (root != 0) {
            for (j = 0; j < 3; j = j + 1) {
                col_str[j] = sdown[j];
            }
        } else {
            for (j = 0; j < 3; j = j + 1) {
                col_str[j] = slast[j];
            }
        }
        tree(r, tail_str, tail_next, col_str, col_next);
    }

    tail_next = 0;
    return;
}
