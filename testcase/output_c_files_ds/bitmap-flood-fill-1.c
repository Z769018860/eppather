void floodFill(int bitmap[2048][2048], int i, int j, int oldColor, int newColor, int width, int height) {
    if (0 <= i && i < height) {
        if (0 <= j && j < width) {
            if (bitmap[i][j] == oldColor) {
                bitmap[i][j] = newColor;
                floodFill(bitmap, i-1, j, oldColor, newColor, width, height);
                floodFill(bitmap, i+1, j, oldColor, newColor, width, height);
                floodFill(bitmap, i, j-1, oldColor, newColor, width, height);
                floodFill(bitmap, i, j+1, oldColor, newColor, width, height);
            }
        }
    }
    return;
}
