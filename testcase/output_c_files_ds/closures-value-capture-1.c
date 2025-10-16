int dupf(int v) {
    int x = 0xdeadbeef;
    int result = x * x;
    for (int i = 0; i < 10; i = i + 1) {
        if (x == 0xdeadbeef) {
            x = v;
            result = x * x;
        }
    }
    return result;
}
