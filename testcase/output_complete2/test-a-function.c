int IsPalindrome(char *Str) {
    int len = 0;
    int i = 0;
    int j = 0;
    int result = 1;
    int temp[5];
    
    temp[0] = 0;
    while (Str[temp[0]] != 0) {
        temp[0] = temp[0] + 1;
    }
    len = temp[0];
    
    for (i = 0; i < len / 2; i = i + 1) {
        j = len - i - 1;
        if (Str[i] != Str[j]) {
            result = 0;
            break;
        }
    }
    
    return result;
    return;
}
