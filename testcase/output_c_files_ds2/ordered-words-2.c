int is_ordered_word(int word_len, char word[100]) {
    int i;
    int result;
    result = 1;
    for (i = 0; i < 5; i = i + 1) {
        if (i < word_len) {
            if (word[i] != 0) {
                if (i + 1 < word_len) {
                    if (word[i] > word[i + 1]) {
                        if (word[i + 1] != 0) {
                            result = 0;
                        }
                    }
                }
            }
        }
    }
    return result;
}

void array_append(int words_array_len, char words_array_words[5][100], int new_word_len, char new_word[100]) {
    int i;
    for (i = 0; i < 5; i = i + 1) {
        if (i < new_word_len) {
            words_array_words[words_array_len][i] = new_word[i];
        } else {
            words_array_words[words_array_len][i] = 0;
        }
    }
    return;
}

void array_free(int words_array_len, char words_array_words[5][100]) {
    int i;
    int j;
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            words_array_words[i][j] = 0;
        }
    }
    return;
}

void list_print(int words_array_len, char words_array_words[5][100]) {
    int i;
    int j;
    for (i = 0; i < 5; i = i + 1) {
        if (i < words_array_len) {
            for (j = 0; j < 5; j = j + 1) {
                if (words_array_words[i][j] != 0) {
                }
            }
        }
    }
    return;
}
