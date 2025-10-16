int func(int n1, int n2) {
    int array[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        array[i] = 0;
    }
    for (i = 0; i < 5; i = i + 1) {
        array[i] = array[i] + 1;
    }
    return;
}
