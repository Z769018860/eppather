int char_repeat(int n, char c, char dest[6]) {
    for (int i = 0; i < n; i = i + 1) {
        dest[i] = c;
    }
    dest[n] = 0;
    return 0;
}
