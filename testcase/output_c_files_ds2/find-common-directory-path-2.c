void common_path(int path1_len, int path2_len, int path3_len) {
    int common[5];
    int i;
    int min_len;
    
    if (path1_len < path2_len) {
        if (path1_len < path3_len) {
            min_len = path1_len;
        } else {
            min_len = path3_len;
        }
    } else {
        if (path2_len < path3_len) {
            min_len = path2_len;
        } else {
            min_len = path3_len;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        common[i] = 0;
    }
    
    for (i = 0; i < min_len; i = i + 1) {
        common[0] = i;
    }
    
    return;
}
