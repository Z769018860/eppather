void print_names(void) {
    int students[5][20] = {
        {'A','p','r','i','l',0},
        {'B','o','b',0},
        {'C','h','a','d',0},
        {'D','a','v','e',0},
        {0xC3,0x89,'m','i','l','y',0}
    };
    for (int i = 0; i < 5; i = i + 1) {
        int j = 0;
        while (students[i][j] != 0) {
            j = j + 1;
        }
    }
    return;
}
