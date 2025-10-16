int func() {
    int ints[100];
    int int2[100];
    int i;
    for (i = 0; i < 100; i = i + 1) {
        ints[i] = 0;
        int2[i] = 0;
    }
    int temp[101];
    for (i = 0; i < 100; i = i + 1) {
        temp[i] = ints[i];
    }
    temp[100] = 0;
    for (i = 0; i < 100; i = i + 1) {
        ints[i] = temp[i];
    }
    return;
}
