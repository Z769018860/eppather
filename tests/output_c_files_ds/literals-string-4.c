char* foo(char* MY_SYMBOL) {
    char result[100];
    int i;
    int j;
    for (i = 0; i < 7; i = i + 1) {
        result[i] = "prefix_"[i];
    }
    for (j = 0; MY_SYMBOL[j] != '\0'; j = j + 1) {
        result[i + j] = MY_SYMBOL[j];
    }
    for (i = i + j; i < i + j + 7; i = i + 1) {
        result[i] = "_suffix"[i - (i + j)];
    }
    result[i] = '\0';
    return result;
}
