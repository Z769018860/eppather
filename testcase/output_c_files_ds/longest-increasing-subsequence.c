void lis(int *v, int len) {
    int next[100];
    int lengths[100];
    int i;
    int j;
    int max_len;
    int max_index;
    
    for (i = 0; i < len; i = i + 1) {
        lengths[i] = 1;
        next[i] = -1;
    }
    
    for (i = len - 1; i >= 0; i = i - 1) {
        for (j = i + 1; j < len; j = j + 1) {
            if (v[j] > v[i] && lengths[j] >= lengths[i]) {
                next[i] = j;
                lengths[i] = lengths[j] + 1;
            }
        }
    }
    
    max_len = lengths[0];
    max_index = 0;
    for (i = 1; i < len; i = i + 1) {
        if (lengths[i] > max_len) {
            max_len = lengths[i];
            max_index = i;
        }
    }
    
    return;
}
