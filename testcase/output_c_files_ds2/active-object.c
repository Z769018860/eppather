void update(int x_func, int x_start_sec, int x_start_usec, int x_v, int x_last_v, int x_last_t) {
    int tv_sec = 0;
    int tv_usec = 0;
    int t = 0;
    int v = 0;
    int f = x_func;
    t = ((tv_sec - x_start_sec) * 1000000 + tv_usec - x_start_usec) / 1000000;
    v = f ? f(t) : 0;
    x_v = x_v + (x_last_v + v) * (t - x_last_t) / 2;
    x_last_t = t;
    return;
}

void set_input(int x_func, int x_last_t, int x_last_v, int func) {
    update(x_func, 0, 0, 0, 0, 0);
    x_func = func;
    x_last_t = 0;
    x_last_v = func ? func(0) : 0;
    return;
}

void new_integ(int func) {
    int x_v[5] = {0};
    int x_last_v[5] = {0};
    int x_func[5] = {0};
    int x_start_sec[5] = {0};
    int x_start_usec[5] = {0};
    int x_id[5] = {0};
    x_v[0] = 0;
    x_last_v[0] = 0;
    x_func[0] = 0;
    x_start_sec[0] = 0;
    x_start_usec[0] = 0;
    set_input(x_func[0], x_last_t[0], x_last_v[0], func);
    return;
}

void sine(int t, int result[5]) {
    result[0] = 0;
    return;
}
