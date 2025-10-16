int palindrome(const char* t) {
    int l = 0;
    int i = 0;
    int result = 1;
    for (i = 0; t[i] != '\0'; i = i + 1) {
        l = l + 1;
    }
    for (i = 0; i < l / 2; i = i + 1) {
        if (t[i] != t[l - i - 1]) {
            result = 0;
            break;
        }
    }
    return result;
}

int palindrome_r(const char* t, int left, int right) {
    if (left >= right) {
        return 1;
    }
    if (t[left] != t[right - 1]) {
        return 0;
    }
    return palindrome_r(t, left + 1, right - 1);
}
