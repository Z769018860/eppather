void sort_letters(char s[100]) {
    int i;
    int j;
    char t;
    for (i = 0; s[i] != '\0'; i = i + 1) {
        for (j = i + 1; s[j] != '\0'; j = j + 1) {
            if (s[j] < s[i]) {
                t = s[j];
                s[j] = s[i];
                s[i] = t;
            }
        }
    }
    return;
}
