int func() {
    int array[40];
    int i;
    for (i = 0; i < 20; i = i + 1) {
        array[i] = 0;
    }
    for (i = 20; i < 40; i = i + 1) {
        array[i] = 0;
    }
    return;
}
