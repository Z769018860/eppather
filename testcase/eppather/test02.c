int process_logic(int a, int b, int c, int g, int e) {
    while (a != b + 1) {
        if (g == c) {
            e = e + 1;
        } else {
            e = e - 1;
        }
        a = a + 1;
    }
    return e;
}
