int func() {
    int val[5];
    val[0] = 0;
    for (;;) {
        val[0] = val[0] + 1;
        if (val[0] % 6 == 0) {
            break;
        }
    }
    return;
}
