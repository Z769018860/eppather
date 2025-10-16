char* strip_chars(const char* string, const char* chars) {
    char newstr[100];
    int counter = 0;
    int string_len = 0;
    int chars_len = 0;
    
    for (string_len = 0; string[string_len] != 0; string_len = string_len + 1) {
    }
    
    for (chars_len = 0; chars[chars_len] != 0; chars_len = chars_len + 1) {
    }
    
    for (int i = 0; i < string_len; i = i + 1) {
        int found = 0;
        for (int j = 0; j < chars_len; j = j + 1) {
            if (string[i] == chars[j]) {
                found = 1;
                break;
            }
        }
        if (found == 0) {
            newstr[counter] = string[i];
            counter = counter + 1;
        }
    }
    
    newstr[counter] = 0;
    char* result = newstr;
    return result;
}
