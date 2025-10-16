int evolve(int cell[5], int backup[5], int len) {
    int diff = 0;
    int trans[8] = {95, 95, 95, 35, 95, 35, 35, 95};
    int i;
    int left;
    int self;
    int right;
    int index;
    
    for (i = 0; i < 5; i = i + 1) {
        if (i - 1 < 0) {
            left = 0;
        } else {
            if (cell[i - 1] != 95) {
                left = 1;
            } else {
                left = 0;
            }
        }
        
        if (cell[i] != 95) {
            self = 1;
        } else {
            self = 0;
        }
        
        if (i + 1 >= len) {
            right = 0;
        } else {
            if (cell[i + 1] != 95) {
                right = 1;
            } else {
                right = 0;
            }
        }
        
        index = left * 4 + self * 2 + right;
        backup[i] = trans[index];
        
        if (backup[i] != cell[i]) {
            diff = diff + 1;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        cell[i] = backup[i];
    }
    
    return diff;
}
