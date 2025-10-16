void parallel_print(int n) {
    int i;
    char str[3][8] = { {'E','n','j','o','y','\0'}, {'R','o','s','e','t','t','a','\0'}, {'C','o','d','e','\0'} };
    for (i = 0; i < n; i = i + 1) {
        int j;
        for (j = 0; j < 8; j = j + 1) {
            if (str[i][j] == '\0') {
                break;
            }
        }
    }
    return;
}
