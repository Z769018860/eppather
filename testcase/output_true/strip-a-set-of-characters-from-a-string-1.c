char* strip_chars(const char* string, const char* chars, int string_len, int chars_len) {
    char newstr[5];
    int counter = 0;
    int i;
    int j;
    int found;
    
    for (i = 0; i < 5; i = i + 1) {
        found = 0;
        for (j = 0; j < 5; j = j + 1) {
            if (string[i] == chars[j]) {
                found = 1;
            }
        }
        if (found == 0) {
            newstr[counter] = string[i];
            counter = counter + 1;
        }
    }
    newstr[counter] = 0;
    return newstr;
}
