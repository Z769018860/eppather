int sum(int lo_byname, int hi_byname) {
    int i;
    int temp[5];
    temp[0] = 0;
    int lo;
    lo = lo_byname;
    int hi;
    hi = hi_byname;
    for (i = lo; i <= hi; i = i + 1) {
        temp[0] = temp[0] + (1 / i);
    }
    return temp[0];
    return;
}
