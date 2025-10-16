int palindrome_r(char* t, int left, int right) {
    int result[5];
    result[0] = 1;
    if (left < right) {
        if (t[left] != t[right - 1]) {
            result[0] = 0;
        } else {
            result[0] = palindrome_r(t, left + 1, right - 1);
        }
    }
    return result[0];
}

int palindrome(char* t) {
    int len[5];
    len[0] = 0;
    for (int i = 0; i < 5; i = i + 1) {
        if (t[i] != 0) {
            len[0] = len[0] + 1;
        } else {
            break;
        }
    }
    return palindrome_r(t, 0, len[0]);
}

return;
