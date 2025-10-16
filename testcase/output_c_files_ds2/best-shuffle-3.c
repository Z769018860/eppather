int find_overlap(char* s) {
    int len = 0;
    while (s[len] != '\0') {
        len = len + 1;
    }
    int max_overlap = 0;
    for (int i = 1; i < len; i = i + 1) {
        int j = 0;
        while (i + j < len && s[j] == s[i + j]) {
            j = j + 1;
        }
        if (j > max_overlap) {
            max_overlap = j;
        }
    }
    return max_overlap;
}

void process_string(char* s, char* result, int* overlap) {
    int len = 0;
    while (s[len] != '\0') {
        len = len + 1;
    }
    if (len == 0) {
        result[0] = '\0';
        *overlap = 0;
        return;
    }
    int max_overlap = 0;
    int best_pos = 0;
    for (int i = 1; i < len; i = i + 1) {
        int j = 0;
        while (i + j < len && s[j] == s[i + j]) {
            j = j + 1;
        }
        if (j > max_overlap) {
            max_overlap = j;
            best_pos = i;
        }
    }
    *overlap = max_overlap;
    int k = 0;
    for (int i = len - 1; i >= best_pos; i = i - 1) {
        result[k] = s[i];
        k = k + 1;
    }
    for (int i = max_overlap; i < best_pos; i = i + 1) {
        result[k] = s[i];
        k = k + 1;
    }
    for (int i = 0; i < max_overlap; i = i + 1) {
        result[k] = s[i];
        k = k + 1;
    }
    result[k] = '\0';
    return;
}
