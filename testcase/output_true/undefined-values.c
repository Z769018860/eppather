int func(int n1, int n2) {
    int junk[5];
    int junkp[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        junk[i] = 0;
        junkp[i] = 0;
    }
    junkp[0] = n1;
    if (junkp[0]) {
        junk[0] = junkp[0];
    }
    return;
}
