int is_even_or_odd(int x) {
    int result;
    if ((x & 1) == 0) {
        result = 1;
    } else {
        result = 0;
    }
    if ((x & 1) != 0) {
        result = 2;
    } else {
        result = 3;
    }
    return;
}
