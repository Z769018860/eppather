int find_max_overlap(char* s) {
    int len = 0;
    int max_overlap = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int overlap = 0;
    
    for (i = 0; s[i] != '\0'; i = i + 1) {
        len = len + 1;
    }
    
    for (i = 1; i < len; i = i + 1) {
        overlap = 0;
        for (j = 0, k = i; k < len; j = j + 1, k = k + 1) {
            if (s[j] == s[k]) {
                overlap = overlap + 1;
            } else {
                break;
            }
        }
        if (overlap > max_overlap) {
            max_overlap = overlap;
        }
    }
    
    return max_overlap;
}
