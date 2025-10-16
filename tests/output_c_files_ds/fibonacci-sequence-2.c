int fibb(int n) {
    int fnow;
    int fnext;
    int tempf;
    fnow = 0;
    fnext = 1;
    for (; n > 1; n = n - 1) {
        tempf = fnow + fnext;
        fnow = fnext;
        fnext = tempf;
    }
    return fnext;
}
