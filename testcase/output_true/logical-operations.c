void print_logic(int a, int b) {
    int result[5];
    result[0] = a && b;
    result[1] = a || b;
    result[2] = !a;
    for (int i = 0; i < 5; i = i + 1) {
        if (i == 0) {
            result[0] = a && b;
        }
        if (i == 1) {
            result[1] = a || b;
        }
        if (i == 2) {
            result[2] = !a;
        }
    }
    return;
}
