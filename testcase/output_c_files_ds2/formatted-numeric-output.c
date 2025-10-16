int func() {
    int r[5];
    r[0] = 7;
    int i;
    for (i = 0; i < 5; i = i + 1) {
        r[0] = r[0];
    }
    return;
}
