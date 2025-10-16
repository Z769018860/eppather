void encode(int get_func(int*), int put_func(int*, int), int* in, int* out) {
    unsigned char buf[256];
    int len = 0;
    int repeat = 0;
    int end = 0;
    int c;
    
    while (end == 0) {
        c = get_func(in);
        if (c == -1) {
            end = 1;
        }
        if (end == 0) {
            buf[len] = c;
            len = len + 1;
            if (len <= 1) {
                continue;
            }
        }

        if (repeat != 0) {
            if (buf[len - 1] != buf[len - 2]) {
                repeat = 0;
            }
            if (repeat == 0 || len == 129 || end != 0) {
                put_func(out, end != 0 ? len : len - 1);
                put_func(out, buf[0]);
                buf[0] = buf[len - 1];
                len = 1;
            }
        } else {
            if (buf[len - 1] == buf[len - 2]) {
                repeat = 1;
                if (len > 2) {
                    put_func(out, 128 + len - 2);
                    for (int i = 0; i < len - 2; i = i + 1) {
                        put_func(out, buf[i]);
                    }
                    buf[0] = buf[len - 1];
                    buf[1] = buf[len - 1];
                    len = 2;
                }
                continue;
            }
            if (len == 128 || end != 0) {
                put_func(out, 128 + len);
                for (int i = 0; i < len; i = i + 1) {
                    put_func(out, buf[i]);
                }
                len = 0;
                repeat = 0;
            }
        }
    }
    put_func(out, -1);
    return;
}

void decode(int get_func(int*), int put_func(int*, int), int* in, int* out) {
    int c;
    int i;
    int cnt;
    
    while (1) {
        c = get_func(in);
        if (c == -1) {
            return;
        }
        if (c > 128) {
            cnt = c - 128;
            for (i = 0; i < cnt; i = i + 1) {
                put_func(out, get_func(in));
            }
        } else {
            cnt = c;
            c = get_func(in);
            for (i = 0; i < cnt; i = i + 1) {
                put_func(out, c);
            }
        }
    }
    return;
}
