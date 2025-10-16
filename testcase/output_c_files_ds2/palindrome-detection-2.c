int palindrome(int s[5], int t[5], int n) {
    int result[5];
    result[0] = 1;
    t[0] = 0;
    for (; t[0] < n; t[0] = t[0] + 1) {
        if (s[t[0]] == 0) {
            break;
        }
    }
    t[0] = t[0] - 1;
    for (; s[0] < t[0]; s[0] = s[0] + 1, t[0] = t[0] - 1) {
        if (s[s[0]] != t[t[0]]) {
            result[0] = 0;
            break;
        }
    }
    return result[0];
}
