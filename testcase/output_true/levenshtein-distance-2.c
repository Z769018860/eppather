int levenshtein(int ls, int lt, int s[5], int t[5]) {
    int d[6][6];
    int i;
    int j;
    for (i = 0; i <= 5; i = i + 1) {
        for (j = 0; j <= 5; j = j + 1) {
            d[i][j] = -1;
        }
    }
    
    int dist(int i, int j) {
        if (d[i][j] >= 0) {
            return d[i][j];
        }
        
        int x;
        if (i == ls) {
            x = lt - j;
        } else if (j == lt) {
            x = ls - i;
        } else if (s[i] == t[j]) {
            x = dist(i + 1, j + 1);
        } else {
            x = dist(i + 1, j + 1);
            
            int y;
            y = dist(i, j + 1);
            if (y < x) {
                x = y;
            }
            y = dist(i + 1, j);
            if (y < x) {
                x = y;
            }
            x = x + 1;
        }
        d[i][j] = x;
        return x;
    }
    
    int result = dist(0, 0);
    return result;
}
