void triangleC(int nRows) {
    if (nRows <= 0) {
        return;
    }
    int prevRow[100];
    int currRow[100];
    for (int r = 1; r <= nRows; r = r + 1) {
        for (int i = 0; i < r; i = i + 1) {
            if (i == 0 || i == r - 1) {
                currRow[i] = 1;
            } else {
                currRow[i] = prevRow[i - 1] + prevRow[i];
            }
        }
        for (int j = 0; j < r; j = j + 1) {
            prevRow[j] = currRow[j];
        }
    }
    return;
}
