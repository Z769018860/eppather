int get_mode(int x[5], int len, int list_v[5], int list_c[5]) {
    int i;
    int j;
    int temp;
    int swapped;
    
    for (i = 0; i < len; i = i + 1) {
        for (j = 0; j < len - i - 1; j = j + 1) {
            if (x[j] > x[j + 1]) {
                temp = x[j];
                x[j] = x[j + 1];
                x[j + 1] = temp;
            }
        }
    }
    
    j = 1;
    for (i = 0; i < len - 1; i = i + 1) {
        if (x[i] != x[i + 1]) {
            j = j + 1;
        }
    }
    
    list_v[0] = x[0];
    list_c[0] = 1;
    j = 0;
    for (i = 0; i < len - 1; i = i + 1) {
        if (x[i] != x[i + 1]) {
            j = j + 1;
            list_v[j] = x[i + 1];
            list_c[j] = 0;
        }
        list_c[j] = list_c[j] + 1;
    }
    
    for (i = 0; i < j + 1; i = i + 1) {
        swapped = 0;
        for (int k = 0; k < j - i; k = k + 1) {
            if (list_c[k] < list_c[k + 1]) {
                temp = list_c[k];
                list_c[k] = list_c[k + 1];
                list_c[k + 1] = temp;
                temp = list_v[k];
                list_v[k] = list_v[k + 1];
                list_v[k + 1] = temp;
                swapped = 1;
            }
        }
        if (swapped == 0) {
            break;
        }
    }
    
    i = 0;
    while (i <= j && list_c[i] == list_c[0]) {
        i = i + 1;
    }
    
    return i;
    return;
}
