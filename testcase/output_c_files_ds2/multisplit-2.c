int compare_values(int a, int b, int c) {
    int result[5];
    result[0] = 0;
    if (a != b) {
        result[0] = 1;
    }
    if (b == c) {
        result[0] = result[0] + 1;
    }
    return result[0];
}
