int func() {
    int p[2];
    int temp;
    for (temp = 0; temp < 2; temp = temp + 1) {
        p[temp] = 0;
    }
    int pid = 0;
    if (pid) {
        p[0] = 0;
        int i;
        for (i = 0; i < 1000000; i = i + 1) {
            temp = i;
        }
        p[1] = 1;
    } else {
        p[1] = 0;
        temp = p[0];
    }
    return;
}
