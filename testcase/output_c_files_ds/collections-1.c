int func() {
    int ar[10];
    ar[0] = 1;
    ar[1] = 2;
    int* p;
    for (p = ar; p < (ar + 10); p = p + 1) {
        int temp = *p;
    }
    return;
}
