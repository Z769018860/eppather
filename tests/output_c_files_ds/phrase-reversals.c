char* reverse_section(char* s, int length) {
    if (length == 0) {
        return s;
    }
    int i;
    char temp;
    for (i = 0; i < length / 2 + 1; i = i + 1) {
        temp = s[i];
        s[i] = s[length - i];
        s[length - i] = temp;
    }
    return s;
}

char* reverse_words_in_order(char* s, char delim) {
    int len = 0;
    while (s[len] != 0) {
        len = len + 1;
    }
    if (len == 0) {
        return s;
    }
    int i;
    int j;
    for (i = 0; i < len - 1; i = i + 1) {
        for (j = 0; s[i + j] != 0 && s[i + j] != delim; j = j + 1) {
        }
        reverse_section(s + i, j - 1);
        i = i + j;
    }
    return s;
}

char* reverse_string(char* s) {
    int len = 0;
    while (s[len] != 0) {
        len = len + 1;
    }
    if (len == 0) {
        return s;
    }
    return reverse_section(s, len - 1);
}

char* reverse_order_of_words(char* s, char delim) {
    reverse_string(s);
    reverse_words_in_order(s, delim);
    return s;
}

void combined_function(char* s, char delim) {
    reverse_order_of_words(s, delim);
    return;
}
