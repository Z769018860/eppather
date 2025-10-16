int funcB_funcC(int a) {
    int integers[1];
    integers[0] = 0;
    static int ints[1];
    ints[0] = 0;
    integers[0] = a;
    int result;
    result = integers[0] + ints[0];
    return result;
    return;
}
