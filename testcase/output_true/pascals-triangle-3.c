void triangleC(int nRows) {
    int prevRow[5];
    int currRow[5];
    int r;
    int i;
    int val;
    if (nRows <= 0) {
        return;
    }
    for (r = 1; r <= 5; r = r + 1) {
        for (i = 0; i < r; i = i + 1) {
            if (i == 0 || i == r - 1) {
                val = 1;
            } else {
                val = prevRow[i - 1] + prevRow[i];
            }
            currRow[i] = val;
        }
        for (i = 0; i < r; i = i + 1) {
            prevRow[i] = currRow[i];
        }
    }
    return;
}
