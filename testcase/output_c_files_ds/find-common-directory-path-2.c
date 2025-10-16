int compare_paths(char path1[100], char path2[100]) {
    int i = 0;
    int common_len = 0;
    for (i = 0; i < 100; i = i + 1) {
        if (path1[i] == '\0' || path2[i] == '\0') {
            break;
        }
        if (path1[i] == path2[i]) {
            common_len = common_len + 1;
        } else {
            break;
        }
    }
    return common_len;
}
