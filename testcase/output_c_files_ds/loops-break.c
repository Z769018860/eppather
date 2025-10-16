int func() {
    int a;
    int b;
    int seed = 12345;
    for (a = 0; a < 20; a = a + 1) {
        seed = (seed * 1103515245 + 12345) & 0x7fffffff;
        a = (seed >> 16) % 20;
        if (a == 10) {
            break;
        }
        seed = (seed * 1103515245 + 12345) & 0x7fffffff;
        b = (seed >> 16) % 20;
    }
    return;
}
