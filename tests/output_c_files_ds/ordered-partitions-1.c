int next_perm(int size, int * nums) {
    int *k;
    int *l;
    int tmp;
    
    k = nums + size - 2;
    while (k >= nums) {
        if (k[0] >= k[1]) {
            k = k - 1;
        } else {
            break;
        }
    }
    if (k < nums) {
        return 0;
    }
    
    l = nums + size - 1;
    while (*l <= *k) {
        l = l - 1;
    }
    tmp = *k;
    *k = *l;
    *l = tmp;
    
    l = nums + size - 1;
    k = k + 1;
    while (k < l) {
        tmp = *k;
        *k = *l;
        *l = tmp;
        k = k + 1;
        l = l - 1;
    }
    
    return 1;
}

void make_part(int n, int * sizes) {
    int x[1024];
    int i;
    int j;
    int *ptr;
    int len;
    
    len = 0;
    ptr = x;
    for (i = 0; i < n; i = i + 1) {
        for (j = 0; j < sizes[i]; j = j + 1) {
            *ptr = i;
            ptr = ptr + 1;
            len = len + 1;
        }
    }
    
    do {
        for (i = 0; i < n; i = i + 1) {
            for (j = 0; j < len; j = j + 1) {
                if (x[j] == i) {
                }
            }
        }
    } while (next_perm(len, x));
    
    return;
}
