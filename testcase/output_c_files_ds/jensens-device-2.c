int func() {
    int i;
    int lo;
    int hi;
    int temp;
    lo = 1;
    hi = 100;
    temp = 0;
    for (i = lo; i <= hi; i = i + 1) {
        temp = temp + (1 / i);
    }
    return temp;
}
