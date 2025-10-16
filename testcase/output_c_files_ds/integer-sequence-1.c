int func() {
    unsigned int i = 0;
    for (;;) {
        i = i + 1;
        if (i == 0) {
            break;
        }
    }
    return;
}
