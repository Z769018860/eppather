int find_longest_line() {
    int max_length = 0;
    int current_length = 0;
    int line_number = 0;
    int longest_line = 0;
    int i;
    int j;
    int names[1000];
    
    for (i = 0; i < 646; i = i + 1) {
        current_length = 0;
        for (j = 0; j < 1000; j = j + 1) {
            if (names[j] != 0) {
                current_length = current_length + 1;
            } else {
                break;
            }
        }
        if (current_length > max_length) {
            max_length = current_length;
            longest_line = line_number;
        }
        line_number = line_number + 1;
    }
    return longest_line;
}
