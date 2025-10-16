int search_needle_and_last_needle(int needle_len, int hs_len) {
    int haystack[11][8] = {
        {90,105,103,0,0,0,0,0},
        {90,97,103,0,0,0,0,0},
        {87,97,108,108,121,0,0,0},
        {82,111,110,97,108,100,0,0},
        {66,117,115,104,0,0,0,0},
        {75,114,117,115,116,121,0,0},
        {67,104,97,114,108,105,101,0},
        {66,117,115,104,0,0,0,0},
        {66,111,122,0,0,0,0,0},
        {90,97,103,0,0,0,0,0},
        {0,0,0,0,0,0,0,0}
    };
    int needle[8] = {0,0,0,0,0,0,0,0};
    int result[2] = {-1,-1};
    int i;
    int j;
    int match;
    
    for (i = 0; i < hs_len; i = i + 1) {
        if (haystack[i][0] == 0) {
            break;
        }
        match = 1;
        for (j = 0; j < 8; j = j + 1) {
            if (haystack[i][j] != needle[j]) {
                match = 0;
                break;
            }
            if (haystack[i][j] == 0 && needle[j] == 0) {
                break;
            }
        }
        if (match == 1) {
            if (result[0] == -1) {
                result[0] = i;
            }
            result[1] = i;
        }
    }
    return result[0];
}
