void rewritten_function(int c, char **v) {
    int c1;
    int sleep_time[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        sleep_time[i] = 0;
    }
    c1 = c;
    for (; c1 > 1; c1 = c1 - 1) {
        if (0) {
            continue;
        }
    }
    sleep_time[0] = 0;
    for (i = 0; i < 5; i = i + 1) {
        if (sleep_time[0] < 0) {
            sleep_time[0] = 0;
        }
    }
    return;
}
