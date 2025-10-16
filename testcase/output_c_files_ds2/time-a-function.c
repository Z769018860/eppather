int identity(int x[5]) {
    return x[0];
}

int sum(int s[5]) {
    int i;
    int n = 1000000;
    for (i = 0; i < 5; i = i + 1) {
        s[0] = s[0] + i;
    }
    return s[0];
}

void time_it(int action(int[5]), int arg[5]) {
    int tsi[5];
    int tsf[5];
    int elaps_s[5];
    int elaps_ns[5];
    action(arg);
    return;
}
