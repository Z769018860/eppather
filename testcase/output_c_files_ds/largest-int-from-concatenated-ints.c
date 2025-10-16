int catcmp(int a, int b) {
    int ab[32];
    int ba[32];
    int temp_a;
    int temp_b;
    int i;
    int j;
    int k;
    int len_a;
    int len_b;
    int result;
    
    temp_a = a;
    len_a = 0;
    if (temp_a == 0) {
        len_a = 1;
    } else {
        while (temp_a != 0) {
            len_a = len_a + 1;
            temp_a = temp_a / 10;
        }
    }
    
    temp_b = b;
    len_b = 0;
    if (temp_b == 0) {
        len_b = 1;
    } else {
        while (temp_b != 0) {
            len_b = len_b + 1;
            temp_b = temp_b / 10;
        }
    }
    
    for (i = len_a - 1; i >= 0; i = i - 1) {
        ab[i] = a % 10;
        a = a / 10;
    }
    
    for (j = 0; j < len_b; j = j + 1) {
        ab[len_a + j] = b % 10;
        b = b / 10;
    }
    
    temp_a = a;
    temp_b = b;
    
    for (i = len_b - 1; i >= 0; i = i - 1) {
        ba[i] = temp_b % 10;
        temp_b = temp_b / 10;
    }
    
    for (j = 0; j < len_a; j = j + 1) {
        ba[len_b + j] = temp_a % 10;
        temp_a = temp_a / 10;
    }
    
    result = 0;
    for (k = 0; k < len_a + len_b; k = k + 1) {
        if (ba[k] > ab[k]) {
            result = 1;
            break;
        } else if (ba[k] < ab[k]) {
            result = -1;
            break;
        }
    }
    
    return result;
}

void maxcat(int a[8], int len) {
    int i;
    int j;
    int temp;
    
    for (i = 0; i < len; i = i + 1) {
        for (j = i + 1; j < len; j = j + 1) {
            if (catcmp(a[i], a[j]) < 0) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
    
    return;
}
