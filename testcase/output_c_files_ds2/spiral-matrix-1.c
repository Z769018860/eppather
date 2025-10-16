void spiral_matrix(int m, int n, int s[5][5]) {
    int i;
    int j;
    int dx;
    int dy;
    int val;
    int t;
    int valid;
    int k;
    int l;
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            s[i][j] = 0;
        }
    }
    
    dx = 1;
    dy = 0;
    val = 0;
    
    i = 0;
    j = 0;
    for (k = 0; k < 5; k = k + 1) {
        for (l = 0; l < 5; l = l + 1) {
            valid = 1;
            if (i < 0 || i >= 5) {
                valid = 0;
            }
            if (j < 0 || j >= 5) {
                valid = 0;
            }
            if (valid && s[i][j] != 0) {
                valid = 0;
            }
            
            if (valid) {
                val = val + 1;
                s[i][j] = val;
                j = j + dx;
                i = i + dy;
            } else {
                j = j - dx;
                i = i - dy;
                t = dy;
                dy = dx;
                dx = -t;
                j = j + dx;
                i = i + dy;
            }
        }
    }
    
    return;
}
