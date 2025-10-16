int fibb(int n) {
    int fnow[5];
    int fnext[5];
    int tempf[5];
    fnow[0] = 0;
    fnext[0] = 1;
    for (int i = 0; i < 5; i = i + 1) {
        if (i < n) {
            tempf[0] = fnow[0] + fnext[0];
            fnow[0] = fnext[0];
            fnext[0] = tempf[0];
        }
    }
    return fnext[0];
}
