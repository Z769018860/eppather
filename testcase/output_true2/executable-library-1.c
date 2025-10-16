int hailstone(int n, int* arr) {
    int i;
    int len;
    len = 0;
    arr[0] = n;
    len = len + 1;
    for (i = 0; i < 5; i = i + 1) {
        if (n == 1) {
            break;
        } else {
            if (n % 2 == 0) {
                n = n / 2;
            } else {
                n = 3 * n + 1;
            }
            arr[len] = n;
            len = len + 1;
        }
    }
    return len;
}
