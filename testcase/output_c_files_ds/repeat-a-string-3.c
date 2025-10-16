char * char_repeat(int n, char c) {
    char dest[100];
    int i;
    for (i = 0; i < n; i = i + 1) {
        dest[i] = c;
    }
    dest[n] = '\0';
    return dest;
}

return;
