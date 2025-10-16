void process_sequence(int n, char word[5][5], int ones[5], int zeros[5], int entropy[5]) {
    int i;
    int j;
    int total[5];
    int result[5];
    int c[5];
    
    for (i = 0; i < 5; i = i + 1) {
        ones[0] = 0;
        zeros[0] = 0;
        for (j = 0; j < 5; j = j + 1) {
            c[0] = word[i][j];
            if (c[0] == 0) {
                break;
            }
            if (c[0] == '0') {
                zeros[0] = zeros[0] + 1;
            }
            if (c[0] == '1') {
                ones[0] = ones[0] + 1;
            }
        }
        total[0] = ones[0] + zeros[0];
        if (total[0] != 0) {
            if (ones[0] != 0 && zeros[0] != 0) {
                result[0] = 1;
            } else {
                result[0] = 0;
            }
        } else {
            result[0] = 0;
        }
        entropy[i] = result[0];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (i < n) {
            for (j = 0; j < 5; j = j + 1) {
                if (word[i][j] == 0) {
                    break;
                }
            }
        }
    }
    return;
}
