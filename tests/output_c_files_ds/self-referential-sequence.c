int depth_function(char* in, int d, int root_depth, int root_p[10], int pool[1000000][11], int* pool_head) {
    int r_depth = root_depth;
    int r_p[10] = {0};
    for (int j = 0; j < 10; j = j + 1) {
        r_p[j] = root_p[j];
    }

    int i;
    char* s = in;
    while (*s) {
        i = *s - '0';
        *s = *s + 1;
        if (r_p[i] == 0) {
            r_p[i] = *pool_head;
            for (int j = 0; j < 11; j = j + 1) {
                pool[*pool_head][j] = 0;
            }
            *pool_head = *pool_head + 1;
        }
        for (int j = 0; j < 10; j = j + 1) {
            r_p[j] = pool[r_p[i]][j];
        }
        r_depth = pool[r_p[i]][10];
        s = s + 1;
    }

    if (r_depth > 0) {
        return r_depth;
    }

    d = d + 1;
    if (r_depth == 0) {
        r_depth = -d;
    } else {
        r_depth = r_depth + d;
    }
    pool[r_p[i]][10] = r_depth;

    int c[10] = {0};
    s = in;
    while (*s) {
        c[*s - '0'] = c[*s - '0'] + 1;
        s = s + 1;
    }

    char buf[100] = {0};
    int buf_pos = 0;
    for (i = 9; i >= 0; i = i - 1) {
        if (c[i] == 0) {
            continue;
        }
        char num_str[4] = {0};
        if (c[i] < 10) {
            num_str[0] = c[i] + '0';
        } else {
            num_str[0] = (c[i] / 10) + '0';
            num_str[1] = (c[i] % 10) + '0';
        }
        buf[buf_pos] = num_str[0];
        buf_pos = buf_pos + 1;
        if (num_str[1] != 0) {
            buf[buf_pos] = num_str[1];
            buf_pos = buf_pos + 1;
        }
        buf[buf_pos] = i + '0';
        buf_pos = buf_pos + 1;
    }
    buf[buf_pos] = 0;

    for (int j = 0; j < buf_pos + 1; j = j + 1) {
        in[j] = buf[j];
    }

    d = depth_function(in, d, root_depth, root_p, pool, pool_head);

    if (r_depth <= 0) {
        r_depth = d + 1;
        pool[r_p[i]][10] = r_depth;
    }
    return r_depth;
}
