void encode(int (*get)(int*), int (*put)(int*, int), int* in, int* out) {
    int buf[256];
    int len = 0;
    int repeat = 0;
    int end = 0;
    int c;
    int i;
    
    while (end == 0) {
        c = get(in);
        if (c == -1) {
            end = 1;
        } else {
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
                put(out, end != 0 ? len : len - 1);
                put(out, buf[0]);
                buf[0] = buf[len - 1];
                len = 1;
            }
        } else {
            if (buf[len - 1] == buf[len - 2]) {
                repeat = 1;
                if (len > 2) {
                    put(out, 128 + len - 2);
                    for (i = 0; i < len - 2; i = i + 1) {
                        put(out, buf[i]);
                    }
                    buf[0] = buf[1];
                    buf[1] = buf[len - 1];
                    len = 2;
                }
                continue;
            }
            if (len == 128 || end != 0) {
                put(out, 128 + len);
                for (i = 0; i < len; i = i + 1) {
                    put(out, buf[i]);
                }
                len = 0;
                repeat = 0;
            }
        }
    }
    put(out, -1);
    return;
}

void decode(int (*get)(int*), int (*put)(int*, int), int* in, int* out) {
    int c;
    int i;
    int cnt;
    
    for (;;) {
        c = get(in);
        if (c == -1) {
            return;
        }
        if (c > 128) {
            cnt = c - 128;
            for (i = 0; i < cnt; i = i + 1) {
                put(out, get(in));
            }
        } else {
            cnt = c;
            c = get(in);
            for (i = 0; i < cnt; i = i + 1) {
                put(out, c);
            }
        }
    }
    return;
}
