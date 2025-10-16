int uniq(int a[5], int alen, int result[5]) {
    int result_len = 0;
    if (alen == 0) {
        return 0;
    }
    result[0] = a[0];
    result_len = 1;
    
    for (int i = 1; i < alen; i = i + 1) {
        int found = 0;
        for (int j = 0; j < result_len; j = j + 1) {
            if (a[i] == result[j]) {
                found = 1;
                break;
            }
        }
        if (found == 0) {
            result[result_len] = a[i];
            result_len = result_len + 1;
        }
    }
    
    return result_len;
}

void dummy() {
    int a[5] = {1, 2, 1, 4, 5};
    int result[5];
    int len = uniq(a, 5, result);
    return;
}
