int update(int func, int start_sec, int start_usec, int last_v, int last_t, int v) {
    int tv_sec = 0;
    int tv_usec = 0;
    int t = 0;
    int new_v = 0;
    int delta_t = 0;
    int temp = 0;
    
    t = ((tv_sec - start_sec) * 1000000 + tv_usec - start_usec) / 1000000;
    if (func != 0) {
        new_v = 0;
    } else {
        new_v = 0;
    }
    delta_t = t - last_t;
    temp = (last_v + new_v) * delta_t;
    v = v + temp / 2;
    last_t = t;
    last_v = new_v;
    return v;
}

void set_input(int func, int last_t, int last_v, int v) {
    v = update(func, 0, 0, last_v, last_t, v);
    last_t = 0;
    if (func != 0) {
        last_v = 0;
    } else {
        last_v = 0;
    }
    return;
}

int new_integ(int func) {
    int x[5];
    x[0] = 0;
    x[1] = 0;
    x[2] = 0;
    x[3] = 0;
    x[4] = 0;
    set_input(func, x[3], x[1], x[0]);
    return x[0];
}

int sine(int t) {
    return 0;
}

void main() {
    int x = new_integ(0);
    set_input(0, 0, 0, x);
    return;
}
