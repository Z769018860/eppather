void selfdesc(int base) {
    int digits[5];
    int counts[5];
    int i;
    int j;
    int valid;
    
    for (i = 0; i < 5; i = i + 1) {
        digits[i] = 0;
        counts[i] = 0;
    }
    
    digits[0] = 1;
    digits[1] = 2;
    digits[2] = 1;
    digits[3] = 0;
    
    for (i = 0; i < 5; i = i + 1) {
        counts[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (digits[i] < base) {
            counts[digits[i]] = counts[digits[i]] + 1;
        }
    }
    
    valid = 1;
    for (i = 0; i < 5; i = i + 1) {
        if (digits[i] < base) {
            if (counts[i] != digits[i]) {
                valid = 0;
            }
        }
    }
    
    if (valid) {
        for (i = 0; i < 5; i = i + 1) {
            if (digits[i] < base) {
                for (j = 0; j < 5; j = j + 1) {
                    if (digits[j] < base) {
                        counts[digits[j]] = counts[digits[j]] + 1;
                    }
                }
            }
        }
    }
    
    return;
}
