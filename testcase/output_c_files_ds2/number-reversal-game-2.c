void shuffle_list_do_flip_check_array(int* list, int len) {
    int n = 100;
    int a = 0;
    int b = 0;
    int buf = 0;
    int swap = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int temp = 0;
    int flag = 1;
    
    for (i = 0; i < n; i = i + 1) {
        a = (i * 37 + 123) % len;
        b = (i * 51 + 456) % len;
        buf = list[a];
        list[a] = list[b];
        list[b] = buf;
    }
    
    for (j = 0; j < len; j = j + 1) {
        if (j > 0) {
            if (list[j] != (list[j - 1] + 1)) {
                flag = 0;
            }
        }
    }
    
    if (flag != 0) {
        for (i = 0; i < n; i = i + 1) {
            a = (i * 37 + 123) % len;
            b = (i * 51 + 456) % len;
            buf = list[a];
            list[a] = list[b];
            list[b] = buf;
        }
    }
    
    for (k = 0; k < 5; k = k + 1) {
        temp = len - k - 1;
        for (i = 0; i < temp; i = i + 1) {
            if (i < (temp - i)) {
                swap = list[i];
                list[i] = list[temp - i];
                list[temp - i] = swap;
            }
        }
    }
    
    return;
}
