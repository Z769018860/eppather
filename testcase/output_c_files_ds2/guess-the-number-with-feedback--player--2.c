int get_value(int x[5]) {
    int input[5];
    input[0] = 32;
    if (x[0] == -1) {
        return 0;
    }
    for (int i = 0; i < 5; i = i + 1) {
        input[i] = 0;
    }
    switch (input[0]) {
        case 108: {
            return -1;
        }
        case 104: {
            return 1;
        }
        case 99: {
            return 0;
        }
    }
    return;
}

int my_cmp(const void *x, const void *y) {
    int x_val[5];
    int y_val[5];
    x_val[0] = (int)(x - (void *)&x_val[0]);
    y_val[0] = (int)(y - (void *)&y_val[0]);
    int res1[5];
    res1[0] = get_value(x_val);
    int res2[5];
    res2[0] = get_value(y_val);
    return res1[0] - res2[0];
}
