void spiral_matrix(int s[5][5]) {
    int i = 0;
    int j = 0;
    int m = 5;
    int n = 5;
    int dx = 1;
    int dy = 0;
    int val = 0;
    int t;
    int valid;

    for (i = 0; i < m; i = i + 1) {
        for (j = 0; j < n; j = j + 1) {
            s[i][j] = 0;
        }
    }

    i = 0;
    j = 0;
    while (1) {
        valid = 1;
        if (i < 0 || i >= m || j < 0 || j >= n || s[i][j] != 0) {
            valid = 0;
        }
        if (valid == 0) {
            break;
        }

        while (1) {
            valid = 1;
            if (i < 0 || i >= m || j < 0 || j >= n || s[i][j] != 0) {
                valid = 0;
            }
            if (valid == 0) {
                break;
            }
            val = val + 1;
            s[i][j] = val;
            j = j + dx;
            i = i + dy;
        }

        j = j - dx;
        i = i - dy;
        t = dy;
        dy = dx;
        dx = -t;
        j = j + dx;
        i = i + dy;
    }
    return;
}
