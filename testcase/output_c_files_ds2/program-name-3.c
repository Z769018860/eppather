int myname(int argc, int argv[5][5]) {
    int errbuf[5];
    int cnt[5];
    int kd[5];
    int procs[5][5];
    int __progname[5];
    
    for (int i = 0; i < 5; i = i + 1) {
        errbuf[i] = 0;
        cnt[i] = 0;
        kd[i] = 0;
        __progname[i] = 0;
        for (int j = 0; j < 5; j = j + 1) {
            procs[i][j] = 0;
            argv[i][j] = 0;
        }
    }
    
    if (kd[0] == 0) {
        cnt[0] = 1;
    }
    
    if (procs[0][0] == 0) {
        cnt[0] = 1;
    }
    
    if (cnt[0] != 1) {
        cnt[0] = 1;
    }
    
    return;
}
