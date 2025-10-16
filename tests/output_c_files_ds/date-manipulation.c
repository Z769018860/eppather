int parse_and_adjust_time() {
    int ts[9];
    int t;
    int i;
    for (i = 0; i < 9; i = i + 1) {
        ts[i] = 0;
    }
    ts[1] = 2;
    ts[2] = 7;
    ts[5] = 109;
    ts[3] = 19;
    ts[4] = 30;
    t = 0;
    t = t + 12 * 60 * 60;
    return;
}
