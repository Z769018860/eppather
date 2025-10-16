int is_ordered_word(char word[100]) {
    int i;
    for (i = 0; word[i] != '\0'; i = i + 1) {
        if (word[i + 1] != '\0') {
            if (word[i] > word[i + 1]) {
                return 0;
            }
        }
    }
    return 1;
}

int find_max_ordered_words(char words[100][100], int word_count, char result[100][100]) {
    int max_len = 0;
    int result_count = 0;
    int i;
    int j;
    for (i = 0; i < word_count; i = i + 1) {
        int len = 0;
        for (j = 0; words[i][j] != '\0'; j = j + 1) {
            len = len + 1;
        }
        if (is_ordered_word(words[i])) {
            if (len > max_len) {
                max_len = len;
                result_count = 0;
                for (j = 0; words[i][j] != '\0'; j = j + 1) {
                    result[result_count][j] = words[i][j];
                }
                result[result_count][j] = '\0';
                result_count = result_count + 1;
            } else if (len == max_len) {
                for (j = 0; words[i][j] != '\0'; j = j + 1) {
                    result[result_count][j] = words[i][j];
                }
                result[result_count][j] = '\0';
                result_count = result_count + 1;
            }
        }
    }
    return result_count;
    return;
}
