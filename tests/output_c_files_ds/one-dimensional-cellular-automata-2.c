int evolve(int c[20], int len) {
    int i;
    int diff = 0;
    int trans[8] = {0, 0, 0, 1, 0, 1, 1, 0};
    
    for (i = 0; i < len; i = i + 1) {
        if (c[i] == 35) {
            c[i] = 1;
        } else {
            c[i] = 0;
        }
    }
    
    for (i = 0; i < len; i = i + 1) {
        int left;
        int current;
        int right;
        int index;
        
        if (i - 1 < 0) {
            left = 0;
        } else {
            left = (c[i - 1] & 15) == 1;
        }
        
        current = (c[i] & 15) == 1;
        
        if (i + 1 >= len) {
            right = 0;
        } else {
            right = (c[i + 1] & 15) == 1;
        }
        
        index = left * 4 + current * 2 + right;
        if (trans[index] == 1) {
            c[i] = c[i] | 16;
        } else {
            c[i] = c[i] | 0;
        }
    }
    
    for (i = 0; i < len; i = i + 1) {
        diff = diff + ((c[i] & 15) ^ (c[i] >> 4));
    }
    
    for (i = 0; i < len; i = i + 1) {
        if ((c[i] >> 4) != 0) {
            c[i] = 35;
        } else {
            c[i] = 95;
        }
    }
    
    return diff;
}
