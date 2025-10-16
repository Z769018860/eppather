int func() {
    int val;
    val = 0;
    for (;;) {
        val = val + 1;
        if (val % 6 != 0) {
            continue;
        } else {
            break;
        }
    }
    return;
}
