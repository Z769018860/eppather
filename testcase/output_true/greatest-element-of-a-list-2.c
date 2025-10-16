int max_function(int a, int b, int c, int d, int e) {
    int max_val = a;
    int temp;
    if (b > max_val) {
        max_val = b;
    }
    if (c > max_val) {
        max_val = c;
    }
    if (d > max_val) {
        max_val = d;
    }
    if (e > max_val) {
        max_val = e;
    }
    return max_val;
}
