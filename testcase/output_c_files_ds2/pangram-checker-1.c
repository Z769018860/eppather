int is_pangram(const char *s, int n1, int n2) {
    int alpha[52] = {97,98,99,100,101,102,103,104,106,105,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90};
    int wasused[26] = {0};
    int total = 0;
    int i = 0;
    int j;
    int idx;
    int found;
    
    for (; s[i] != 0; i = i + 1) {
        found = 0;
        for (j = 0; j < 52; j = j + 1) {
            if (s[i] == alpha[j]) {
                found = 1;
                break;
            }
        }
        if (found == 0) {
            continue;
        }
        idx = j % 26;
        if (wasused[idx] == 0) {
            total = total + 1;
            wasused[idx] = 1;
        }
        if (total == 26) {
            return 1;
        }
    }
    return 0;
    return;
}
