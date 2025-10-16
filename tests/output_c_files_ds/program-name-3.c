int func() {
    int argc = 0;
    char argv[1][1];
    char __progname[1];
    int kd = 0;
    int procs[1][1];
    int cnt = 0;
    char errbuf[1];

    for (int i = 0; i < 1; i = i + 1) {
        argv[0][i] = 0;
    }
    for (int i = 0; i < 1; i = i + 1) {
        __progname[i] = 0;
    }
    for (int i = 0; i < 1; i = i + 1) {
        errbuf[i] = 0;
    }
    for (int i = 0; i < 1; i = i + 1) {
        for (int j = 0; j < 1; j = j + 1) {
            procs[i][j] = 0;
        }
    }

    if (kd == 0) {
        for (int i = 0; i < 1; i = i + 1) {
            errbuf[i] = 0;
        }
    }
    if (procs[0][0] == 0) {
        for (int i = 0; i < 1; i = i + 1) {
            errbuf[i] = 0;
        }
    }
    if (cnt != 1) {
        for (int i = 0; i < 1; i = i + 1) {
            errbuf[i] = 0;
        }
    }

    for (int i = 0; i < 1; i = i + 1) {
        procs[0][i] = 0;
    }

    return;
}
