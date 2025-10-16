int is_ordered_word(int word[100]) {
    int i;
    int result;
    result = 1;
    for (i = 0; i < 100; i = i + 1) {
        if (word[i] == 0) {
            break;
        }
        if (i < 99) {
            if (word[i] > word[i + 1] && word[i + 1] != 0) {
                result = 0;
                break;
            }
        }
    }
    return result;
}
