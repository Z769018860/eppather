int compare(int a, int b, int c) {
    int result;
    if (a != b) {
        if (b == c) {
            result = 1;
        } else {
            result = 0;
        }
    } else {
        if (b != c) {
            result = 1;
        } else {
            result = 0;
        }
    }
    return result;
}
