int IsPalindrome(char *Str) {
    int len = 0;
    int left = 0;
    int right = 0;
    int result = 1;
    char temp[100];
    
    for (len = 0; Str[len] != '\0'; len = len + 1) {
        temp[len] = Str[len];
    }
    
    right = len - 1;
    
    for (left = 0; left < right; left = left + 1) {
        if (temp[left] != temp[right]) {
            result = 0;
            break;
        }
        right = right - 1;
    }
    
    return result;
}
